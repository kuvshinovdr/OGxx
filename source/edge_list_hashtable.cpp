#include <unordered_set>
#include <algorithm>
#include <utility>
#include <memory>
#include <iostream>
#include <vector>

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
                return -1;
            }
            auto max_index_iter = std::max_element(edges.begin(), edges.end(),
                [](const Vertex_pair& a, const Vertex_pair& b) {
                    return std::max(a.first, a.second) < std::max(b.first, b.second);
                });
            return std::max(max_index_iter->first, max_index_iter->second);
        }

    private:
        std::unordered_set<Vertex_pair, std::hash<Vertex_pair>> edges;
    };

    class Graph_view {
    public:
        virtual void view() const = 0;
    };

    class Directed_graph_view : public Graph_view {
    public:
        void view() const override {

            std::cout << "This is a directed graph" << std::endl;
        }
    };

    class Undirected_graph_view : public Graph_view {
    public:
        void view() const override {

            std::cout << "This is an undirected graph" << std::endl;
        }
    };

    using Edge_list_uptr = std::unique_ptr<Edge_list>;
    using Edge_list_const_uptr = std::unique_ptr<const Edge_list>;
    using Graph_view_uptr = std::unique_ptr<Graph_view>;
    using Graph_view_const_uptr = std::unique_ptr<const Graph_view>;

    [[nodiscard]] auto new_edge_list_vector() -> Edge_list_uptr {
        return std::make_unique<Edge_list_hashtable>();
    }

    namespace directed {
        [[nodiscard]] auto graph_view(Edge_list const& el) -> Graph_view_const_uptr {
            return std::make_unique<Directed_graph_view>();
        }

        [[nodiscard]] auto graph_view(Edge_list& el) -> Graph_view_uptr {
            return std::make_unique<Directed_graph_view>();
        }
    }

    namespace undirected {
        [[nodiscard]] auto graph_view(Edge_list const& el) -> Graph_view_const_uptr {
            return std::make_unique<Undirected_graph_view>();
        }

        [[nodiscard]] auto graph_view(Edge_list& el) -> Graph_view_uptr {
            return std::make_unique<Undirected_graph_view>();
        }
    }
}