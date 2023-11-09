/// doc-comment
#include <ogxx/iterable.hpp>

namespace ogxx
{
  
  template <typename Item>
  class Iterable_span
    : public ogxx::Indexed_iterable<Item>
  {
  public:
    Iterable_span() = default;

    Iterable_span(Item *begin, Item *end, Scalar_index stride = 1)
      : _begin(begin), _end(end), _stride(stride) {}

    [[nodiscard]] auto iterate() const
      -> Basic_iterator_uptr<See_by<Item>> override
    {
      // TODO
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
      
      if constexpr (std::is_pointer_v<See_by<Item>>)
        return ptr;
      else
        return *ptr; // only if See_by<Item> === Item
    }

    [[nodiscard]] auto set(Scalar_index index, Pass_by<Item> value)
      -> Pass_by<Item> override
    {
      // TODO
    }

  private:
    Item *_begin = nullptr;
    Item *_end   = nullptr;
    Scalar_index _stride = 1;
  };

}
