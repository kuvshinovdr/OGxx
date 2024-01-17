/// @file cartesian_product.cpp
/// @brief Cartesian product procedure test
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include "testing_head.hpp"
#include <ogxx/graph_view.hpp>
#include <ogxx/edge_list.hpp>


TEST_SUITE("Cartesian product")
{
  TEST_CASE("3x4")
  {
    auto g = new_edge_list_vector({{0, 1}, {1, 2}, {0, 2}});
    auto h = new_edge_list_vector({{0, 1}, {1, 2}, {2, 3}, {0, 3}});
    auto gv = directed::graph_view(*g);
    auto hv = directed::graph_view(*h);
    
    auto p = new_edge_list_vector();
    auto pv = directed::graph_view(*p);
    cartesian_product(*gv, *hv, *pv);

    CHECK(pv->vertex_count() == 12);
    CHECK(pv->edge_count() == 24);

    static Vertex_pair const ref[]
    {
      {0, 1}, {1, 2}, {2, 3}, {0, 3},
      {4, 5}, {5, 6}, {6, 7}, {4, 7},
      {8, 9}, {9, 10}, {10, 11}, {8, 11},
      {0, 4}, {1, 5}, {2, 6}, {3, 7},
      {4, 8}, {5, 9}, {6, 10}, {7, 11},
      {0, 8}, {1, 9}, {2, 10}, {3, 11}
    };

    for (auto e: ref)
      CHECK(pv->are_connected(e));
  }
}
