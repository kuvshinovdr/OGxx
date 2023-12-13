/// @file iterable.hpp
/// @brief Iterable interfaces
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ITERABLE_HPP_INCLUDED
#define OGXX_ITERABLE_HPP_INCLUDED

#include <ogxx/primitive_definitions.hpp>
#include <ogxx/iterator.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Make a value-type to return from an iterator.
  /// @tparam Item type of items being iterated
  template <typename Item>
  using See_by =
    std::conditional_t<
      std::is_abstract_v<std::remove_cv_t<Item>>,
          Item*, Item>;

  /// @brief Make movable type to pass a value of Item (pass ownership).
  /// @tparam Item type of items being passed to a function or returned from a function
  template <typename Item>
  using Pass_by =
    std::conditional_t<
      std::is_abstract_v<std::remove_cv_t<Item>>,
          std::unique_ptr<Item>, Item>;


  /// @brief An interface for an object that can be iterated with an iterator.
  /// @tparam Item the type of the object items that can be iterated
  template <typename Item>
  class Iterable
  {
  public:
    virtual ~Iterable() {}

    /// @brief Organize an iteration by creating a new iterator for this iterable collection.
    /// @return an object of the iterator
    [[nodiscard]] virtual auto iterate() const
      -> Basic_iterator_uptr<See_by<Item>> = 0;

    /// @brief Check if this iterable range is actually empty.
    /// @return true if it is empty, false otherwise
    [[nodiscard]] virtual auto is_empty() const noexcept
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
    [[nodiscard]] virtual auto size() const noexcept
      -> Scalar_size = 0;
  };


  /// @brief Finally, the linear zero-based integer-indexed iterable collection.
  /// @tparam Item the type of the object items that can be iterated
  template <typename Item>
  class Indexed_iterable
    : public virtual Sized_iterable<Item>
  {
  public:
    /// @brief Get (see) an item by its index by value.
    /// @param index zero-based index < size()
    /// @return a copy or a view of the item at the given index, may throw or return some default value if index is out-of-range
    [[nodiscard]] virtual auto get(Scalar_index index) const
      -> See_by<Item> = 0;

    /// @brief Set an item at the specified index.
    /// @param index where to locate the item
    /// @param value which value to assign the item
    /// @return old value of the item (if it existed), may throw or resize and return some default value if index is out-of-range
    virtual auto set(Scalar_index index, Pass_by<Item> value)
      -> Pass_by<Item> = 0;
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
    virtual void put(Pass_by<Item> item) = 0;

    /// @brief Remove the last item and return it.
    /// @return the value removed, the function may return some default value or throw if the container is empty, but no UB please
    virtual auto take()
      -> Pass_by<Item> = 0;

    /// @brief Make this list empty.
    virtual void clear() = 0;
  };

  /// @brief A bag of scalar indices.
  using Index_bag = Bag<Scalar_index>;

  /// @brief An owning pointer to a bag of scalar indices.
  using Index_bag_uptr = std::unique_ptr<Index_bag>;


  /// @brief Generic container interface with inserts and erases and stores them in linear order as a list.
  /// @tparam Item container item type
  template <typename Item>
  class List
    : public virtual Indexed_iterable<Item>
    , public virtual Bag<Item>
  {
  public:
    /// @brief Insert an item at the given position moving all the following items one position up.
    /// Should throw on bad index.
    /// @param at    the position where to insert, insert(0, item) does prepend(item)
    /// @param item  the value to insert
    virtual void put(Scalar_index at, Pass_by<Item> item) = 0;

    /// @brief Remove the item from the given position and return it.
    /// @return the value removed, the function may return some default value or throw if the container is empty, but no UB please
    virtual auto take(Scalar_index from)
      -> Pass_by<Item> = 0;
  };

  /// @brief A list of scalar indices.
  using Index_list = List<Scalar_index>;

  /// @brief An owning pointer to a list of scalar indices.
  using Index_list_uptr = std::unique_ptr<Index_list>;

  /// @brief A list of 32-bit integers.
  using Int_list = List<Int>;

  /// @brief An owning pointer to a list of 32-bit integers.
  using Int_list_uptr = std::unique_ptr<Int>;

  /// @brief A list of floating point numbers.
  using Float_list = List<Float>;

  /// @brief An owning pointer to a list of floating point numbers.
  using Float_list_uptr = std::unique_ptr<Float_list>;

 template <typename Item>
  class DynArray
    : public virtual List<Item>
   {
   public:
   
   virtual auto new_index_dynarray() -> Index_list_uptr;
   virtual auto new_index_dynarray(Index_iterator_uptr) -> Index_list_uptr;
   
   virtual auto new_int_dynarray() -> Int_list_uptr;
   virtual auto new_int_dynarray(Float_iterator_uptr) -> Int_list_uptr;
   
   virtual auto new_float_dynarray() -> Float_list_uptr;
   virtual auto new_float_dynarray(Float_iterator_uptr) -> Float_list_uptr;

   };


}

#endif//OGXX_ITERABLE_HPP_INCLUDED
