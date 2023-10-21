/// @file st_set.hpp
/// @brief Simple type set interface. Set may be ordered or unordered.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
/// A set may be iterable as well. An indexed set should provide find method to map a key to its index.
#ifndef OGXX_ST_SET_HPP_INCLUDED
#define OGXX_ST_SET_HPP_INCLUDED

#include "primitive_definitions.hpp"


namespace ogxx
{

  /// @brief Possibly non-iterable set of simple type items.
  /// @tparam Item a simpe type
  template <typename Item>
  class St_set
  {
  public:
    virtual ~St_set() {}

    /// @brief Check if item belongs to the set.
    /// @param item the item to check
    /// @return true if item belongs to the set, false otherwise
    virtual auto contains(Item item) const noexcept
      -> bool = 0;

    /// @brief Insert an item into the set.
    /// @param item to be inserted
    /// @return true if the item was inserted, false if the item was already present in the set
    virtual auto insert(Item item)
      -> bool = 0;

    /// @brief Erase an item from the set.
    /// @param item to be erased
    /// @return true if the item was erased, false if the item was not present in the set
    virtual auto erase(Item item)
      -> bool = 0;

  protected:
    St_set& operator=(St_set const&) = default;
    St_set& operator=(St_set&&)      = default;
  };


  /// Owning pointer to an object of St_set of Item.
  template <typename Item>
  using St_set_uptr = std::unique_ptr<St_set<Item>>;

  /// Owning pointer to a read-only object of St_set of Item (only contains() method is available here).
  template <typename Item>
  using St_set_const_uptr = std::unique_ptr<St_set<Item> const>;

  /// @brief A set of integer indices.
  using Index_set = St_set<Scalar_index>;

  /// @brief An owning pointer to a set of integer indices.
  using Index_set_uptr = St_set_uptr<Scalar_index>;

  /// @brief An owning pointer to a read-only set of integer indices.
  using Index_set_const_uptr = St_set_const_uptr<Scalar_index>;

}

#endif//OGXX_ST_SET_HPP_INCLUDED
