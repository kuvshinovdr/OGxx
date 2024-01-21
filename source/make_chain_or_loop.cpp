#include "iterator.hpp"
#include "graph_view.hpp"

namespace ogxx {


    void make_chain(Graph_view& gv, Index_iterator_uptr vertices) {
        int v1, v2;
        if (vertices->next(v1)) {
            while (vertices->next(v2)) {
                gv.connect(v1, v2);
                v1 = v2;
            }
        }
    }


    void make_loop(Graph_view& gv, Index_iterator_uptr vertices) {
        int v1, v2;
        if (vertices->next(v1)) {
            int firstVertex = v1;
            while (vertices->next(v2)) {
                gv.connect(v1, v2);
                v1 = v2;
            }
            gv.connect(v1, firstVertex);
        }
    }

}
