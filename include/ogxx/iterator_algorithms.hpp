/// @file iterator_algorithms.hpp
/// @brief Helper functions to work with iterators inspired by STL algorithm header.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru, Chaplygin M.D.
#ifndef OGXX_ITERATOR_ALGORITHMS_HPP_INCLUDED
#define OGXX_ITERATOR_ALGORITHMS_HPP_INCLUDED

#include <ogxx/iterator.hpp>


/// Root namespace of the OGxx library.
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
    if (iterator)
    {
      for (Item item; iterator->next(item);)
        action(item);
    }
    return action;
  }


  /// @brief Skip the given quantity of items in an iterator object (just calls next() n times).
  /// @tparam Item    the type of an item
  /// @param iterator iterator object being fast forwarded
  /// @param n        how many items to skip
  /// @return false if the end of the sequence has been met before n items could have been skipped, true if n items have been skipped successfully
  template <typename Item>
  auto skip_n(Basic_iterator_uptr<Item>& iterator, Scalar_index n)
    -> bool
  {
    if (!iterator)
      return false;

    while (n-- != 0)
      if (Item item; !iterator->next(item))
        return false;
    return true;
  }

  // skip_while, skip_until...


  /// @brief Count how many times an item occurs in a sequence represented by an iterator.
  /// @tparam Item    sequence item type
  /// @param iterator object representing the sequence
  /// @param item     the value being counted
  /// @return         how many times the item occurs in the sequence 
  template <typename Item>
  auto count(Basic_iterator_uptr<Item> const iterator, Item item)
    -> Scalar_size
  {
    Scalar_size result = 0;
    if (iterator)
    {
      for (Item _item; iterator->next(_item);)
        result += _item == item;
    }
    return result;
  }


  /// @brief Count how many times an item satysfying the predicate occurs in a sequence represented by an iterator.
  /// @tparam Item    sequence item type
  /// @tparam Pred    predicate type
  /// @param iterator object representing the sequence
  /// @param pred     object representing the predicate
  /// @return         how many times the item occurs satysfying the predicate in the sequence 
  template <typename Item, typename Pred>
  auto count_if(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> Scalar_size
  {
    Scalar_size result = 0;
    
    if (iterator)
    {
      for (Item item; iterator->next(item);)
        if (pred(item))
          ++result;
    }

    return result;
  }


  /// @brief Find an item by its value in the sequence
  /// @tparam Item    sequence item type
  /// @param iterator object representing the sequence
  /// @param item     the target value
  /// @return         pair: a position of target value(length of the sequence, if target value isn't found) in the sequence
  /// and iterator of the sequence, starts with the next element after the target value, if its found
  template <typename Item>
  auto find(Basic_iterator_uptr<Item> iterator, Item item)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    
    if (iterator)
    {
      for (Item _item; iterator->next(_item) && !(_item == item);)
        ++result;
    }

    return { result, std::move(iterator) };
  }


  /// @brief Find the first item in a sequence that satysfying a predicate.
  /// @tparam Item    sequence item type
  /// @tparam Pred    predicate type
  /// @param iterator object representing the sequence
  /// @param pred     object representing the predicate
  /// @return         pair: a position of target value(length of the sequence, if target value isn't found) in the sequence
  /// and iterator of the sequence, starts with the next element after the target value, if its found
  template <typename Item, typename Pred>
  auto find_if(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    
    if (iterator)
    {
      for (Item item; iterator->next(item) && !pred(item);)
        ++result;
    }

    return { result, std::move(iterator) };
  }


  /// @brief Find the first element in a sequence that isn't equal to an item.
  /// @tparam Item    sequence item type
  /// @param iterator object representing the sequence
  /// @param item     the copmared element
  /// @return         pair: a position of the first element in the sequence that isn't equal an item(length of the sequence, if target value isn't found)
  /// and iterator of the sequence, starts with the next element after the found element, if its found
  template <typename Item>
  auto find_not(Basic_iterator_uptr<Item> iterator, Item item)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    
    if (iterator)
    {
      for (Item _item; iterator->next(_item) && _item == item;)
        ++result;
    }

    return { result, std::move(iterator) };
  }


  /// @brief Find the first item in the sequence doesn't satysfy the predicate.
  /// @tparam Item    sequence item type
  /// @tparam Pred    predicate type
  /// @param iterator object representing the sequence
  /// @param pred     object representing the predicate
  /// @return         pair: a position of the first element in the sequence that doesn't satysfy the predicate(length of the sequence, if target value isn't found)
  /// and iterator of the sequence, starts with the next element after the the found element, if its found
  template <typename Item, typename Pred>
  auto find_if_not(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> std::pair<Scalar_index, Basic_iterator_uptr<Item>>
  {
    Scalar_index result = 0;
    
    if (iterator)
    {
      for (Item item; iterator->next(item) && pred(item);)
        ++result;
    }

    return { result, std::move(iterator) };
  }


  /// @brief Ñhecks whether each element of a sequence satisfies the given predicate.
  /// @tparam Item    sequence item type
  /// @tparam Pred    predicate type
  /// @param iterator object representing the sequence
  /// @param pred     object representing the predicate
  /// @return true if all elements of the sequence satisfy the given predicate, false otherwise 
  template <typename Item, typename Pred>
  auto all_of(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> bool
  {
    if (iterator)
    {
      for (Item item; iterator->next(item);)
        if (!pred(item))
          return false;
    }

    return true;
  }


  /// @brief Ñhecks if at least one element of a sequence satisfies the given predicate.
  /// @tparam Item    sequence item type
  /// @tparam Pred    predicate type
  /// @param iterator object representing the sequence
  /// @param pred     object representing the predicate
  /// @return true if at least one element of the sequence satisfy the given predicate, false otherwise 
  template <typename Item, typename Pred>
  auto any_of(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> bool
  {
    if (iterator)
    {
      for (Item item; iterator->next(item);)
        if (pred(item))
          return true;
    }

    return false;
  }


  /// @brief Ñhecks that all elements of the sequence don't satisfy the given predicate.
  /// @tparam Item    sequence item type
  /// @tparam Pred    predicate type
  /// @param iterator object representing the sequence
  /// @param pred     object representing the predicate
  /// @return true if all elements of the sequence don't satisfy the given predicate, false otherwise 
  template <typename Item, typename Pred>
  auto none_of(Basic_iterator_uptr<Item> iterator, Pred&& pred)
    -> bool
  {
    return !ogxx::any_of(std::move(iterator), std::forward<Pred>(pred));
  }

  /// @brief Ñhecks whether two sequences are equal.
  /// @tparam Item1   the first sequence item type
  /// @tparam Item2   the second sequence item type
  /// @tparam Compare comparator type
  /// @param it1      object representing the first sequence, if null equal throws invalid_argument
  /// @param it2      object representing the second sequence, if null equal throws invalid_argument
  /// @param compare  object representing the comaprator
  /// @return true if if the sequences are equal element by element, false otherwise
  template <typename Item1, typename Item2, typename Compare>
  auto equal(Basic_iterator_uptr<Item1> it1, Basic_iterator_uptr<Item2> it2, Compare&& compare)
    -> bool
  {
    if (!it1)
      throw std::invalid_argument("ogxx::equal: it1 is null");
    if (!it2)
      throw std::invalid_argument("ogxx::equal: it2 is null");

    Item1 item1;
    Item2 item2;
    
    for (;;)
    {
      bool const
        got1 = it1->next(item1),
        got2 = it2->next(item2);
      if (got1 != got2)
        return false;
      if (!got1) // got1 == got2
        return true;
      if (!compare(item1, item2))
        return false;       
    }
  }

  
  /// @brief The same as 'equal()', but comparator is '=='
  template <typename Item1, typename Item2>
  auto equal(Basic_iterator_uptr<Item1> it1, Basic_iterator_uptr<Item2> it2)
    -> bool
  {
    return ogxx::equal(std::move(it1), std::move(it2), 
      [](Item1 item1, Item2 item2) { return item1 == item2; });
  }


  /// @brief Accumulates the sum of all elements.
  /// @tparam Item     sequence item type
  /// @tparam Accum    the type of an object accumulating the sum of elements
  /// @param iterator  object representing the sequence
  /// @param accum     an object accumulating the sum of elements
  /// @return an object that has accumulated the sum of elements
  template <typename Item, typename Accum>
  auto accumulate(Basic_iterator_uptr<Item> iterator, Accum accum)
    -> Accum
  {
    if (iterator)
    {
      for (Item item; iterator->next(item);)
        accum += item;
    }

    return accum;
  }



  /// @brief The same as 'accumulate', but instead of '+', it uses the union functor
  template <typename Item, typename Accum, typename Combine>
  auto accumulate(Basic_iterator_uptr<Item> iterator, Accum accum, Combine&& combine)
    -> Accum
  {
    if (iterator)
    {
      for (Item item; iterator->next(item);)
        accum = combine(accum, item);
    }

    return accum;
  }


  /// @brief Inner product of two sequences represented by iterators.
  /// @tparam Item1     the first sequence item type
  /// @tparam Item2     the second sequence item type
  /// @tparam Accum     the type of the object accumulating the result sum
  /// @tparam Add       the type of additional functor
  /// @tparam Multiply  the type of multiplying functor
  /// @param it1        object representing the first sequence, if null inner_product throws invalid_argument
  /// @param it2        object representing the second sequence, if null inner_product throws invalid_argument
  /// @param accum      the object accumulating the result sum
  /// @param add        the additional functor
  /// @param multiply   the multiplying functor
  template <typename Item1, typename Item2, typename Accum, typename Add, typename Multiply>
  auto inner_product(
      Basic_iterator_uptr<Item1> it1,
      Basic_iterator_uptr<Item2> it2,
      Accum accum,
      Add&& add,
      Multiply&& multiply
    ) -> Accum
  {
    if (!it1)
      throw std::invalid_argument("ogxx::inner_product: it1 is null");
    if (!it2)
      throw std::invalid_argument("ogxx::inner_product: it2 is null");

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


  /// @brief The same as 'ogxx::inner_product', but the add functor is '+'.
  template <typename Item1, typename Item2, typename Accum, typename Multiply>
  auto inner_product(
      Basic_iterator_uptr<Item1> it1,
      Basic_iterator_uptr<Item2> it2,
      Accum accum,
      Multiply&& multiply
    ) -> Accum
  {
    return ogxx::inner_product(std::move(it1), std::move(it2), accum,
      [](Accum a, auto b) { return a + b; }, std::forward<Multiply>(multiply));
  }


  /// @brief The same as 'ogxx::inner_product', but the add functor is '+' and the multiply functor is '*'.
  template <typename Item1, typename Item2, typename Accum>
  auto inner_product(
      Basic_iterator_uptr<Item1> it1,
      Basic_iterator_uptr<Item2> it2,
      Accum accum
    ) -> Accum
  {
    return ogxx::inner_product(std::move(it1), std::move(it2), accum,
      [](Accum a, auto  b) { return a + b; },
      [](Item1 a, Item2 b) { return a * b; });
  }

}

#endif//OGXX_ITERATOR_ALGORITHMS_HPP_INCLUDED
