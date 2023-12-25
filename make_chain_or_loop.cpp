
#include "iterator.hpp"
#include "graph_view.hpp"

namespace ogxx {

    void make_chain(Graph_view& gv, Index_iterator_uptr vertices) {
        while (vertices->has_next()) {
            auto v1 = vertices->next();
            if (vertices->has_next()) {
                auto v2 = vertices->next();
                gv.add_edge(v1, v2);
            }
        }
    }

    void make_loop(Graph_view& gv, Index_iterator_uptr vertices) {
        while (vertices->has_next()) {
            auto v1 = vertices->next();
            if (vertices->has_next()) {
                auto v2 = vertices->next();
                gv.add_edge(v1, v2);
            }
        }
        // Добавляем ребро от последней вершины к первой для создания цикла
        gv.add_edge(vertices->last(), vertices->first());
    }

}
