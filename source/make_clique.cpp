#include <../include/ogxx/graph_view.hpp>
#include <../include/ogxx/iterator.hpp>
#include <vector>
#include <iostream>

namespace ogxx {
    void make_undirected_clique(Graph_view& gv, Index_iterator_uptr vertices) {
        using namespace std;
        using namespace ogxx;

        vector<Vertex_index> indices;

        for (Vertex_index vertex; vertices->next(vertex);) {
            indices.emplace_back(vertex);
        }

        for (size_t i = 0; i < indices.size(); ++i) {
            for (size_t j = i + 1; j < indices.size(); ++j) {
                gv.connect(indices[i], indices[j]);
            }
        }
    }
}