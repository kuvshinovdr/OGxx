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
      for (Scalar_size j = 0; j < h_vertex_count; ++j)
      {
        // Iterate through the edges of g
        auto g_edge_iter = g.iterate_edges();
        for (Vertex_pair g_edge; g_edge_iter->next(g_edge);)
        {
          Vertex_index g_from = g_edge.first;
          Vertex_index g_to = g_edge.second;

          // Add the corresponding edge to the product graph
          Vertex_index product_from = i * h_vertex_count + j;
          Vertex_index product_to = g_to * h_vertex_count + j;
          product.connect(product_from, product_to);
        }

        // Iterate through the edges of h
        auto h_edge_iter = h.iterate_edges();
        for (Vertex_pair h_edge; h_edge_iter->next(h_edge);)
        {
          Vertex_index h_from = h_edge.first;
          Vertex_index h_to = h_edge.second;

          // Add the corresponding edge to the product graph
          Vertex_index product_from = i * h_vertex_count + j;
          Vertex_index product_to = i * h_vertex_count + h_to;
          product.connect(product_from, product_to);
        }
      }
    }
  }
}
