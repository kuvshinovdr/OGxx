/// @file edge_list_vector.cpp
/// @brief Edge_list implementation based upon std::vector
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru, Zvorygin M.A.
#include <ogxx/edge_list.hpp>
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>
#include <vector>

namespace ogxx
{
    class Edge_list_vector : public Edge_list, public List<Vertex_pair>
    {
    private:
        std::vector<Vertex_pair> _edges;

    public:
        ~Edge_list_vector() noexcept override = default;

        // From Edge_list:
        auto find(Vertex_pair edge) const noexcept
            -> Scalar_index override
        {
            for (size_t i = 0; i < _edges.size(); ++i) {
                if (_edges[i] == edge) {
                    return static_cast<Scalar_index>(i);
                }
            }
			
            return npos; // Not found
        }

        auto max_vertex_index() const noexcept
            -> Vertex_index override
        {
            Vertex_index maxIndex = 0;
            for (const auto& edge : _edges) {
                maxIndex = max(maxIndex, edge.first, edge.second);
            }
            return maxIndex;
        }

        // From List<Vertex_pair>:

        auto take(Scalar_index from)
            -> Pass_by<Vertex_pair> override
        {
            if (static_cast<size_t>(from) >= _edges.size()) {
                throw std::out_of_range("Edge_list_vector::take: index out of range");
            }
            auto item = _edges[from];
            _edges.erase(_edges.begin() + from);
            return item;
        }

        void put(Scalar_index at, Pass_by<Vertex_pair> item) override
        {
            if (static_cast<size_t>(at) > _edges.size()) {
                throw std::out_of_range("Edge_list_vector::put: index out of range");
            }
            _edges.insert(_edges.begin() + at, item);
        }

        // From Bag<Vertex_pair>:

        void clear() override
        {
            _edges.clear();
        }

        auto take() -> Pass_by<Vertex_pair> override
        {
            if (_edges.empty())
                throw std::logic_error("Edge_list_vector::take: the list is empty");

            Vertex_pair vp = _edges.back();
            _edges.pop_back();
            return vp;
        }

        void put(Pass_by<Vertex_pair> item) override
        {
            _edges.emplace_back(item);
        }

        // Indexed_iterable<Vertex_pair>

        auto get(Scalar_index index) const
            -> See_by<Vertex_pair> override
        {
            return _edges.at(index);
        }

        auto set(Scalar_index index, Pass_by<Vertex_pair> value)
            -> Pass_by<Vertex_pair> override
        {
            auto old_vp = _edges.at(index);
            _edges[index] = value;
            return old_vp;
        }

        // Sized_iterable<Vertex_pair>

        auto size() const noexcept
            -> Scalar_size override
        {
            return _edges.size();
        }

        // Iterable<Vertex_pair>

        auto iterate() const
            -> Basic_iterator_uptr<See_by<Vertex_pair>> override
        {
            return new_stl_iterator(_edges);
        }

        auto is_empty() const noexcept
            -> bool override
        {
            return _edges.empty();
        }

    
    };

    auto new_edge_list_vector() -> Edge_list_uptr
    {
        return std::make_unique<Edge_list_vector>();
    }
}  // namespace ogxx