/// @file source/index_set_sortedvector.cpp
/// @brief Index_set implemented via sorted vector.
/// @author Nasonenko I. D.
#include "index_set_sortedvector.hpp"

#include <ogxx/stl_iterator.hpp>
#include <algorithm>


namespace ogxx {

  Index_set_sortedvector::Index_set_sortedvector(Index_iterator_uptr elems)
  {
      for (Scalar_index index; elems->next(index);)
          sorted_vector.emplace_back(index);
          
      std::sort(sorted_vector.begin(), sorted_vector.end());
      sorted_vector.erase(std::unique(sorted_vector.begin(), sorted_vector.end()),
          sorted_vector.end());
  }

  auto Index_set_sortedvector::insert(Scalar_index index) -> bool {
      auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
      if (it != sorted_vector.end() && *it == index) return false;
      sorted_vector.insert(it, index);
      return true;
  }

  auto Index_set_sortedvector::erase(Scalar_index index) -> bool {
      auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
      if (it == sorted_vector.end() || *it != index) return false;
      sorted_vector.erase(it);
      return true;
  }

  auto Index_set_sortedvector::contains(Scalar_index index) const noexcept -> bool {
      auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
      return (it != sorted_vector.end() && *it == index);
  }

  auto Index_set_sortedvector::iterate() const -> Index_iterator_uptr {
      return new_stl_iterator(sorted_vector);
  }

  auto Index_set_sortedvector::get(Scalar_index index) const -> Scalar_index
  {
      if (static_cast<size_t>(index) >= sorted_vector.size())
        return npos;
            
      return sorted_vector[index];
  }

  auto Index_set_sortedvector::set(Scalar_index index, Scalar_index value) -> Scalar_index
  {
      if (static_cast<size_t>(index) >= sorted_vector.size())
        throw std::out_of_range("Index_set_sortedvector::set: index is out of range");
            
      auto ret = sorted_vector[index];
      sorted_vector[index] = value;
      return ret;
  }


  auto new_index_set_sortedvector() -> Index_set_uptr
  {
    return std::make_unique<Index_set_sortedvector>();
  }

  auto new_index_set_sortedvector(Index_iterator_uptr elems) -> Index_set_uptr
  {
    return std::make_unique<Index_set_sortedvector>(std::move(elems));
  }
}
