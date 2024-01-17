///@file is_independent_set.cpp
///@brief implementation of the function is_independent_set
///@author Krukovich Sonya

#include <ogxx/iterator.hpp>
#include <ogxx/subgraph_checks.hpp>


namespace ogxx {

  namespace undirected
  {
    auto is_independent_set(Graph_view const& gv, Index_iterator_uptr vertices) -> bool {
      // �������� ���������� ���� ����� ����� ������ ������ � ��������� vertices
      for (Vertex_index from; vertices->next(from);) {
        auto neighbors_iter = gv.iterate_neighbors(from);

        for (Vertex_index to; neighbors_iter->next(to);) {
          // ���� ���������� ����� ����� ��������� from � to, �� - �� ����������� ���������
          if (gv.are_connected(from, to))
            return false;
        }
      }

      // ���� �� ������� �� ������ ����� ����� ��������� �� ���������, �� - ����������� ���������
      return true;
    }
  }

  namespace directed
  {
    auto is_independent_set(Graph_view const& gv, Index_iterator_uptr vertices) -> bool {
      // �������� ���������� ���� ����� ����� ������ ������ � ��������� vertices
      for (Vertex_index from; vertices->next(from);) {
        auto neighbors_iter = gv.iterate_neighbors(from);

        for (Vertex_index to; neighbors_iter->next(to);) {
          // ���� ���������� ����� ����� ��������� from � to, �� �� - ����������� ���������
          if (gv.are_connected(from, to) || gv.are_connected(to, from))
            return false;
        }
      }

      // ���� �� ������� �� ������ ����� ����� ��������� �� ���������, �� - ����������� ���������
      return true;
    }
  }
}
