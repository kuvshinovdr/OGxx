/// @file Index_set_sortedvector.cpp
/// @brief 
/// @author Nasonenko I. D.

#include <ogxx/st_set.hpp>
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>

#include <vector>
#include <algorithm>

namespace ogxx {
    class Index_set_sortedvector : public Index_set, public Indexed_iterable<Scalar_index> {
    private:
        std::vector<Scalar_index> sorted_vector;
        
    public:
        auto insert(Scalar_index index)
        -> bool override {
            auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
            if (it != sorted_vector.end() && *it == index) return false;
            sorted_vector.insert(it, index);
            return true;
        }

        auto erase(Scalar_index index)
        -> bool override {
            auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
            if (it == sorted_vector.end() || *it != index) return false;
            sorted_vector.erase(it);
            return true;
        }

        auto contains(Scalar_index index) const noexcept
        -> bool override {
            auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
            return (it != sorted_vector.end() && *it == index);
        }

        [[nodiscard]] auto iterate() const
        -> Basic_iterator_uptr<Scalar_index> override{
            return new_stl_iterator(sorted_vector);
        }

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
        -> Scalar_index override
        {
            if (static_cast<size_t>(index) >= sorted_vector.size())
              return npos;
            
            return sorted_vector[index];
        }

        auto set(Scalar_index index, Scalar_index value)
        -> Scalar_index override
        {
            if (static_cast<size_t>(index) >= sorted_vector.size())
              throw std::out_of_range("Index_set_sortedvector::set: index is out of range");
            
            auto ret = sorted_vector[index];
            sorted_vector[index] = value;
            return ret;
        }
};
}
