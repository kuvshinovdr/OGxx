/// @file is_chain_loop.cpp
/// @brief ogxx::functions, that check a subgraph of the graph gv contains (contour) on the vertices enumerated by the vertices iterator.
/// @author Artemenko I.V

#include <ogxx/graph_view.hpp>
#include <ogxx/iterator.hpp>
#include <vector>

namespace ogxx {
	using namespace std;

	bool is_chain(Graph_view const& gv, Index_iterator_uptr vertices) {
		vector<Vertex_index> vertex_vect;

		for (Vertex_index vertex; vertices->next(vertex)) {
			vertex_vect.emplace_back(vertex);
		}

		if (vertex_vect.size() < 2) {
			return false;
		}

		for (size_t i = 0; i < vertex_vect.size()-1; i++) {
			if (!gv.are_connected(vertex_vect[i], vertex_vect[i+1]))
				return false;	
		}
		return true;
	}

	bool is_loop(Graph_view const& gv, Index_iterator_uptr vertices) {
		vector<Vertex_index> vertex_vect;

		for (Vertex_index vertex; vertices->next(vertex)) {
			vertex_vect.emplace_back(vertex);
		} 

		for (size_t i = 0; i < vertex_vect.size() - 1; i++) {
			if (!gv.are_connected(vertex_vect[i], vertex_vect[i + 1]))
				return false;
		}
		
		return gv.are_connected(vertex_vect.back(), vertex_vect[0]);
	}
}