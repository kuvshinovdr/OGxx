/// @file make_hypercube.cpp
/// @brief Implementation of function 'make_hypercube_one_direction'
/// @author Zaykina V.E.

#include <ogxx/graph_view.hpp>
#include <vector>
#include <algorithm>
#include <cmath>


namespace ogxx {
	/// @brief Make hypercube on vertices represented by 'vertices'
	/// @param gv					the graph view on the basis of which the hypercube is created
	/// @param vertices		the iterator that represents vertices of hypercube
	void make_hypercube_one_direction(Graph_view& gv, Index_iterator_uptr vertices) {
		Scalar_size count_of_vertices = 0;
		for (Scalar_index item; vertices->next(item);) {
			++count_of_vertices;
		}

		if (count_of_vertices > 0 && (count_of_vertices & (count_of_vertices - 1)) == 0) {
			throw std::invalid_argument("make_hypercube_one_direction: count of vertices != 2^n.");
		}

		std::vector<Scalar_index> vertices_;
		for (Scalar_index item; vertices->next(item); ) {
			vertices_.push_back(item);
		}

		Scalar_size const n = std::log2(count_of_vertices);

		std::vector<Scalar_index> masks;
		for (Scalar_index i = 1, j = 0; j < n; i = i << 1, ++j) {
			masks.push_back(i);
		}

		for (Scalar_index i = 0; i < count_of_vertices - 1; ++i) {
			for (Scalar_index j = 0, neighbour_i; j < n; ++j) {
				neighbour_i = i ^ masks[j];
				if (i < neighbour_i) {
					gv.connect(vertices_[i], neighbour_i);
				}
			}
		}
	}
}

