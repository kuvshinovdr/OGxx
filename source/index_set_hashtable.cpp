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
template <typename Scalar_index>    
class Index_set_hashtable: public Index_set, public Sized_iterable<Scalar_index>
{
    private:
        std::unordered_set<Scalar_index> unord_set;
    public:
        ~Index_set_hashtable() override {};
        auto contains(Scalar_index item) override
        {
            return unord_set.contains(item);
        }
        auto insert(Scalar_index item) override
        {
            return unord_set.insert(item).second;
        }
        auto erase(Scalar_index item) override
        {
            return unord_set.erase(item);
        }
        auto size() override
        {
            return unord_set.size();
        }
};
}
int main()
{
    ogxx::Index_set_hashtable<int> a;
    std::cout<<5;    
}
#endif