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

  /// @brief An owning pointer to a bit iterator object.
  using Bit_iterator_uptr = std::unique_ptr<Bit_iterator>;

  /// @brief Iterating over an index sequence.
  using Index_iterator = Basic_iterator<Scalar_index>;

  /// @brief An owning pointer to a index iterator object.
  using Index_iterator_uptr = std::unique_ptr<Index_iterator>;

  /// @brief Iterating over an integer number sequence.
  using Int_iterator = Basic_iterator<Int>;

  /// @brief An owning pointer to a integer iterator object.
  using Int_iterator_uptr = std::unique_ptr<Int_iterator>;

  /// @brief Iterating over a floating point number sequence.
  using Float_iterator = Basic_iterator<Float>;

  /// @brief An owning pointer to a float iterator object.
  using Float_iterator_uptr = std::unique_ptr<Float_iterator>;

}

#endif//OGXX_ITERATOR_HPP_INCLUDED
