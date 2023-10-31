/// @file st_matrix.hpp
/// @brief St_matrix interface, st_ stands for "simple type", i.e. a thing like int or double
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ST_MATRIX_HPP_INCLUDED
#define OGXX_ST_MATRIX_HPP_INCLUDED

#include "matrix.hpp"
#include "iterable.hpp"


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

  /// @brief Owning pointer to a read-only simple-type matrix object.
  /// @tparam ST item type
  template <typename ST>
  using St_matrix_const_uptr = std::unique_ptr<St_matrix<ST> const>;

  /// @brief Simple type matrix interface.
  /// Iterating the matrix means going through all its elements in row-major order.
  /// @tparam ST item type
  template <typename ST>
  class St_matrix 
    : public virtual Matrix_base
    , public virtual Sized_iterable<ST>
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
    /// @param value    the new value of the item
    /// @return the old value of the item
    virtual auto set(Matrix_index position, ST value)
      -> ST = 0;

    /// @brief Set a (row, col) item of the matrix.
    /// Throws std::out_of_range if position is out of range.
    /// @param row    the row index of the element
    /// @param col    the column index of the element
    /// @param value  the new value of the item
    /// @return the old value of the item
    auto set(Scalar_index row, Scalar_index col, ST value)
      -> ST { return set(Matrix_index{ row, col }, value); }

    /// @brief Assigns all elements of the matrix the same value.
    /// @param value the value to be assigned, the default one (ST{}) if not passed explicitly
    virtual void fill(ST value = ST{}) noexcept = 0;

    /// @brief Go through all elements in a row.
    /// @param row index of the row to iterate through
    /// @return an iterator object
    [[nodiscard]] virtual auto iterate_row(Scalar_index row) const
      -> Basic_iterator_uptr<ST> = 0;

    /// @brief Go through all elements in a column.
    /// @param row index of the column to iterate through
    /// @return an iterator object
    [[nodiscard]] virtual auto iterate_col(Scalar_index col) const
      -> Basic_iterator_uptr<ST> = 0;

    /// @brief Read a window in this matrix as a separate matrix.
    /// @param window the region to look through
    /// @return constant ST matrix object
    [[nodiscard]] virtual auto view(Matrix_window window) const
      -> St_matrix_const_uptr<ST> = 0;

    /// @brief Read or write a window in this matrix as a separate matrix.
    /// @param window the region to look through
    /// @return read-write ST matrix object
    [[nodiscard]] virtual auto view(Matrix_window window)
      -> St_matrix_uptr<ST> = 0;

    /// @brief Make a copy of a window of the matrix into a separate matrix object.
    /// @param window the region to copy
    /// @return a separate ST matrix object
    [[nodiscard]] virtual auto copy(Matrix_window window)
      -> St_matrix_uptr<ST> = 0;

    /// @brief Make a copy of the full matrix.
    /// @return a clone of this matrix
    [[nodiscard]] auto copy() const
      -> St_matrix_uptr<ST>
    {
      return copy(Matrix_window::main(shape()));
    }
  };


  /// @brief Integer matrix interface.
  using Int_matrix = St_matrix<Int>;

  /// @brief Integer matrix owning pointer.
  using Int_matrix_uptr = St_matrix_uptr<Int>;

  /// @brief Read-only integer matrix owning pointer.
  using Int_matrix_const_uptr = St_matrix_const_uptr<Int>;

  /// @brief Floating point matrix interface.
  using Float_matrix = St_matrix<Float>;

  /// @brief Floating point matrix owning pointer.
  using Float_matrix_uptr = St_matrix_uptr<Float>;

  /// @brief Read-only floating point matrix owning pointer.
  using Float_matrix_const_uptr = St_matrix_const_uptr<Float>;

}

#endif//OGXX_ST_MATRIX_HPP_INCLUDED
