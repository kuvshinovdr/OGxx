/// @file matrix.hpp
/// @brief Abstract matrix interface
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_MATRIX_HPP_INCLUDED
#define OGXX_MATRIX_HPP_INCLUDED

#include <ogxx/primitive_definitions.hpp>
#include <ogxx/iterator.hpp>
#include <compare>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /////////////////////////////////////////////////////////////////////////////
  // Auxiliary structures

  /// @brief Index of an item of a matrix.
  /// Negative indices are to be interpreted as offsets from the right end
  /// like it is done in Python, e.g. a[-1] is the last element of a.
  struct Matrix_index
  {
    /// @brief The first index of a matrix item (zero-based).
    Scalar_index row = 0;
    /// @brief The second index of a matrix item (zero-based).
    Scalar_index col = 0;

    friend auto operator<=>(Matrix_index a, Matrix_index b) noexcept = default;
    friend bool operator== (Matrix_index a, Matrix_index b) noexcept = default;
  };


  /// @brief Matrix shape description (just two sizes).
  struct Matrix_shape
  {
    /// @brief Quantity of rows in a matrix.
    Scalar_size rows = 0;
    /// @brief Quantity of columns in a matrix.
    Scalar_size cols = 0;

    friend auto operator<=>(Matrix_shape a, Matrix_shape b) noexcept = default;
    friend bool operator== (Matrix_shape a, Matrix_shape b) noexcept = default;

    /// @brief Check if the size representation is valid.
    /// @return true if both rows and cols are positive or both are zero
    [[nodiscard]] constexpr auto is_valid() const noexcept
      -> bool
    {
      return (rows > 0 && cols > 0) || (rows == 0 && cols == 0);
    }

    /// Check if the matrix is a square matrix.
    [[nodiscard]] constexpr auto is_square() const noexcept
      -> bool
    {
      return rows == cols;
    }

    /// Compute total element count of a matrix with this shape.
    /// Throws on overflow.
    [[nodiscard]] auto element_count() const
      -> Scalar_size
    {
      Scalar_size result = 0;
      if (checked_multiply(rows, cols, result))
        return result;

      throw std::out_of_range("Matrix_shape::element_count: overflow");
    }

    /// @brief Check if the index is valid if applied to a matrix of the given shape.
    /// @param position matrix position to be checked
    /// @return true if the index is valid (is contained in the matrix)
    [[nodiscard]] constexpr auto contains(Matrix_index position) const noexcept
      -> bool
    {
      return is_within(position.row, -rows, rows - 1)
          && is_within(position.col, -cols, cols - 1);
    }

    /// @brief Check if the current index is valid for the given shape and correct negative row or col according to the shape.
    /// @param position the index to be checked and corrected (by reference)
    /// @return true if the index is correct, false otherwise
    [[nodiscard]] constexpr auto check_and_correct(Matrix_index& position) const noexcept
      -> bool
    {
      if (position.row < 0)
        position.row += rows;
      if (position.col < 0)
        position.col += cols;

      return contains(position);
    }

    /// @brief Get linear index of the matrix index for row-major packed matrix stored in a linear array.
    /// @param position 2D index to be transformed into a linear index
    /// @return index in row-major linear array matrix storage
    [[nodiscard]] constexpr auto linear_index(Matrix_index position) const noexcept
      -> Scalar_index
    {
      return cols * position.row + position.col;
    }

    /// @brief Computes a linear index in a packed matrix where only the upper part (including the main diagonal) is stored.
    /// @param position 2D index to be transformed into a linear index
    /// @return index in row-major linear array storage for symmetric matrix
    [[nodiscard]] constexpr auto upper_index(Matrix_index position) const noexcept
    {
      // ASSERT rows == cols
      auto [row, col] = position;
      if (col < row)
        std::swap(row, col);
      
      // cols * row - row * (row - 1) / 2 + (col - row) =
      return (row * ((cols << 1) - (row + 1)) >> 1) + col;
    }

    /// @brief Computes a linear index in a packed matrix where only the upper part without the main diagonal is stored (unmd means "upper no main diagonal").
    /// @param position 2D index to be transformed into a linear index
    /// @return index in row-major linear array storage for symmetric matrix without main diagonal
    [[nodiscard]] constexpr auto unmd_index(Matrix_index position) const noexcept
    {
      // ASSERT rows == cols
      // ASSERT position.row != position.col
      auto [row, col] = position;
      if (col < row)
        std::swap(row, col);

      // row * cols - row * (row + 1) / 2 + col - row - 1 =
      return (row * ((cols << 1) - (row + 3)) >> 1) + (col - 1);
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


  /// @brief Rectangular matrix window coordinates: position and shape.
  struct Matrix_window
  {
    /// @brief The position of the left upper corner (minimal row and column).
    /// Negative index inverses the corresponding extent.
    Matrix_index position;
    /// @brief The size of a matrix.
    Matrix_shape shape;

    friend bool operator==(Matrix_window const& a, Matrix_window const& b) noexcept = default;

    /// Get the right-lower item coordinates.
    /// Does not work right with negative position indices or empty shape.
    [[nodiscard]] constexpr auto right_lower_coordinates() const noexcept
      -> Matrix_index
    {
      return { position.row + shape.rows - 1, position.col + shape.cols - 1 };
    }

    /// @brief Create a square matrix window.
    /// @param position where is the left upper corner
    /// @param size     rows and columns in the window
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

    /// Check if the window fits in a matrix shape.
    [[nodiscard]] constexpr auto fits_into(Matrix_shape shape) noexcept
      -> bool
    {
      return shape.contains(position) && shape.contains(right_lower_coordinates());
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Matrix_base interface

  class Matrix_base;

  /// @brief Owning pointer to a matrix object (Matrix_base).
  using Matrix_uptr = std::unique_ptr<Matrix_base>;

  /// @brief Owning pointer to a read-only matrix object (Matrix_base).
  using Matrix_const_uptr = std::unique_ptr<Matrix_base const>;

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
    /// May throw bad_alloc if new_shape is too large or invalid.
    /// @param new_shape new matrix sizes: rows and columns
    virtual void reshape(Matrix_shape new_shape) = 0;

  protected:
    Matrix_base& operator=(Matrix_base const&) noexcept = default;
    Matrix_base& operator=(Matrix_base&&) noexcept      = default;
  };

}

#endif//OGXX_MATRIX_HPP_INCLUDED
