/// @file is_chain_loop.cpp
/// @brief ogxx::functions, that check a subgraph of the graph gv contains (contour) on the vertices enumerated by the vertices iterator.
/// @author Artemenko I.V

#include <ogxx/graph_view.hpp>
#include <ogxx/iterator.hpp>
#include <vector>

namespace ogxx {

	bool is_chain(Graph_view const& gv, Index_iterator_uptr vertices) {
		Vertex_index first_vertex, second_vertex;

		if (!vertices->next(first_vertex)) {
			return false;
		}

		if (!vertices->next(second_vertex)) {
			return true;
		}

		do {
			if (!gv.are_connected(first_vertex, second_vertex)) {
				return false;
			}
			first_vertex = second_vertex;
		} while (vertices->next(second_vertex));

		return true;
	}

	bool is_loop(Graph_view const& gv, Index_iterator_uptr vertices) {
		Vertex_index first_vertex, second_vertex;
		if (!vertices->next(first_vertex)) {
			return false;
		}
		Vertex_index start = first_vertex;

		if (!vertices->next(second_vertex)) {
			return true;
		}

		do {
			if (!gv.are_connected(first_vertex, second_vertex)) {
				return false;
			}
			first_vertex = second_vertex;
		} while (vertices->next(second_vertex));
		
		Vertex_index end = second_vertex;
		
		return end == start || gv.are_connected(end, start);
	}
}
