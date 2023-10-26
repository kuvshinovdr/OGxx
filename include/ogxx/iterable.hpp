/// @file iterable.hpp
/// @brief Iterable interfaces
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ITERABLE_HPP_INCLUDED
#define OGXX_ITERABLE_HPP_INCLUDED

#include "primitive_definitions.hpp"
#include "iterator.hpp"


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief An interface for an object that can be iterated with an iterator.
  /// @tparam Item the type of the object items that can be iterated
  template <typename Item>
  class Iterable
  {
  public:
    virtual ~Iterable() {}

    /// @brief Organize an iteration by creating a new iterator for this iterable collection.
    /// @return an object of the iterator
    virtual auto iterate() const
      -> Basic_iterator_uptr<Item> = 0;

    /// @brief Check if this iterable range is actually empty.
    /// @return true if it is empty, false otherwise
    virtual auto is_empty() const noexcept
      -> bool = 0;

  protected:
    Iterable& operator=(Iterable const&) noexcept = default;
    Iterable& operator=(Iterable&&) noexcept      = default;
  };


  /// @brief Not only iterable but we know in advance, how many items it contains.
  /// @tparam Item the type of the object items that can be iterated
  template <typename Item>
  class Sized_iterable
    : public virtual Iterable<Item>
  {
  public:
    /// @brief Get the size of the collection.
    /// @return how many items will we iterate through
    virtual auto size() const noexcept
      -> Scalar_size = 0;
  };


  /// @brief Finally, the linear zero-based integer-indexed iterable collection.
  /// @tparam Item the type of the object items that can be iterated
  template <typename Item>
  class Indexed_iterable
    : public virtual Sized_iterable<Item>
  {
  public:
    /// @brief Get an item by its index by value.
    /// @param index zero-based index < size()
    /// @return a copy of the item at the given index, may throw or return some default value if index is out-of-range
    virtual auto get(Scalar_index index) const
      -> Item = 0;

    /// @brief Set an item at the specified index.
    /// @param index where to locate the item
    /// @param value which value to assign the item
    /// @return old value of the item (if it existed), may throw or resize and return some default value if index is out-of-range
    virtual auto set(Scalar_index index, Item value)
      -> Item = 0;
  };


  /// @brief Generic container interface with inserts and erases but no fixed ordering of items.
  /// @tparam Item container item type
  template <typename Item>
  class Bag
    : public virtual Sized_iterable<Item>
  {
  public:
    /// @brief Append item to the end of the container (i.e. push_back).
    /// @param item the value to append
    virtual void put(Item item) = 0;

    /// @brief Insert an item at the given position moving all the following items one position up.
    /// Should throw on bad index.
    /// @param at    the position where to insert, insert(0, item) does prepend(item)
    /// @param item  the value to insert
    virtual void put(Scalar_index at, Item item) = 0;

    /// @brief Remove the last item and return it.
    /// @return the value removed, the function may return some default value or throw if the container is empty, but no UB please
    virtual auto take()
      -> Item = 0;

    /// @brief Remove the item from the given position and return it.
    /// @return the value removed, the function may return some default value or throw if the container is empty, but no UB please
    virtual auto take(Scalar_index from)
      -> Item = 0;

    /// @brief Make this list empty.
    virtual void clear() = 0;
  };


  /// @brief Generic container interface with inserts and erases and stores them in linear order as a list.
  /// @tparam Item container item type
  template <typename Item>
  class List
    : public Indexed_iterable<Item>
    , public Bag<Item>
  {};

}

#endif//OGXX_ITERABLE_HPP_INCLUDED
