/// @file is_star.cpp
/// @brief Identify the graph is a star
/// @author Artemenko I.V
#include <ogxx/iterator.hpp>
#include <ogxx/subgraph_checks.hpp>

#include <vector>

namespace ogxx
{

    namespace
    {
        // Get the degree of the vertex
        auto get_deg_vertex(Vertex_index index, std::vector<Vertex_index>& vertex, Graph_view const& gv) {
            size_t deg=0;
            for (auto v: vertex) {
                if (gv.are_connected(index, v)) {
                    deg++;
                }
            }
            return deg;
        }
    }
	

    auto is_star(Graph_view const& gv, Index_iterator_uptr vertices)
        -> std::optional<Vertex_index> {
        std::vector <Vertex_index> vertex;
        for (Vertex_index v; vertices->next(v);) {
            vertex.emplace_back(v);
        }
        auto const len = vertex.size();
        if (len < 3)
            return {};
        size_t sum = 0;
		
        Vertex_index center = -1;
        for (auto index : vertex) {
            auto deg = get_deg_vertex(index, vertex, gv);
            sum += deg;
            if (deg != 1 && deg != len - 1) {
                return {};
            }
            if (deg == len - 1) {
                if (center != -1)
                    return {};
                else
                    center = index;

            }
        }
        
        if (sum / 2 == len - 1)
          return center;
        
        return {};
    }
}
