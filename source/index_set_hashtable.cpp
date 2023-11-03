///  stl_iterator.hpp
/// This file defines the Stl_iterator class, which provides an iterator for standard C++ containers.
/// ChernyshevMV
#ifndef OGXX_INDEX_SET_HASHTABLE_CPP
#define OGXX_INDEX_SET_HASHTABLE_CPP

#include <ogxx/st_set.hpp>
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>
#include <unordered_set>
#include <iostream>

namespace ogxx{
//template <typename Scalar_index>    
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
            throw std::logic_error("iterator not implemented");
        }

        [[nodiscard]] auto is_empty() const noexcept
        -> bool override {
              throw std::logic_error("is_empty not implemented");
        }
    };
}
int main()
{
    ogxx::Index_set_hashtable a;
    std::cout<<5;    
}
#endif