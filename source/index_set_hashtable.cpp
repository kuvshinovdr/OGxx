/// @file index_set_hashtable.cpp
/// @brief index_set_hashtable.hpp implementation
/// @author ChernyshevMV, Kuvshinov D.R.
#include "index_set_hashtable.hpp"
#include <ogxx/stl_iterator.hpp>


namespace ogxx
{

    Index_set_hashtable::Index_set_hashtable(Index_iterator_uptr elems)
    {
        for (Scalar_index index; elems->next(index);)
            unord_set.emplace(index);
    }

    auto Index_set_hashtable::contains(Scalar_index item) const noexcept -> bool
    {
        return (unord_set.find(item) != unord_set.end());
    } 
        
    auto Index_set_hashtable::insert(Scalar_index item) -> bool
    {
        return unord_set.insert(item).second;
    }
        
    auto Index_set_hashtable::erase(Scalar_index item) -> bool
    {
        return unord_set.erase(item) != 0;
    }
        
    auto Index_set_hashtable::size() const noexcept -> Scalar_size
    {
        return unord_set.size();
    }

    auto Index_set_hashtable::iterate() const -> Basic_iterator_uptr<Scalar_index>
    {
        return new_stl_iterator(unord_set);
    }

    
    auto new_index_set_hashtable() -> Index_set_uptr
    {
      return std::make_unique<Index_set_hashtable>();
    }

    auto new_index_set_hashtable(Index_iterator_uptr elems) -> Index_set_uptr
    {
      return std::make_unique<Index_set_hashtable>(std::move(elems));
    }
}
