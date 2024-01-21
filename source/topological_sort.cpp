#include "graph_view.hpp"
#include "iterator.hpp"
#include <vector>
#include <queue>

namespace ogxx {

    Index_iterator_uptr topological_sort(Graph_view& gv) {
        std::vector<int> in_degree(gv.num_vertices(), 0);
        for (Vertex_index v = 0; v < gv.num_vertices(); ++v) {
            for (const auto& neighbor : gv.neighbors(v)) {
                in_degree[neighbor]++;
            }
        }

        std::queue<Vertex_index> zero_in_degree_vertices;
        for (Vertex_index v = 0; v < gv.num_vertices(); ++v) {
            if (in_degree[v] == 0) {
                zero_in_degree_vertices.push(v);
            }
        }

        std::vector<Vertex_index> topological_order;
        while (!zero_in_degree_vertices.empty()) {
            Vertex_index u = zero_in_degree_vertices.front();
            zero_in_degree_vertices.pop();
            topological_order.push_back(u);

            Vertex_index first_vertex = -1;
            for (const auto& neighbor : gv.neighbors(u)) {
                if (first_vertex == -1) {
                    first_vertex = neighbor;
                }

                if (--in_degree[neighbor] == 0) {
                    zero_in_degree_vertices.push(neighbor);
                }
            }
        }

        if (topological_order.size() != gv.num_vertices()) {
            return nullptr;
        }

        auto result = std::make_unique<Index_iterator>();
        for (Vertex_index v : topological_order) {
            result->add(v);
        }

        return result;
    }

}
