#include <ogxx/graph_view.hpp>

namespace ogxx
{
    void ogxx::cartesian_product(Graph_view const& g, Graph_view const& h, Graph_view& product)
    {
    // Получаем количество вершин в графах g и h
    Scalar_size g_vertex_count = g.vertex_count();
    Scalar_size h_vertex_count = h.vertex_count();

    // Устанавливаем количество вершин в графе product
    Scalar_size product_vertex_count = g_vertex_count * h_vertex_count;
    product.set_vertex_count(product_vertex_count);

    // Добавляем ребра декартова произведения
    for (Vertex_index g_vertex = 0; g_vertex < g_vertex_count; ++g_vertex)
    {
        for (Vertex_index h_vertex = 0; h_vertex < h_vertex_count; ++h_vertex)
        {
        // Получаем индекс вершины в графе product
        Vertex_index product_vertex = g_vertex * h_vertex_count + h_vertex;

        // Проверяем, есть ли ребро между соответствующими вершинами в графах g и h
        if (g.are_connected(g_vertex, g_vertex) || h.are_connected(h_vertex, h_vertex))
        {
            // Добавляем ребро в граф product
            product.connect(product_vertex, product_vertex);
        }
        }
    }
    }
}

#include <ogxx/graph_view.hpp>
#include <iostream>

int main()
{
  ogxx::Graph_view_uptr g = std::make_unique<ogxx::Graph_view>();
  ogxx::Graph_view_uptr h = std::make_unique<ogxx::Graph_view>();
  ogxx::Graph_view_uptr product = std::make_unique<ogxx::Graph_view>();

  // Add vertices and edges to g and h

  ogxx::cartesian_product(*g, *h, *product);

  // Print the vertices and edges of the product graph

  return 0;
}