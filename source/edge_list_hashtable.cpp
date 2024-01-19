/// @file edge_list_hashtable.cpp
/// @brief Edge_list implementation based upon std::unordered_set.

#include <ogxx/edge_list.hpp>
#include <ogxx/st_set.hpp>

#include <ogxx/stl_iterator.hpp>

#include <unordered_set>
#include <algorithm>


// Define the hash function for Vertex_pair
namespace {
    struct Vertex_pair_hash {
        auto operator()(const ogxx::Vertex_pair& p) const noexcept -> size_t {
            std::hash<ogxx::Scalar_index> h;
            auto const h1 = h(p.first), h2 = h(p.second);
            return (h1 << 13) ^ (h1 >> 17) ^ h2;
        }
    };
}

namespace ogxx {

    class Edge_list_hashtable : public Edge_list, public St_set<Vertex_pair> {
    public:
        auto contains(Vertex_pair item) const noexcept -> bool override {
            return edges.count(item) > 0;
        }

        auto insert(Vertex_pair item) -> bool override {
            auto [iter, inserted] = edges.insert(item);
            return inserted;
        }

        auto erase(Vertex_pair item) -> bool override {
            return edges.erase(item) > 0;
        }

        auto find(Vertex_pair edge) const noexcept -> Scalar_index override {
            auto iter = edges.find(edge);
            if (iter != edges.end()) {
                return std::distance(edges.begin(), iter);
            }
            return npos;
        }

        auto max_vertex_index() const noexcept -> Vertex_index override {
            if (edges.empty()) {
                return npos;
            }

            Vertex_index max_index = 0;
            for (auto [u, v]: edges)
                max_index = std::max({max_index, u, v});

            return max_index;
        }

        void put(Pass_by<Vertex_pair> item) override {
            edges.emplace(item);
        }

        auto take() -> Pass_by<Vertex_pair> override {
            Vertex_pair result { npos, npos };

            if (!edges.empty()) {
                result = *edges.begin();
                edges.erase(edges.begin());
            }

            return result;
        }

        void clear() override {
            edges.clear();
        }

        auto size() const noexcept -> Scalar_size override {
            return static_cast<Scalar_size>(edges.size());
        }

        auto iterate() const -> Vertex_pair_iterator_uptr override {
            return new_stl_iterator(edges);
        }

        auto is_empty() const noexcept -> bool override {
            return edges.empty();
        }


        Edge_list_hashtable() = default;

        Edge_list_hashtable(std::initializer_list<Vertex_pair> vp_il)
            : edges(vp_il) {}

        explicit Edge_list_hashtable(Vertex_pair_iterator_uptr vp_it) {
            for (Vertex_pair vp; vp_it->next(vp);)
                edges.emplace(vp);
        }

    private:
        std::unordered_set<Vertex_pair, Vertex_pair_hash> edges;
    };


    auto new_edge_list_hashtable() -> Edge_list_uptr {
        return std::make_unique<Edge_list_hashtable>();
    }

    auto new_edge_list_hashtable(Vertex_pair_iterator_uptr vp_it) -> Edge_list_uptr {
        return std::make_unique<Edge_list_hashtable>(std::move(vp_it));
    }

    auto new_edge_list_hashtable(std::initializer_list<Vertex_pair> vp_il) -> Edge_list_uptr {
        return std::make_unique<Edge_list_hashtable>(vp_il);
    }

}
