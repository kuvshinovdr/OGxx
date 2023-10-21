/// @file st_matrix.hpp
/// @brief St_matrix interface, st_ stands for "simple type", i.e. a thing like int or double
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ST_MATRIX_HPP_INCLUDED
#define OGXX_ST_MATRIX_HPP_INCLUDED

#include "matrix.hpp"


/// Root namespace of the OGxx library.
namespace ogxx
{

  // Forward declaration.
  template <typename ST>
  class St_matrix;

  /// @brief Owning pointer to a simple-type matrix object.
  /// @tparam ST item type
  template <typename ST>
  using St_matrix_uptr = std::unique_ptr<St_matrix<ST>>;

  /// @brief Simple type matrix interface.
  /// @tparam ST item type
  template <typename ST>
  class St_matrix : public Matrix_base
  {
  public:
    /// @brief Get the item of a matrix at the given position.
    /// @param position matrix item position (row, column)
    /// @return the item value, default value (ST{}) if position is out of range
    [[nodiscard]] virtual auto get(Matrix_index position) const noexcept
      -> ST = 0;

    /// @brief Get the item of a matrix at the given position (row, col).
    /// @param row the first index of the item (zero-based)
    /// @param col the second index of the item (zero-based)
    /// @return true or false according the bit value, false if position is out of range
    [[nodiscard]] auto get(Scalar_index row, Scalar_index col) const noexcept
      -> ST { return get(Matrix_index{ row, col }); }

    /// @brief Set an item of the matrix.
    /// Throws std::out_of_range if position is out of range.
    /// @param position matrix item position (row, column)
    /// @param value the new value of the item
    /// @return the old value of the set item
    virtual auto set(Matrix_index position, ST value)
      -> ST = 0;

    /// @brief Assigns all elements of the matrix the same value.
    /// @param value the value to be assigned, the default one (ST{}) if not passed explicitly
    virtual void fill(ST value = ST{}) noexcept = 0;
  };

}

#endif//OGXX_ST_MATRIX_HPP_INCLUDED
