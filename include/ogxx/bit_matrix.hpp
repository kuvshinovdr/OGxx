/// @file bit_matrix.hpp
/// @brief Bit_matrix interface
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_BIT_MATRIX_HPP_INCLUDED
#define OGXX_BIT_MATRIX_HPP_INCLUDED

#include <ogxx/matrix.hpp>
#include <ogxx/graph_view.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  class Bit_matrix;

  /// @brief Owning pointer to a bit matrix object.
  using Bit_matrix_uptr = std::unique_ptr<Bit_matrix>;

  /// @brief Owning pointer to a read-only bit matrix object.
  using Bit_matrix_const_uptr = std::unique_ptr<Bit_matrix const>;

  /// @brief Bit matrix interface.
  /// Iterating the matrix means going through all its elements in row-major order.
  class Bit_matrix
    : public virtual Matrix_base
    , public virtual Sized_iterable<bool>
  {
  public:
    /// @brief Get the item of a matrix at the given position.
    /// @param position matrix item position (row, column)
    /// @return true or false according the bit value, false if position is out of range
    [[nodiscard]] virtual auto get(Matrix_index position) const noexcept
      -> bool = 0;

    /// @brief Get the item of a matrix at the given position (row, col).
    /// @param row the first index of the item (zero-based)
    /// @param col the second index of the item (zero-based)
    /// @return true or false according the bit value, false if position is out of range
    [[nodiscard]] auto get(Scalar_index row, Scalar_index col) const noexcept
      -> bool { return get(Matrix_index{ row, col }); }

    /// @brief Set an item of the matrix.
    /// Throws std::out_of_range if position is out of range.
    /// @param position matrix item position (row, column)
    /// @param value true (by default) or false, the new value
    /// @return the old value of the set bit
    virtual auto set(Matrix_index position, bool value = true)
      -> bool = 0;

    /// Equivalent to set(Matrix_index{row, col}, value).
    auto set(Scalar_index row, Scalar_index col, bool value = true)
      -> bool { return set(Matrix_index{row, col}, value); }

    /// @brief A shortcut for set(position, false).
    /// @param position matrix item position (row, column)
    /// @return the old value of the set bit 
    auto reset(Matrix_index position)
      -> bool { return set(position, false); }

    /// Equivalent to reset(Matrix_index{row, col}).
    auto reset(Scalar_index row, Scalar_index col)
      -> bool { return reset(Matrix_index{ row, col }); }

    /// @brief Effectively returns set(position, !operator()(position)) but in one virtual call.
    /// Throws std::out_of_range if position is out of range.
    /// @param position matrix item position (row, column)
    /// @return the old value of the flipped bit
    virtual auto flip(Matrix_index position)
      -> bool = 0;

    /// Equivalent to flip(Matrix_index{ row, col }).
    auto flip(Scalar_index row, Scalar_index col)
      -> bool { return flip(Matrix_index{ row, col }); }

    /// @brief Assigns all elements of the matrix the same value.
    /// @param value the value to be assigned
    virtual void fill(bool value) = 0;

    /// @brief Go through all elements in a row.
    /// @param row index of the row to iterate through
    /// @return Boolean iterator
    [[nodiscard]] virtual auto iterate_row(Scalar_index row) const
      -> Basic_iterator_uptr<bool> = 0;

    /// @brief Go through all elements in a column.
    /// @param row index of the column to iterate through
    /// @return Boolean iterator
    [[nodiscard]] virtual auto iterate_col(Scalar_index col) const
      -> Basic_iterator_uptr<bool> = 0;

    /// @brief Read a window in this matrix as a separate bit matrix.
    /// @param window the region to look through
    /// @return constant bit matrix object
    [[nodiscard]] virtual auto view(Matrix_window window) const
      -> Bit_matrix_const_uptr = 0;

    /// @brief Read or write a window in this matrix as a separate bit matrix.
    /// @param window the region to look through
    /// @return read-write bit matrix object
    [[nodiscard]] virtual auto view(Matrix_window window)
      -> Bit_matrix_uptr = 0;
  
    /// @brief Make a copy of a window of the matrix into a separate bit matrix object.
    /// @param window the region to copy
    /// @return a separate bit matrix object
    [[nodiscard]] virtual auto copy(Matrix_window window) const
      -> Bit_matrix_uptr = 0;

    /// @brief Make a copy of the full matrix.
    /// @return a clone of this matrix
    [[nodiscard]] auto copy() const
      -> Bit_matrix_uptr { return copy(Matrix_window::main(shape())); }
  };


  /// Directed graph facilities.
  namespace directed
  {

    /// @brief Create a read-only graph view for an adjacency matrix of a directed graph.
    /// @param am viewed adjacency matrix (square), must live while the result graph view is being used
    /// @return a graph view read-only object
    [[nodiscard]] auto graph_view(Bit_matrix const& am)
      -> Graph_view_const_uptr;

    /// @brief Create a read-write graph view for an adjacency matrix of a directed graph.
    /// @param am viewed adjacency matrix (square), must live while the result graph view is being used
    /// @return a graph view read-write object
    [[nodiscard]] auto graph_view(Bit_matrix& am)
      -> Graph_view_uptr;

  }

  /// Undirected graph facilities.
  namespace undirected
  {

    /// @brief Create a read-only graph view for an adjacency matrix of an undirected graph.
    /// @param el viewed adjacency matrix (square symmetric), must live while the result graph view is being used
    /// @return a graph view read-only object
    [[nodiscard]] auto graph_view(Bit_matrix const& am)
      -> Graph_view_const_uptr;

    /// @brief Create a read-write graph view for an adjacency matrix of an undirected graph.
    /// @param el viewed adjacency matrix (square symmetric), must live while the result graph view is being used
    /// @return a graph view read-write object
    [[nodiscard]] auto graph_view(Bit_matrix& am)
      -> Graph_view_uptr;

  }

}

#endif//OGXX_BIT_MATRIX_HPP_INCLUDED
