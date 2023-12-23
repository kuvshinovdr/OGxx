/// @file point_distance_matrix.cpp
/// @brief Implementation of point distance matrix adapter for a metrics object.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/primitive_definitions.hpp>
#include <ogxx/point_distance_matrix.hpp>
#include <ogxx/iterator_algorithms.hpp>
#include <ogxx/stl_iterator.hpp>

#include <cmath>
#include <algorithm> // std::max
#include <numeric>
#include <vector>
#include <new>


namespace ogxx::metrics
{

  namespace
  {

    class Point_distance_matrix
      : public Float_matrix
    {
    public:
      Point_distance_matrix() = default;

      explicit Point_distance_matrix(
          Metrics_uptr metrics,
          Basic_iterator_uptr<Float_iterator_uptr> points)
        : _metrics(std::move(metrics))
      {
        for (Float_iterator_uptr point; points->next(point);)
        {
          _point.emplace_back();
          
          auto& cur = _point.back();
          for (Float coord; point->next(coord);)
            cur.emplace_back(coord);

          cur.shrink_to_fit();
        }

        _shape = Matrix_shape::square(static_cast<Scalar_size>(_point.size()));
      }


      ///////////////////////////////////////////////////////////////
      // Interface implementation

      // Matrix_base

      auto shape() const noexcept
        -> Matrix_shape override { return _shape; }

      void reshape(Matrix_shape new_shape) override
      {
        throw std::logic_error("Point_distance_matrix::reshape: can not reshape a read-only matrix");
      }

      // Iterable<Float>

      auto iterate() const
        -> Basic_iterator_uptr<See_by<Float>> override
      {
        // TODO
        throw std::logic_error("Point_distance_matrix::iterate: not yet implemented");
      }

      auto is_empty() const noexcept
        -> bool override { return _point.empty(); }

      // Sized_iterable<Float>

      auto size() const noexcept
        -> Scalar_size override
      {
        Scalar_size result = 0;
        auto const  n = static_cast<Scalar_size>(_point.size());
        if (checked_multiply(n, n, result))
          return result;
        
        return -1;
      }

      // St_matrix<Float>

      auto get(Matrix_index position) const noexcept
        -> Float override
      {
        if (!_shape.check_and_correct(position) || position.row == position.col)
          return {};

        try // suppress out-of-memory error... but, what can we do then?
        {
          return _metrics->compute(
              new_stl_iterator(_point[position.row]),
              new_stl_iterator(_point[position.col]));
        }
        catch (std::bad_alloc const&)
        {
          return not_a_number; // a bad thing too...
        }
      }

      auto set(Matrix_index, Float) -> Float override
      {
        throw std::logic_error("Point_distance_matrix::set: can not change a read-only matrix");
      }

      void fill(Float) override
      {
        throw std::logic_error("Point_distance_matrix::fill: can not change a read-only matrix");
      }

      auto iterate_row(Scalar_index row) const
        -> Basic_iterator_uptr<Float> override
      {
        // TODO
        throw std::logic_error("Point_distance_matrix::iterate_row: not yet implemented");
      }

      auto iterate_col(Scalar_index col) const
        -> Basic_iterator_uptr<Float> override
      {
        // TODO
        throw std::logic_error("Point_distance_matrix::iterate_col: not yet implemented");
      }

      auto view(Matrix_window window) const
        -> Float_matrix_const_uptr override
      {
        // TODO
        throw std::logic_error("Point_distance_matrix::view: not yet implemented");
      }

      auto view(Matrix_window window)
        -> Float_matrix_uptr override
      {
        throw std::logic_error("Point_distance_matrix::view: can not change a read-only matrix");
      }

      auto copy(Matrix_window window) const
        -> Float_matrix_uptr override
      {
        // TODO: make a dense matrix.
        throw std::logic_error("Point_distance_matrix::copy: not yet implemented");
      }

    private:
      Metrics_uptr                    _metrics;
      std::vector<std::vector<Float>> _point;
      Matrix_shape                    _shape;
    };

  }

  auto new_point_distance_matrix(
      Metrics_uptr metrics,
      Basic_iterator_uptr<Float_iterator_uptr> points)
    -> Float_matrix_const_uptr
  {
    return std::make_unique<Point_distance_matrix>(std::move(metrics), std::move(points));
  }


  ///////////////////////////////////////////////////////////////////
  // Metrics implementations

  namespace
  {

    [[nodiscard]] auto metrics_compute(
        Float_iterator_uptr p1_coords,
        Float_iterator_uptr p2_coords,
        auto combine
      ) noexcept -> Float
    {
      Float result = 0;
      for (Float u, v;;)
      {
        if (!p1_coords->next(u))
          return accumulate(std::move(p2_coords), result, combine);
        if (!p2_coords->next(v))
          return accumulate(std::move(p1_coords), combine(result, u), combine);

        result = combine(result, u - v);
      }
    }

    class Hamming_metrics
      : public Metrics
    {
    public:
      auto compute(
          Float_iterator_uptr p1_coords,
          Float_iterator_uptr p2_coords
        ) const noexcept -> Float override
      {
        return metrics_compute(std::move(p1_coords), std::move(p2_coords),
          [](Float a, Float x) { return a + (x == 0); });
      }
    };


    class Manhattan_metrics
      : public Metrics
    {
    public:
      auto compute(
          Float_iterator_uptr p1_coords,
          Float_iterator_uptr p2_coords
        ) const noexcept -> Float override
      {
        return metrics_compute(std::move(p1_coords), std::move(p2_coords),
          [](Float a, Float x) { return a + std::fabs(x); });
      }
    };


    class Euclidian_metrics
      : public Metrics
    {
    public:
      auto compute(
          Float_iterator_uptr p1_coords,
          Float_iterator_uptr p2_coords
        ) const noexcept -> Float override
      {
        return std::sqrt(metrics_compute(std::move(p1_coords), std::move(p2_coords),
          [](Float a, Float x) { return a + x * x; }));
      }
    };


    class Chebyshev_metrics
      : public Metrics
    {
    public:
      auto compute(
          Float_iterator_uptr p1_coords,
          Float_iterator_uptr p2_coords
        ) const noexcept -> Float override
      {
        return metrics_compute(std::move(p1_coords), std::move(p2_coords),
          [](Float a, Float x) { return std::max(a, std::fabs(x)); });
      }
    };


    class P_norm_metrics
      : public Metrics
    {
    public:
      P_norm_metrics() = default;

      explicit P_norm_metrics(Float p)
        : p(p) {}

      auto compute(
          Float_iterator_uptr p1_coords,
          Float_iterator_uptr p2_coords
        ) const noexcept -> Float override
      {
        return std::pow(metrics_compute(std::move(p1_coords), std::move(p2_coords),
          [p = this->p](Float a, Float x) { return a + std::pow(std::fabs(x), p); }), Float{1} / p);
      }

    private:
      Float p {2};
    };


    class French_railway_metrics
      : public Metrics
    {
    public:
      auto compute(
          Float_iterator_uptr p1_coords,
          Float_iterator_uptr p2_coords
        ) const noexcept -> Float override
      {
        bool collinear = true;
        Float proportion_max = -infinity;
        Float proportion_min = +infinity;
        Float p1norm = 0;
        Float p2norm = 0;

        for (Float u = 0, v = 0; p1_coords->next(u) || p2_coords->next(v); u = v = 0)
        {
          if (u == 0 && v == 0)
            continue;

          p1norm += u * u;
          p2norm += v * v;
          
          if (collinear)
          {
            if (u != 0 && v != 0 && std::signbit(u) != std::signbit(v))
            {
              collinear = false;
              continue;
            }

            auto const proportion = u / v;
            proportion_max = std::max(proportion_max, proportion);
            proportion_min = std::min(proportion_min, proportion);

            if (eps < proportion_max - proportion_min)
              collinear = false;
          }
        }

        if (collinear)
          return std::fabs(p1norm - p2norm);
        return p1norm + p2norm;
      }

    private:
      Float eps = 1e-6;
    };

  }

  auto new_hamming_metrics() -> Metrics_uptr
  {
    return std::make_unique<Hamming_metrics>();
  }

  auto new_manhattan_metrics() -> Metrics_uptr
  {
    return std::make_unique<Manhattan_metrics>();
  }

  auto new_euclidian_metrics() -> Metrics_uptr
  {
    return std::make_unique<Euclidian_metrics>();
  }

  auto new_chebyshev_metrics() -> Metrics_uptr
  {
    return std::make_unique<Chebyshev_metrics>();
  }

  auto new_p_norm_metrics(Float p) -> Metrics_uptr
  {
    if (p == 0)
      return new_hamming_metrics();
    if (p == 1)
      return new_manhattan_metrics();
    if (p == 2)
      return new_euclidian_metrics();
    if (p == infinity)
      return new_chebyshev_metrics();

    return std::make_unique<P_norm_metrics>(p);
  }

  auto new_french_railway_metrics() -> Metrics_uptr
  {
    return std::make_unique<French_railway_metrics>();
  }

}
