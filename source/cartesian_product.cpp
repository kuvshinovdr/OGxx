#include <ogxx/graph_view.hpp>
namespace ogxx
{
  void cartesian_product(Graph_view const& g, Graph_view const& h, Graph_view& product)
  {
    // Set the vertex count of the product graph
    Scalar_size g_vertex_count = g.vertex_count();
    Scalar_size h_vertex_count = h.vertex_count();
    Scalar_size product_vertex_count = g_vertex_count * h_vertex_count;
    product.set_vertex_count(product_vertex_count);

    // Add edges to the product graph
    for (Scalar_size i = 0; i < g_vertex_count; ++i)
    {
      auto const ig = i * h_vertex_count;
      auto edges = h.iterate_edges();
      for (Vertex_pair e; edges->iterate(e);)
      {
        auto const [h1, h2] = e;
        product.connect(ig + h1, ig + h2);
      }
    }

    for (Scalar_size j = 0; j < h_vertex_count; ++j)
    {
      auto edges = g.iterate_edges();
      for (Vertex_pair e; edges->iterate(e);)
      {
        auto const [g1, g2] = e;
        product.connect(g1 * h_vertex_count + j, g2 * h_vertex_count + j);
      }
    }
  }
}
