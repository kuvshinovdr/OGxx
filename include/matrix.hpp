/// @file matrix.hpp
/// @brief Abstract matrix interface
/// @author Kuvshinov D.R.
#ifndef OGXX_MATRIX_HPP_INCLUDED
#define OGXX_MATRIX_HPP_INCLUDED

#include <cstddef>
#include <optional>

/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Linear sequence size.
  using Scalar_size = std::size_t;

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
  using Scalar_index = std::size_t;

  /// @brief Index of an item of a matrix.
  struct Matrix_index
  {
    /// @brief The first index of a matrix item.
    Scalar_index row = 0;
    /// @brief The second index of a matrix item.
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

    /// @brief Get the item of a matrix at the given position.
    /// @param position matrix item position (row, column). 
    /// @return true or false according the bit value, false if position is out of range
    [[nodiscard]] virtual auto operator()(Matrix_index position) const noexcept
      -> bool = 0;
  };

}

#endif//OGXX_MATRIX_HPP_INCLUDED
