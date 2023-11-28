/// @file iterator.hpp
/// @brief Linear sequence iterator interfaces
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ITERATOR_HPP_INCLUDED
#define OGXX_ITERATOR_HPP_INCLUDED

#include <ogxx/primitive_definitions.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Generic iterator for traversing a sequence of items of a small easily-copyable or movable type.
  /// @tparam Item small easily-copyable or movable type
  template <typename Item>
  class Basic_iterator
  {
  public:
    virtual ~Basic_iterator() {}

    /// @brief Get the next item of the sequence.
    /// Possible enumerating using this iterator may be done by the following loop:
    /// @code{.cpp}
    ///     for (Item val; iterator->next(val);)
    ///       do_something_with(val);
    /// @endcode
    /// @param out_item the variable where to put the next item of the sequence if this item exists
    /// @return true if the item value was written to out_item, false if the sequence is empty
    virtual auto next(Item& out_item) noexcept(std::is_nothrow_assignable_v<Item, Item>)
      -> bool = 0;

  protected:
    Basic_iterator& operator=(Basic_iterator const&) noexcept = default;
    Basic_iterator& operator=(Basic_iterator&&) noexcept      = default;
  };


  /// @brief An owning pointer to a basic iterator.
  /// @tparam Item basic iterator item type
  template <typename Item>
  using Basic_iterator_uptr = std::unique_ptr<Basic_iterator<Item>>;

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

  /// @brief Create a linear dense bit iterator returning bools.
  /// @param word
  /// @param firstbit
  /// @param endbit
  /// @param stride
  /// @return
  [[nodiscard]] auto new_dense_bit_iterator(
    unsigned const* word,
    size_t          firstbit,
    size_t          endbit,
    size_t          stride = 1) -> Bit_iterator_uptr;
}

#endif//OGXX_ITERATOR_HPP_INCLUDED
