/// @file graph_view_un_el.cpp
/// @brief graph_view_un_el.cpp implementation
/// @author Solonitsyn Maksim

#include <ogxx/graph_view.hpp>
#include <ogxx/edge_list.hpp>

namespace ogxx {

    class Graph_view_undirected_edge_list : public Graph_view {
    private:
        Edge_list& edge_list;

    public:
        explicit Graph_view_undirected_edge_list(Edge_list& el) : edge_list(el) {}

        [[nodiscard]] auto vertex_count() const noexcept -> Scalar_size override {
                return edge_list.max_vertex_index() + 1;
        }

        [[nodiscard]] auto edge_count() const noexcept -> Scalar_size override {
                return edge_list.size();
        }

        [[nodiscard]] auto iterate_edges() const -> Vertex_pair_iterator_uptr override {

            return edge_list.sorted_iterate();
        }

        [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept -> bool override {

                return edge_list.contains(edge) || edge_list.contains({ edge.second, edge.first });
        }

        void set_vertex_count(Scalar_size count) override = 0;

        auto connect(Vertex_pair edge) -> bool override {
            return edge_list.sorted_insert(edge) || edge_list.sorted_insert({ edge.second, edge.first });
        }

        auto disconnect(Vertex_pair edge) -> bool override {
            return edge_list.sorted_erase(edge) > 0 || edge_list.sorted_erase({ edge.second, edge.first }) > 0;
        }
        auto Graph_view_undirected_edge_list::copy_from(Graph_view const& gv) -> Scalar_size {
            Scalar_size added_edges = 0;
            Scalar_size const verts = std::max(vertex_count(), gv.vertex_count());
            set_vertex_count(verts);

            auto gv_edge_iter = gv.iterate_edges();
            for (Vertex_pair vp; gv_edge_iter->next(vp);)
                if (connect(vp))
                    ++added_edges;

            return added_edges;
        }
    };
    [[nodiscard]] auto undirected::graph_view(Edge_list& el) -> Graph_view_uptr {
        return std::make_unique<Graph_view_undirected_edge_list>(el);
    }
}


