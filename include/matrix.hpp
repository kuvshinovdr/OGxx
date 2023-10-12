/// @file matrix.hpp
/// @brief Abstract matrix interface
/// @author Kuvshinov D.R.
#ifndef OGXX_MATRIX_HPP_INCLUDED
#define OGXX_MATRIX_HPP_INCLUDED

#include <cstddef>

/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Linear sequence size.
  using Scalar_size = std::ptrdiff_t;

  /// @brief Matrix shape description (just two sizes).
  struct Matrix_shape
  {
    /// @brief Quantity of rows in a matrix.
    Scalar_size rows = 0;
    /// @brief Quantity of columns in a matrix.
    Scalar_size cols = 0;

    /// @brief Make square matrix shape.
    /// @param size size of the square matrix (the same number of rows and columns)
    /// @return Matrix_shape object containing square matrix shape
    [[nodiscard]] constexpr static auto square(Scalar_size size) noexcept
      -> Matrix_shape
    {
      return { size, size };
    }
  };


  /// @brief Linear random-access sequence index.
  using Scalar_index = std::ptrdiff_t;

  /// @brief Index of an item of a matrix.
  /// Negative indices are to be interpreted as offsets from the right end
  /// like it is done in Python, e.g. a[-1] is the last element of a.
  struct Matrix_index
  {
    /// @brief The first index of a matrix item (zero-based).
    Scalar_index row = 0;
    /// @brief The second index of a matrix item (zero-based).
    Scalar_index col = 0;
  };


  /// @brief Bit matrix interface.
  class Abstract_bit_matrix
  {
  public:
    virtual ~Abstract_bit_matrix() {}

    /// @brief Get sizes of the matrix.
    /// @return Matrix_shape object containing rows and columns count.
    [[nodiscard]] virtual auto shape() const noexcept
      -> Matrix_shape = 0;

    /// @brief Change matrix sizes (if possible in-place). 
    /// Zero fills the resulting matrix.
    /// May throw bad_alloc if new_shape is too large.
    /// @param new_shape new matrix sizes: rows and columns
    virtual void reshape(Matrix_shape new_shape) = 0;

    /// @brief Get the item of a matrix at the given position.
    /// @param position matrix item position (row, column)
    /// @return true or false according the bit value, false if position is out of range
    [[nodiscard]] virtual auto operator()(Matrix_index position) const noexcept
      -> bool = 0;

    /// @brief Get the item of a matrix at the given position (row, col).
    /// @param row the first index of the item (zero-based)
    /// @param col the second index of the item (zero-based)
    /// @return true or false according the bit value, false if position is out of range
    [[nodiscard]] auto operator()(Scalar_index row, Scalar_index col) const noexcept
      -> bool { return (*this)(Matrix_index{row, col}); }

    /// @brief Set an item of the matrix.
    /// Throws std::out_of_range if position is out of range.
    /// @param position matrix item position (row, column)
    /// @param value true (by default) or false, the new value
    /// @return the old value of the set bit
    virtual auto set(Matrix_index position, bool value = true) 
      -> bool = 0;

    /// @brief A shortcut for set(position, false).
    /// @param position matrix item position (row, column)
    /// @return the old value of the set bit 
    auto reset(Matrix_index position)
      -> bool { return set(position, false); }

    /// @brief Effectively returns set(position, !operator()(position)) but in one virtual call.
    /// Throws std::out_of_range if position is out of range.
    /// @param position matrix item position (row, column)
    /// @return the old value of the flipped bit
    virtual auto flip(Matrix_index position)
      -> bool = 0;
  };

}

#endif//OGXX_MATRIX_HPP_INCLUDED
