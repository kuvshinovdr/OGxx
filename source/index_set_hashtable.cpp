///  index_set_hashtable.cpp
/// This file defines ogxx::Index_set_hashtable: public ogxx::Index_set, public ogxx::Sized_iterable<Scalar_index>.
/// ChernyshevMV
#ifndef OGXX_INDEX_SET_HASHTABLE_CPP
#define OGXX_INDEX_SET_HASHTABLE_CPP

#include <ogxx/st_set.hpp>
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>
#include <unordered_set>

namespace ogxx{

    class Index_set_hashtable: public Index_set, public Sized_iterable<Scalar_index>{
    private:
        std::unordered_set<Scalar_index> unord_set;
    public:
        ~Index_set_hashtable() override {};
        auto contains(Scalar_index item) const noexcept -> bool override {
            return (unord_set.find(item) != unord_set.end());
        } 
        auto insert(Scalar_index item)
            -> bool override
        {
            return unord_set.insert(item).second;
        }
        auto erase(Scalar_index item)
            -> bool override
        {
            return unord_set.erase(item);
        }
        auto size() const noexcept
            -> Scalar_size override
        {
            return unord_set.size();
        }
        [[nodiscard]] auto iterate() const -> Basic_iterator_uptr<Scalar_index> override {
            return new_stl_iterator(unord_set);
        }

        [[nodiscard]] auto is_empty() const noexcept
        -> bool override {
              return unord_set.empty();
        }
    };
}
#endif