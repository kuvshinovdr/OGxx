/// @file index_set_hashtable.hpp
/// @brief This file defines Index_set and Sized_iterable implementation based upon std::unordered_set
/// @author ChernyshevMV
#ifndef OGXX_INDEX_SET_HASHTABLE_HPP_INCLUDED
#define OGXX_INDEX_SET_HASHTABLE_HPP_INCLUDED

#include <ogxx/st_set.hpp>
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>

#include <unordered_set>

namespace ogxx
{

    class Index_set_hashtable
      : public virtual Index_set
      , public virtual Sized_iterable<Scalar_index>
    {
    private:
        std::unordered_set<Scalar_index> unord_set;

    public:
        Index_set_hashtable() = default;

        [[nodiscard]] auto contains(Scalar_index item) const noexcept 
          -> bool override
        {
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
            return unord_set.erase(item) != 0;
        }
        
        [[nodiscard]] auto size() const noexcept
          -> Scalar_size override 
        {
            return unord_set.size();
        }

        [[nodiscard]] auto iterate() const 
          -> Basic_iterator_uptr<Scalar_index> override
        {
            return new_stl_iterator(unord_set);
        }

        [[nodiscard]] auto is_empty() const noexcept
          -> bool override 
        {
              return unord_set.empty();
        }
    };
}

#endif//OGXX_INDEX_SET_HASHTABLE_HPP_INCLUDED
