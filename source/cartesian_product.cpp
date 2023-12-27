#include <ogxx/graph_view.hpp>

namespace ogxx
{
  void cartesian_product(Graph_view const& g, Graph_view const& h, Graph_view& product)
  {
    // 1. Set the vertex count of the product graph
    // The vertex count of the product graph is the product of the vertex counts of g and h
    Scalar_size vertexCount = g.vertex_count() * h.vertex_count();
    product.set_vertex_count(vertexCount);

    // 2. Add edges to the product graph
    // Iterate through all possible pairs of vertices from g and h
    for (Vertex_index gVertex = 0; gVertex < g.vertex_count(); ++gVertex)
    {
      for (Vertex_index hVertex = 0; hVertex < h.vertex_count(); ++hVertex)
      {
        // Get the corresponding vertex index in the product graph
        Vertex_index productVertex = gVertex * h.vertex_count() + hVertex;

        // Check if there is an edge between the current vertices in g or h
        if (g.are_connected(gVertex, gVertex) || h.are_connected(hVertex, hVertex))
        {
          // Add an edge between the current vertices in the product graph
          product.connect(productVertex, productVertex);
        }
      }
    }
  }
}