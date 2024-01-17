#include <ogxx/edge_list.hpp>
#include <ogxx/st_set.hpp>

#include <ogxx/stl_iterator.hpp>


#include <unordered_set>
#include <algorithm>



namespace ogxx {

    // Define the hash function for Vertex_pair
    namespace std {
        template <>
        struct hash<Vertex_pair> {
            auto operator()(const Vertex_pair& p) const noexcept {
                std::hash<Scalar_index> h;
                return h(p.first) * 15485863 ^ h(p.second);
            }
        };
    }

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
            auto max_index_iter = std::max_element(edges.begin(), edges.end(),
                [](const Vertex_pair& a, const Vertex_pair& b) {
                    return std::max(a.first, a.second) < std::max(b.first, b.second);
                });
            return std::max(max_index_iter->first, max_index_iter->second);
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

        virtual auto is_empty() const noexcept -> bool override {
            return edges.empty();
        }

    private:
        std::unordered_set<Vertex_pair, std::hash<Vertex_pair>> edges;
    };

}
