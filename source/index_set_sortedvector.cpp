/// add doc-comment (file, brief, author)

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
	// Поправьте все методы соответственно интерфейсам Index_set и Indexed_iterable<Scalar_index>
	// добавьте ко всем методам override.
        void insert(const Scalar_index& index) {
            auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
            sorted_vector.insert(it, index);
        }

        void erase(const Scalar_index& index) {
            auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
            if (it != sorted_vector.end() && *it == index) {
                sorted_vector.erase(it);
            }
        }

        bool contains(const Scalar_index& index) const {
            auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
            return (it != sorted_vector.end() && *it == index);
        }

        Scalar_index find(const Scalar_index& index) const {
            auto it = std::lower_bound(sorted_vector.begin(), sorted_vector.end(), index);
            if (it != sorted_vector.end() && *it == index) {
                return *it;
            }
            throw std::out_of_range("Index not found");
        }

		// Нет, не так. См. Indexed_iterable.
        using iterator = stl_iterator<typename std::vector<Scalar_index>::iterator>;
        using const_iterator = stl_iterator<typename std::vector<Scalar_index>::const_iterator>;

        iterator begin() { return iterator(sorted_vector.begin()); }
        iterator end() { return iterator(sorted_vector.end()); }
        const_iterator begin() const { return const_iterator(sorted_vector.begin()); }
        const_iterator end() const { return const_iterator(sorted_vector.end()); }
    };
}
