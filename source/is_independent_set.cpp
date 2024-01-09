///@file is_independent_set.cpp
///@brief implementation of the function is_independent_set
///@author Krukovich Sonya

#include <ogxx/iterator.hpp>
#include <ogxx/subgraph_checks.hpp>


namespace ogxx {

  namespace undirected
  {
    auto is_independent_set(Graph_view const& gv, Index_iterator_uptr vertices) -> bool {
      // Проверка отсутствия рёбер между всеми парами вершин в итераторе vertices
      for (Vertex_index from; vertices->next(from);) {
        auto neighbors_iter = gv.iterate_neighbors(from);

        for (Vertex_index to; neighbors_iter->next(to);) {
          // Если существует ребро между вершинами from и to, то - не независимое множество
          if (gv.are_connected(from, to))
            return false;
        }
      }

      // Если не найдено ни одного ребра между вершинами из итератора, то - независимое множество
      return true;
    }
  }

  namespace directed
  {
    auto is_independent_set(Graph_view const& gv, Index_iterator_uptr vertices) -> bool {
      // Проверка отсутствия рёбер между всеми парами вершин в итераторе vertices
      for (Vertex_index from; vertices->next(from);) {
        auto neighbors_iter = gv.iterate_neighbors(from);

        for (Vertex_index to; neighbors_iter->next(to);) {
          // Если существует ребро между вершинами from и to, то не - независимое множество
          if (gv.are_connected(from, to) || gv.are_connected(to, from))
            return false;
        }
      }

      // Если не найдено ни одного ребра между вершинами из итератора, то - независимое множество
      return true;
    }
  }
}
