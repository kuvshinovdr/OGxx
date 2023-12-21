/// @file index_set_bitvector.cpp
/// @brief Defining interfaces for bitvector
/// @author Ivan I. Martynov <7martyn1>
#include "index_set_bitvector.hpp"
#include <stdexcept>
#include <algorithm>


namespace ogxx {

  Index_set_bitvector::Index_set_bitvector(Index_iterator_uptr ind)
  {
    std::vector<Scalar_index> buffer;
    for (Scalar_index value; ind->next(value);)
      buffer.push_back(value);

    if (buffer.empty())
      return;

    std::sort(buffer.begin(), buffer.end());
    buffer.erase(std::unique(buffer.begin(), buffer.end()), buffer.end());
    _bit_count = buffer.size();
    _bits.resize(*std::max_element(buffer.begin(), buffer.end()) + 1);
    for (Scalar_index item: buffer)
      _bits[item] = true;
  }


  bool Index_set_bitvector::contains(Scalar_index index) const noexcept {
    return static_cast<size_t>(index) < _bits.size() && _bits[index];
  }

  bool Index_set_bitvector::insert(Scalar_index item) {
    if (item < 0)
      throw std::invalid_argument("Index_set_bitvector::insert: negative items are not supported");

    if (static_cast<size_t>(item) >= _bits.size())
      _bits.resize(item + 1, false);
    else if (_bits[item])
      return false;

    _bits[item] = true;
    ++_bit_count;
    return true;
  }

  bool Index_set_bitvector::erase(Scalar_index item) {
    if (static_cast<size_t>(item) >= _bits.size())
      return false;

    if (_bits[item])
    {
      _bits[item] = false;
      --_bit_count;
      return true;
    }

    return false;
  }
    

  namespace {

    class Bit_index_iterator
      : public Index_iterator
    {
    public:
      Bit_index_iterator(std::vector<bool> const& bits)
        : _cur(bits.begin()), _end(bits.end()) {}

      bool next(Scalar_index& value) override
      {
        for (;; ++_cur, ++_item)
        {
          if (_cur == _end)
            return false;
          if (*_cur)
          {
            value = _item;
            ++_item;
            ++_cur;
            return true;
          }
        }
      }

    private:
      std::vector<bool>::const_iterator _cur, _end;
      Scalar_index _item = 0;
    };

  }


  auto Index_set_bitvector::iterate() const
    -> Index_iterator_uptr
  {
    return std::make_unique<Bit_index_iterator>(_bits);
  }


  auto new_index_set_bitvector()
    -> Index_set_uptr
  {
    return std::make_unique<Index_set_bitvector>();
  }

  auto new_index_set_bitvector(Index_iterator_uptr ind)
    -> Index_set_uptr
  {
    return std::make_unique<Index_set_bitvector>(std::move(ind));
  }

}
