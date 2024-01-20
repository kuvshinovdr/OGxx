/// @file source/iterable_span.hpp
/// @brief Iterable span iterator class
/// @author Klimentov A. D.
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>

#include <iterator>
#include <stdexcept>


namespace ogxx
{




  template <typename Item>
  class Iterable_span_iterator
  {
  public:
    using value_type      = Item;
    using pointer         = value_type*;
    using reference       = value_type&;
    using difference_type = std::ptrdiff_t;

    Iterable_span_iterator() noexcept = default;

    Iterable_span_iterator(pointer at, Scalar_index stride = 1)
      : _cur(at), _stride(stride) {}

    auto operator*() const noexcept
      -> reference { return *_cur; }

    auto operator->() const noexcept
      -> pointer { return _cur; }

    auto operator++() noexcept
      -> Iterable_span_iterator& 
    { 
      _cur += _stride;
      return *this;
    }

    auto operator++(int) noexcept
      -> Iterable_span_iterator
    {
      auto old = *this;
      ++*this;
      return old;
    }

    friend auto operator==(
      Iterable_span_iterator<Item> a, 
      Iterable_span_iterator<Item> b) noexcept
      -> bool { return a._cur == b._cur; }

  private:
    pointer      _cur    = nullptr;
    Scalar_index _stride = 1;
  };


  template <typename Item>
  inline auto operator!=(
    Iterable_span_iterator<Item> a,
    Iterable_span_iterator<Item> b) noexcept
    -> bool { return !(a == b); }


  /// @brief A wrapper for a contiguous span of data into Indexed_iterable interface.
  /// @tparam Item data type
  template <typename Item>
  class Iterable_span
    : public ogxx::Indexed_iterable<Item>
  {
  public:
    /// @brief Create an empty iterable span.
    Iterable_span() = default;

    /// @brief Create an iterable span using begin and end pointers (in STL manner).
    /// @param begin a pointer to the first member of a contiguous span of data in memory
    /// @param end   a pointer next after the last member of a contiguous span of data in memory
    Iterable_span(
      Pass_by<Item>* begin,
      Pass_by<Item>* end)
      : _begin(begin), _end(end) {}

    /// @brief Create an iterator object going through all elements of the span.
    [[nodiscard]] auto iterate() const
      -> Basic_iterator_uptr<See_by<Item>> override
    {
      return new_stl_iterator(_begin, _end);
    }

    /// @brief Check if the span is empty.
    [[nodiscard]] auto is_empty() const noexcept
      -> bool override
    {
      return _begin == _end;
    }

    /// @brief Get the quantity of items in the span.
    [[nodiscard]] auto size() const noexcept
      -> Scalar_size override
    {
      return _end - _begin;
    }

    /// @brief Get an item by its index, throws std::out_of_range on out of range.
    /// @param index zero-based item index
    /// @return the item at the given index
    [[nodiscard]] auto get(Scalar_index index) const
      -> See_by<Item> override
    {
      auto const ptr = _begin + index;
      if (!is_within(ptr, _begin, _end))
        throw std::out_of_range("Iterable_span::get: invalid index");

      if constexpr (std::is_pointer_v<See_by<Item>>) // abstract class
        return ptr->get();
      else // non-abstract
        return *ptr; // only if See_by<Item> === Item
    }

    /// @brief Set an item at the given index to the given value.
    /// @param index index of the item to set
    /// @param value new value of the item
    /// @return the old value of the set item
    [[nodiscard]] auto set(Scalar_index index, Pass_by<Item> value)
      -> Pass_by<Item> override
    {
      auto const ptr = _begin + index;
      if (!is_within(ptr, _begin, _end))
        throw std::out_of_range("Iterable_span::get: invalid index");

      auto old = std::move(*ptr);
      *ptr = std::move(value);
      return old;
    }

  private:
    Pass_by<Item>* _begin = nullptr;
    Pass_by<Item>* _end   = nullptr;
  };

  
  /// @brief A wrapper for a strided memory span of data into Indexed_iterable interface.
  /// @tparam Item data type
  template <typename Item>
  class Iterable_span_strided
    : public ogxx::Indexed_iterable<Item>
  {
  public:
    /// @brief Create an empty span.
    Iterable_span_strided() = default;

    /// @brief Create a span with the given begin and end pointers and stride value.
    /// @param begin  pointer to the first item
    /// @param end    pointer after the last item
    /// @param stride stride (in items) between items
    Iterable_span_strided(
      Pass_by<Item> *begin, 
      Pass_by<Item> *end, 
      Scalar_index stride = 1)
      : _begin(begin), _end(end), _stride(stride) {}

    /// @brief Create an iterator object going through all elements of the span.
    [[nodiscard]] auto iterate() const
      -> Basic_iterator_uptr<See_by<Item>> override
    {
      return new_stl_iterator(
        Iterable_span_iterator<Item>(_begin, _stride),
        Iterable_span_iterator<Item>(_end,   _stride));
    }

    /// @brief Check if the span is empty.
    [[nodiscard]] auto is_empty() const noexcept
      -> bool override
    {
      return _begin == _end;
    }

    /// @brief Get the quantity of items in the span.
    [[nodiscard]] auto size() const noexcept
      -> Scalar_size override
    {
      return ((_end - _begin) + (_stride - 1)) / _stride;
    }

    /// @brief Get an item by its index, throws std::out_of_range on out of range.
    /// @param index zero-based item index
    /// @return the item at the given index
    [[nodiscard]] auto get(Scalar_index index) const
      -> See_by<Item> override
    {
      auto const ptr = _begin + _stride * index;
      if (!is_within(ptr, _begin, _end))
        throw std::out_of_range("Iterable_span::get: invalid index");
      
      if constexpr (std::is_pointer_v<See_by<Item>>) // abstract class
        return ptr->get();
      else // non-abstract
        return *ptr; // only if See_by<Item> === Item
    }

    /// @brief Set an item at the given index to the given value.
    /// @param index index of the item to set
    /// @param value new value of the item
    /// @return the old value of the set item
    [[nodiscard]] auto set(Scalar_index index, Pass_by<Item> value)
      -> Pass_by<Item> override
    {
      auto const ptr = _begin + _stride * index;
      if (!is_within(ptr, _begin, _end))
        throw std::out_of_range("Iterable_span::get: invalid index");

      auto old = std::move(*ptr);
      *ptr = std::move(value);
      return old;
    }

  private:
    Pass_by<Item> *_begin = nullptr;
    Pass_by<Item> *_end   = nullptr;
    Scalar_index _stride  = 1;
  };


  /// @brief Create a new object of strided iterable span and present it as an Indexed_iterable object.
  /// @tparam Item  span item type
  /// @param begin  pointer to the first item
  /// @param end    pointer after the last item (do not forget about the stride)
  /// @param stride item stride in memory
  /// @return the iterable object wrapped into unique_ptr
  template <typename Item>
  auto new_iterable_span(
      Pass_by<Item>* begin,
      Pass_by<Item>* end,
      Scalar_index stride
  )
    -> Indexed_iterable_uptr<Item>
  {
    return std::make_unique<Iterable_span_strided<Item>>(begin, end, stride);
  }


  /// @brief Create a new object of contiguous memory iterable span and present it as an Indexed_iterable object.
  /// @tparam Item  span item type
  /// @param begin  pointer to the first item
  /// @param end    pointer after the last item
  /// @return the iterable object wrapped into unique_ptr
  template <typename Item>
  auto new_iterable_span(
    Pass_by<Item>* begin,
    Pass_by<Item>* end
  )
    -> Indexed_iterable_uptr<Item>
  {
    return std::make_unique<Iterable_span<Item>>(begin, end);
  }

}
