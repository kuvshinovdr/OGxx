/// @file source/index_set_bitvector.hpp
/// @brief Index_set implemented via bit vector
/// @author Ivan I. Martynov <7martyn1>
#ifndef OGXX_INDEX_SET_BITVECTOR_HPP_INCLUDED
#define OGXX_INDEX_SET_BITVECTOR_HPP_INCLUDED

#include <ogxx/st_set.hpp>
#include <ogxx/iterable.hpp>

#include <vector>


namespace ogxx {
  class Index_set_bitvector 
    : public Index_set
    , public Sized_iterable<Scalar_index> {
    private:
      std::vector<bool> _bits;
      Scalar_size       _bit_count = 0;

    public:
      Index_set_bitvector() = default;
      explicit Index_set_bitvector(Index_iterator_uptr);

      bool contains(Scalar_index index) const noexcept override;
      bool insert(Scalar_index item) override;
      bool erase(Scalar_index item) override;

      Scalar_size size() const noexcept override {
        return _bit_count;
      }

      bool is_empty() const noexcept override {
        return _bit_count == 0;
      }

      auto iterate() const -> Index_iterator_uptr override;
  };

}

#endif//OGXX_INDEX_SET_BITVECTOR_HPP_INCLUDED
