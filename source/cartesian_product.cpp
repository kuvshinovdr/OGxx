/// @file cartesian_product.cpp
/// @brief Compute Cartesian product of two graphs operating Graph_view objects.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/primitive_definitions.hpp>
#include <ogxx/graph_view.hpp>

#include <stdexcept>
#include <vector>


namespace ogxx
{

  void cartesian_product(Graph_view const& g, Graph_view const& h, Graph_view& product)
  {
    auto const g_verts = g.vertex_count(), h_verts = h.vertex_count();
    
    // Product vertex index mapping: product_index(g_index, h_index) == g_index * h_verts + h_index.
    // Thus we have g_verts * h_verts product vertices in total.
    if (Scalar_size product_verts; checked_multiply(g_verts, h_verts, product_verts))
      product.set_vertex_count(product_verts);
    else
      throw std::runtime_error("ogxx::cartesian_product: product vertex count is too big");

    // The simplest algorithm is to check each pair against each pair i.e. O(pow(g_verts*h_verts, 2))-time
    // if are_connected is done in O(1)-time. This can also be done as an adjacency matrix operation.
    // Another algorithm is to iterate edges and do in O(g_verts*h_edges + g_edges*h_verts)-time
    // if iterating edges is done in O(1)-time per edge.
    // This is bounded by O(g_verts*pow(h_verts, 2) + h_verts*pow(g_verts, 2))-time, which
    // is less than O(pow(g_verts + h_verts, 3))-time.
    // So let's implement the latter algorithm.

    std::vector<Vertex_pair> edges;

    // Replicate h for each vertex of g.
    edges.reserve(h.edge_count());
    auto it = h.iterate_edges();
    for (Vertex_pair e; it->next(e);)
      edges.emplace_back(e);

    for (Vertex_index g_index = 0, base = 0; g_index < g_verts; ++g_index, base += h_verts)
    {
      for (auto [h1, h2]: edges)
        product.connect(base + h1, base + h2);
    }

    // Replicate g for each vertex of h.
    edges.clear();
    edges.reserve(g.edge_count());
    it = g.iterate_edges();
    for (Vertex_pair e; it->next(e);)
    {
      auto const [g1, g2] = e;
      edges.emplace_back(g1 * h_verts, g2 * h_verts);
    }

    it.release();

    for (Vertex_index h_index = 0; h_index < h_verts; ++h_index)
    {
      for (auto [b1, b2]: edges)
        product.connect(b1 + h_index, b2 + h_index);
    }
  }

}
