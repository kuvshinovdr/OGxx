/// @file iterator_algorithms.hpp
/// @brief Helper functions to work with iterators inspired by STL algorithm header.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ITERATOR_ALGORITHMS_HPP_INCLUDED
#define OGXX_ITERATOR_ALGORITHMS_HPP_INCLUDED

#include "iterator.hpp"


namespace ogxx
{

  /// @brief Call a function for each item in a sequence.
  /// @tparam Item    type of iterated values
  /// @tparam Action  function object type accepting Item
  /// @param iterator collection access object
  /// @param action   function object called for each item provided by the iterator
  /// @return action object 
  template <typename Item, typename Action>
  auto for_each(Basic_iterator_uptr<Item> iterator, Action&& action)
    -> Action
  {
    for (Item item; iterator->next(item);)
      action(item);
    return action;
  }


  template <typename Item>
  auto count(Basic_iterator_uptr<Item> iterator, Item item)
    -> Scalar_size
  {
    Scalar_size result = 0;
    for (Item _item; iterator->next(_item);)
      result += _item == item;
    return result;
  }


  template <typename Item, typename Pred>
  auto count_if(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> Scalar_size
  {
    Scalar_size result = 0;
    for (Item item; iterator->next(item);)
      if (pred(item)
        ++result;
    return result;
  }


  template <typename Item>
  auto find(Basic_iterator_uptr<Item> iterator, Item item)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    for (Item _item; iterator->next(_item) && !(_item == item);)
      ++result;
    return { result, iterator };
  }


  template <typename Item, typename Pred>
  auto find_if(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    for (Item item; iterator->next(item) && !pred(item);)
      ++result;
    return { result, iterator };
  }


  template <typename Item>
  auto find_not(Basic_iterator_uptr<Item> iterator, Item item)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    for (Item _item; iterator->next(_item) && _item == item;)
      ++result;
    return { result, iterator };
  }


  template <typename Item, typename Pred>
  auto find_if_not(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    for (Item item; iterator->next(item) && pred(item);)
      ++result;
    return { result, iterator };
  }


  template <typename Item, typename Pred>
  auto all_of(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> bool
  {
    for (Item item; iterator->next(item);)
      if (!pred(item))
        return false;
    return true;
  }


  template <typename Item, typename Pred>
  auto any_of(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> bool
  {
    for (Item item; iterator->next(item);)
      if (pred(item))
        return true;
    return false;
  }


  template <typename Item, typename Pred>
  auto none_of(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> bool
  {
    return !any_of(iterator, std::forward<Pred>(pred));
  }


  template <typename Item1, typename Item2, typename Compare>
  auto equal(Basic_iterator_uptr<Item1> it1, Basic_iterator_uptr<Item2> it2, Compare&& compare)
    -> bool
  {
    Item1 item1;
    Item2 item2;
    
    for (;;)
    {
      bool const got1 = it1->next(item1);
      bool const got2 = it2->next(item2);
      if (got1 != got2)
        return false;
      if (!got1)
        return true;
      if (!compare(item1, item2))
        return false;
    }
  }


  template <typename Item1, typename Item2, typename Compare>
  auto equal(Basic_iterator_uptr<Item1> it1, Basic_iterator_uptr<Item2> it2)
    -> bool
  {
    return equal(std::move(it1), std::move(it2), 
      [](Item1 item1, Item2 item2) { return item1 == item2; });
  }


  template <typename Item, typename Accum>
  auto accumulate(Basic_iterator_uptr<Item> iterator, Accum accum)
    -> Accum
  {
    for (Item item; iterator->next(item);)
      accum += item;
    return accum;
  }


  template <typename Item, typename Accum, typename Combine>
  auto accumulate(Basic_iterator_uptr<Item> iterator, Accum accum, Combine&& combine)
    -> Accum
  {
    for (Item item; iterator->next(item);)
      accum = combine(accum, item);
    return accum;
  }


  template <typename Item1, typename Item2, typename Accum, typename Add, typename Multiply>
  auto inner_product(
      Basic_iterator_uptr<Item1> it1,
      Basic_iterator_uptr<Item2> it2,
      Accum accum,
      Add&& add,
      Multiply&& multiply
    ) -> Accum
  {
    Item1 item1;
    Item2 item2;

    for (;;)
    {
      bool const got1 = it1->next(item1);
      bool const got2 = it2->next(item2);
      if (!(got1 && got2))
        return accum;
      accum = add(accum, multiply(item1, item2));
    }
  }


  template <typename Item1, typename Item2, typename Accum, typename Multiply>
  auto inner_product(
      Basic_iterator_uptr<Item1> it1,
      Basic_iterator_uptr<Item2> it2,
      Accum accum,
      Multiply&& multiply
    ) -> Accum
  {
    return inner_product(std::move(it1), std::move(it2), accum,
      [](Accum a, auto b) { return a + b; }, std::forward<Multiply>(multiply));
  }


  template <typename Item1, typename Item2, typename Accum>
  auto inner_product(
      Basic_iterator_uptr<Item1> it1,
      Basic_iterator_uptr<Item2> it2,
      Accum accum
    ) -> Accum
  {
    return inner_product(std::move(it1), std::move(it2), accum,
      [](Accum a, auto  b) { return a + b; },
      [](Item1 a, Item2 b) { return a * b; });
  }

}

#endif//OGXX_ITERATOR_ALGORITHMS_HPP_INCLUDED
