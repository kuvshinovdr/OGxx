/// @file index_set_sortedvector.cpp
/// @brief Testing Edge_list_hashtable class.
#include "testing_head.hpp"
#include <ogxx/edge_list.hpp>
#include <ogxx/stl_iterator.hpp>

TEST_SUITE("Edge_list_hashtable")
{
  TEST_CASE("create from iterator")
  {
    Vertex_pair input[]
    {
      { 0, 2 },
      { 2, 1 },
      { 1, 0 },
      { 1, 3 }
    };

    auto el  = new_edge_list_hashtable(new_stl_iterator(input));
    auto set = dynamic_cast<St_set<Vertex_pair>*>(el.get());
    CHECK(set != nullptr);
    CHECK(el->max_vertex_index() == 3);
    CHECK(el->size() == 4);

    for (auto vp: input)
      CHECK(set->contains(vp));

    CHECK(!set->contains(Vertex_pair{3, 0}));
  }
}
