/// @file stl_iterator.hpp
/// @brief This file defines the Stl_iterator class, which provides an iterator for standard C++ containers.
/// @author ChernyshevMV, Kuvshinov D.R.
#ifndef OGXX_STL_ITERATOR_HPP_INCLUDED
#define OGXX_STL_ITERATOR_HPP_INCLUDED

#include <iterator>
#include <ogxx/iterator.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief STL iterator wrapper providing ogxx::Basic_iterator interface.
  /// @tparam T     item type
  /// @tparam It    iterator type
  /// @tparam Sent  sentinel type
  template <typename T, typename It, typename Sent = It>
  class Stl_iterator 
    : public Basic_iterator<T>
  {
  public:
    /// @brief Default initialize iterators.
    Stl_iterator()
      : current{}, end{} {}

    /// @brief Initialize by iterator-sentinel (end iterator) pair.
    /// @param begin  the beginning of a range
    /// @param end    the end of a range
    Stl_iterator(It begin, Sent end) 
      : current(begin), end(end) {}   
  
    /// @brief Initialize by a range (needs C++20).
    /// @tparam Range type of the range
    /// @param range  reference to a range
    template <typename Range>
    Stl_iterator(Range&& range)
      : Stl_iterator(std::ranges::begin(range), std::ranges::end(range)) {}

    /// @brief Get the next item of the sequence.
    /// @param out_item where to put the value of the next item (assigns a variable through the reference)
    /// @return true if out_item has been assigned, false otherwise
    auto next(T& out_item) noexcept
      -> bool              override
    {
      if (current == end) 
        return false;
      
      out_item = *current;
      ++current;
      
      return true;
    }

  private:
    It    current;
    Sent  end;
  };


  /// @brief Create an Stl_iterator object for the given begin, end pair.
  template <typename It, typename Sent>
  auto new_stl_iterator(It begin, Sent end)
    -> Basic_iterator_uptr<std::iter_value_t<It>>
  {
    using Iterator = Stl_iterator<std::iter_value_t<It>, It, Sent>;
    return std::make_unique<Iterator>(begin, end);
  }


  /// @brief Create an Stl_iterator object iterating over the given range.
  template <typename Range>
  auto new_stl_iterator(Range&& range)
    -> Basic_iterator_uptr<std::ranges::range_value_t<Range>>
  {
    using Iterator = Stl_iterator<
      std::ranges::range_value_t<Range>, 
      std::ranges::iterator_t<Range>,
      std::ranges::sentinel_t<Range>>;

    return std::make_unique<Iterator>(std::forward<Range>(range));
  }

}

#endif//OGXX_STL_ITERATOR_HPP_INCLUDED
