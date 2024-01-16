/// @file source/index_set_sortedvector.hpp
/// @brief Index_set implementation based upon a sorted vector of set elements
/// @author Nasonenko I. D.
#ifndef OGXX_INDEX_SET_SORTEDVECTOR_HPP_INCLUDED
#define OGXX_INDEX_SET_SORTEDVECTOR_HPP_INCLUDED

#include <ogxx/st_set.hpp>
#include <ogxx/iterable.hpp>

#include <vector>


namespace ogxx {
    class Index_set_sortedvector 
      : public Index_set
      , public Indexed_iterable<Scalar_index> {
    private:
        std::vector<Scalar_index> sorted_vector;
        
    public:
        Index_set_sortedvector() noexcept = default;

        explicit Index_set_sortedvector(Index_iterator_uptr elems);

        auto insert(Scalar_index index) -> bool override;

        auto erase(Scalar_index index) -> bool override;

        auto contains(Scalar_index index) const noexcept -> bool override;

        [[nodiscard]] auto iterate() const
          -> Basic_iterator_uptr<Scalar_index> override;

        [[nodiscard]] auto is_empty() const noexcept
          -> bool override
        {
            return sorted_vector.empty();
        }

        [[nodiscard]] auto size() const noexcept
          -> Scalar_size override
        {
            return sorted_vector.size();
        }

        [[nodiscard]] auto get(Scalar_index index) const
          -> Scalar_index override;

        auto set(Scalar_index index, Scalar_index value)
          -> Scalar_index override;
    };
}

#endif//OGXX_INDEX_SET_SORTEDVECTOR_HPP_INCLUDED
