/// doc-comment
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>
#include <iterator>

namespace ogxx
{

  namespace
  {
    template <typename Item>
    class Iterable_span_iterator
    {
    public:
      Iterable_span_iterator() noexcept = default;
      Iterable_span_iterator(Pass_by<Item>* at, Scalar_index stride = 1)
        : _cur(at), _stride(stride) {}

      auto operator*() const noexcept
        -> Pass_by<Item>& { return *_cur; }

      auto operator->() const noexcept
        -> Pass_by<Item>* { return _cur; }

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
      Pass_by<Item>* _cur    = nullptr;
      Scalar_index   _stride = 1;
    };

    inline auto operator!=(
      Iterable_span_iterator<Item> a,
      Iterable_span_iterator<Item> b) noexcept
      -> bool { return !(a == b); }
  }

  
  template <typename Item>
  class Iterable_span
    : public ogxx::Indexed_iterable<Item>
  {
  public:
    Iterable_span() = default;

    Iterable_span(
      Pass_by<Item> *begin, 
      Pass_by<Item> *end, 
      Scalar_index stride = 1)
      : _begin(begin), _end(end), _stride(stride) {}

    [[nodiscard]] auto iterate() const
      -> Basic_iterator_uptr<See_by<Item>> override
    {
      return new_stl_iterator(
        Iterable_span_iterator(_begin, _stride),
        Iterable_span_iterator(_end, _stride));
    }

    [[nodiscard]] auto is_empty() const noexcept
      -> bool override
    {
      return _begin == _end;
    }

    [[nodiscard]] auto size() const noexcept
      -> Scalar_size override
    {
      return ((_end - _begin) + (_stride - 1)) / _stride;
    }

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

    [[nodiscard]] auto set(Scalar_index index, Pass_by<Item> value)
      -> Pass_by<Item> override
    {
      auto const ptr = _begin + _stride * index;
      if (!is_within(ptr, _begin, _end))
        throw std::out_of_range("Iterable_span::get: invalid index");

      auto const old = move(*ptr);
      ptr = move(*value);

      return *old;
      // TODO
      // save old *ptr (old = move(*ptr))
      // move value into *ptr
      // return old
    }

  private:
    Pass_by<Item> *_begin = nullptr;
    Pass_by<Item> *_end   = nullptr;
    Scalar_index _stride  = 1;
  };

}
