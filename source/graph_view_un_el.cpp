/// @file graph_view_un_el.cpp
/// @brief graph_view_un_el.cpp implementation
/// @author Solonitsyn Maksim

#include <ogxx/graph_view.hpp>
#include <ogxx/edge_list.hpp>
#include <ogxx/st_set.hpp>

namespace ogxx {

    class Graph_view_undirected_edge_list : public Graph_view {
    private:
        Edge_list& edge_list;
        St_set<Vertex_pair> * _as_set = nullptr;

    public:
        explicit Graph_view_undirected_edge_list(Edge_list& el) 
          : edge_list(el), _as_set(dynamic_cast<St_set<Vertex_pair>*>(&el)) {}

        [[nodiscard]] auto vertex_count() const noexcept -> Scalar_size override {
                return edge_list.max_vertex_index() + 1;
        }

        [[nodiscard]] auto edge_count() const noexcept -> Scalar_size override {
                return edge_list.size();
        }

        [[nodiscard]] auto iterate_edges() const -> Vertex_pair_iterator_uptr override {
                return edge_list.iterate();
        }

        [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept -> bool override {
                auto const er = edge_reverse(edge);
                if (_as_set)
                    return _as_set->contains(edge) || _as_set->contains(er);
                
                // Check by iterating.
                auto it = edge_list.iterate();
                for (Vertex_pair e; it->next(e);)
                    if (e == edge && e == er)
                        return true;

                return false;
        }

        void set_vertex_count(Scalar_size count) override
        {
              // TODO: throw unimplemented
        }

        auto connect(Vertex_pair edge) -> bool override {
            // TODO: cf. are_connected
            // no sorted_insert in edge_list but put
            return edge_list.sorted_insert(edge) || edge_list.sorted_insert({ edge.second, edge.first });
        }

        auto disconnect(Vertex_pair edge) -> bool override {
            // TODO: cf. are_connected
            // no sorted_erase in edge_list, may throw
            return edge_list.sorted_erase(edge) > 0 || edge_list.sorted_erase({ edge.second, edge.first }) > 0;
        }
    };

    [[nodiscard]] auto undirected::graph_view(Edge_list& el) -> Graph_view_uptr {
        return std::make_unique<Graph_view_undirected_edge_list>(el);
    }
}


