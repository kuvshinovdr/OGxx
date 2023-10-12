/// @file iterator.hpp
/// @brief Linear sequence iterator interfaces
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ITERATOR_HPP_INCLUDED
#define OGXX_ITERATOR_HPP_INCLUDED

#include "primitive_definitions.hpp"


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Generic iterator for traversing a sequence of items of a small easily-copyable or movable type.
  /// @tparam T small easily-copyable or movable type
  template <typename T>
  class Basic_iterator
  {
  public:
    virtual ~Basic_iterator() {}

    /// @brief Get the next item of the sequence.
    /// @param out_item the variable where to put the next item of the sequence if this item exists
    /// @return true if the item value was written to out_item, false if the sequence is empty
    virtual auto next(T& out_item) noexcept
      -> bool = 0;
  };

  /// @brief Iterating over a bit sequence.
  using Bit_iterator = Basic_iterator<bool>;

  /// @brief Iterating over an index sequence.
  using Index_iterator = Basic_iterator<Scalar_index>;

  /// @brief Iterating over an integer number sequence.
  using Int_iterator = Basic_iterator<Int>;

  /// @brief Iterating over a floating point number sequence.
  using Float_iterator = Basic_iterator<Float>;

}

#endif//OGXX_ITERATOR_HPP_INCLUDED
