#include <vector>
#include <unordered_map>
#include <ogxx/iterator.hpp>
#include <ogxx/graph_view.hpp>

namespace ogxx::directed
{
  auto extract_subgraph(Index_iterator_uptr vertices, Graph_view const& from, Graph_view& subgraph)
    -> Scalar_size
  {
    std::unordered_map<Index, Index> index_map;
    for (auto i = 0; i < vertices->size(); ++i)
      index_map[(*vertices)[i]] = i;

    for (auto i = 0; i < vertices->size(); ++i)
      subgraph.add_vertex();

    auto num_edges = 0;
    for (auto i = 0; i < vertices->size(); ++i)
    {
      auto vertex = (*vertices)[i];
      for (auto edge : from.outgoing_edges(vertex))
      {
        auto target = edge.target();
        if (index_map.count(target) > 0)
        {
          subgraph.add_edge(index_map[vertex], index_map[target], edge.weight());
          ++num_edges;
        }
      }
    }

    return num_edges;
  }
}