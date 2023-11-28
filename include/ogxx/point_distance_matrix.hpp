/// @file point_distance_matrix.hpp
/// @brief Facilities to compute distance matrices according to selected metrics.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_POINT_DISTANCE_MATRIX_HPP_INCLUDED
#define OGXX_POINT_DISTANCE_MATRIX_HPP_INCLUDED

#include <ogxx/iterable.hpp>
#include <ogxx/st_matrix.hpp>


namespace ogxx
{

  /// An interface representing metrics calculator object.
  class Metrics
  {
  public:
    virtual ~Metrics() {}

    /// @brief The only operation supported which computes the distance between two points according to their coordinates.
    /// @param p1_coords an iterator enumerating coordinates of the first point
    /// @param p2_coords an iterator enumerating coordinates of the second point
    /// @return the distance between the points; points may have different number of dimensions, then the lower dimension point is considered to be appended with zeroes
    [[nodiscard]] virtual auto compute(
        Float_iterator_uptr p1_coords, 
        Float_iterator_uptr p2_coords
      ) const noexcept -> Float = 0;
  };

  /// @brief An owning pointer to a Metrics object.
  using Metrics_uptr = std::unique_ptr<Metrics>;

  /// @brief Create a matrix object computing point distances for a given set of points (thus read-only).
  /// @param metrics how to define distance between two points
  /// @param points  iterator of points each of one is represented by an iterator of its coordinates
  /// @return matrix object
  [[nodiscard]] auto new_point_distance_matrix(
                    Metrics_uptr metrics,
                    Basic_iterator_uptr<Float_iterator_uptr> points)
    -> Float_matrix_const_uptr;


  /////////////////////////////////////////////////////////////////////////////
  // Different metrics

  /// @brief Predefined metrics factory functions.
  namespace metrics
  {

    /// Computes how many point coordinates in same positions differ. 
    [[nodiscard]] auto new_hamming_metrics() -> Metrics_uptr;

    /// Computes the sum of absolute differences of coordinates.
    [[nodiscard]] auto new_manhattan_metrics() -> Metrics_uptr;

    /// Computes square root of the sum of squared coordinate differences.
    [[nodiscard]] auto new_euclidian_metrics() -> Metrics_uptr;

    /// Computes maximal absolute difference of coordinates.
    [[nodiscard]] auto new_chebyshev_metrics() -> Metrics_uptr;

    /// Computes the sum of absolute differences raised to power p and then raises it to 1/p power.
    /// Special cases: p = 0 -> Hamming, p = 1 -> Manhattan, p = 2 -> Euclidian, p = inf -> Chebyshev.
    [[nodiscard]] auto new_p_norm_metrics(Float p) -> Metrics_uptr;

    /// If the points are collinear returns Euclidian distance between them.
    /// If not, returns the sum of Euclidian distances between each point and the origin.
    [[nodiscard]] auto new_french_railway_metrics() -> Metrics_uptr;

  }

}

#endif//OGXX_POINT_DISTANCE_MATRIX_HPP_INCLUDED
