/// @file iterable.hpp
/// @brief Iterable interfaces
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ITERABLE_HPP_INCLUDED
#define OGXX_ITERABLE_HPP_INCLUDED

#include "primitive_definitions.hpp"
#include "iterator.hpp"


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

  protected:
    Iterable& operator=(Iterable const&) noexcept = default;
    Iterable& operator=(Iterable&&) noexcept      = default;
  };


  /// @brief Not only iterable but we know in advance, how many items it contains.
  /// @tparam Item the type of the object items that can be iterated
  template <typename Item>
  class Sized_iterable : public Iterable<Item>
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
  class Indexed_iterable : public Sized_iterable<Item>
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

}

#endif//OGXX_ITERABLE_HPP_INCLUDED
