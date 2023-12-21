/// doc-comment
#include <ogxx/bit_matrix.hpp>

namespace ogxx
{

  class Bit_matrix_window_view
    : public Bit_matrix
  {
  public:
    Bit_matrix(Matrix_window window, Bit_matrix& matrix)
      : _window(window)
      , _matrix(&matrix)
    {}

    // Bit_matrix

    auto get(Matrix_index position) const noexcept
      -> bool override
    {
      if (_window.shape.check_and_correct(position))
        return _matrix.get(position.row + _window.position.row,
                           position.col + _window.position.col);
      return false;
    }

    auto set(Matrix_index position, bool value)
      -> bool override
    {
        if (_window.shape.check_and_correct(position))
            return _matrix.set(position.row + _window.position.row,
                position.col + _window.position.col, value);
        return false;
    }

    auto flip(Matrix_index position)
      -> bool override
    {
        if (_window.shape.check_and_correct(position))
            return _matrix.flip(position.row + _window.position.row,
                position.col + _window.position.col);
        return false;
    }

    void fill(bool value) override
    {
      for (Scalar_index i = 0; i < _window.shape.rows; ++i)
        for (Scalar_index j = 0; j < _window.shape.cols; ++j)
          _matrix.set(i + _window.position.row, j + _window.position.col, value);
    }

    auto iterate_row(Scalar_index row) const
      -> Basic_iterator_uptr<bool> override
    {
      // TODO: throw that the method is unimplimented
    }

    auto iterate_col(Scalar_index col) const
      -> Basic_iterator_uptr<bool> override
    {
      // TODO: throw that the method is unimplimented
    }

    auto view(Matrix_window window) const
      -> Bit_matrix_const_uptr      override
    {
        auto window_view = std::make_unique<Bit_matrix_window_view>(window, *_matrix);
        return matrix_view;
    }

    auto view(Matrix_window window)
      -> Bit_matrix_uptr override
    {
        auto window_view = std::make_unique<Bit_matrix_window_view>(window, *_matrix);
        return matrix_view;
    }

    auto copy(Matrix_window window) const
      -> Bit_matrix_uptr override
    {
        window.position.row += _window.position.row;
        window.position.col += _window.position.col;
        return _matrix->copy(window);
    }

    // Matrix_base

    auto shape() const noexcept
      -> Matrix_shape  override
    {
      return _window.shape;
    }

    void reshape(Matrix_shape new_shape) override
    {
      throw std::runtime_error("Bit_matrix_window_view::reshape: impossible");
    }

    // Sized_iterable<bool>

    auto size() const noexcept
      -> Scalar_size  override
    {
      return _window.shape.element_count();
    }

    auto is_empty() const noexcept
      -> bool       override
    {
      return _window.shape.rows == 0;
    }

    auto iterate() const
      -> Basic_iterator_uptr<bool> override
    {
      // TODO: throw that the method is unimplemented
    }

  private:
    Matrix_window _window;
    Bit_matrix*   _matrix = nullptr;
  };

}
