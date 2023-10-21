/// @file matrix.hpp
/// @brief Abstract matrix interface
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_MATRIX_HPP_INCLUDED
#define OGXX_MATRIX_HPP_INCLUDED

#include "primitive_definitions.hpp"
#include "iterator.hpp" // TBD


/// Root namespace of the OGxx library.
namespace ogxx
{

  /////////////////////////////////////////////////////////////////////////////
  // Auxiliary structures

  /// @brief Matrix shape description (just two sizes).
  struct Matrix_shape
  {
    /// @brief Quantity of rows in a matrix.
    Scalar_size rows = 0;
    /// @brief Quantity of columns in a matrix.
    Scalar_size cols = 0;

    /// @brief Check if the size representation is valid.
    /// @return true if both rows and cols are positive or both are zero
    [[nodiscard]] constexpr auto is_valid() const noexcept
      -> bool
    {
      return (rows > 0 && cols > 0) || (rows == 0 && cols == 0);
    }

    /// @brief Make square matrix shape.
    /// @param size size of the square matrix (the same number of rows and columns)
    /// @return Matrix_shape object containing square matrix shape
    [[nodiscard]] constexpr static auto square(Scalar_size size) noexcept
      -> Matrix_shape
    {
      return { size, size };
    }
  };


  /// @brief Index of an item of a matrix.
  /// Negative indices are to be interpreted as offsets from the right end
  /// like it is done in Python, e.g. a[-1] is the last element of a.
  struct Matrix_index
  {
    /// @brief The first index of a matrix item (zero-based).
    Scalar_index row = 0;
    /// @brief The second index of a matrix item (zero-based).
    Scalar_index col = 0;

    /// @brief Check if the current index is valid if applied to a matrix of the given shape.
    /// @param shape matrix sizes
    /// @return true if the index is valid (points within the matrix)
    [[nodiscard]] constexpr auto is_valid_for(Matrix_shape shape) const noexcept
      -> bool
    {
      return is_within(row, -shape.rows, shape.rows - 1)
          && is_within(col, -shape.cols, shape.cols - 1);
    }
  };


  /// @brief Rectangular matrix window coordinates: position and shape.
  struct Matrix_window
  {
    /// @brief The position of the left upper corner (minimal row and column).
    /// Negative index inverses the corresponding extent.
    Matrix_index position;
    /// @brief The size of a matrix.
    Matrix_shape shape;

    /// @brief Create a square matrix window.
    /// @param position where is the left upper corner
    /// @param size rows and columns in the window
    /// @return square Matrix_window object
    [[nodiscard]] constexpr static auto square(Matrix_index position, Scalar_size size) noexcept
      -> Matrix_window
    {
      return { position, Matrix_shape::square(size) };
    }

    /// @brief Create a rectangular window positioned at (0, 0).
    /// @param shape sizes of the window
    /// @return Matrix_window object
    [[nodiscard]] constexpr static auto main(Matrix_shape shape) noexcept
      -> Matrix_window
    {
      return { {}, shape };
    }

    /// @brief Create a square window positioned at (0, 0)
    /// @param size square window size
    /// @return square Matrix_window object
    [[nodiscard]] constexpr static auto main(Scalar_size size) noexcept
      -> Matrix_window
    {
      return main(Matrix_shape::square(size));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Matrix_base interface

  /// @brief Owning pointer to a matrix object (Matrix_base).
  using Matrix_uptr = std::unique_ptr<class Matrix_base>;

  /// @brief Common matrix function independent of matrix item type.
  class Matrix_base
  {  
  public:
    virtual ~Matrix_base() {}

    /// @brief Get sizes of the matrix.
    /// @return Matrix_shape object containing rows and columns count.
    [[nodiscard]] virtual auto shape() const noexcept
      -> Matrix_shape = 0;

    /// @brief Change matrix sizes (if possible in-place). 
    /// Zero fills the resulting matrix.
    /// May throw bad_alloc if new_shape is too large.
    /// @param new_shape new matrix sizes: rows and columns
    virtual void reshape(Matrix_shape new_shape) = 0;

  protected:
    Matrix_base& operator=(Matrix_base const&) = default;
    Matrix_base& operator=(Matrix_base&&) = default;
  };

}

#endif//OGXX_MATRIX_HPP_INCLUDED
