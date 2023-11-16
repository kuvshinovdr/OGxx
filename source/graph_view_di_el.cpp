/// @file graph_view_di_el.cpp
/// @brief Graph view implementation for directed graph represented by an edge list.
/// @author Abdullaeva Ainur
#include <ogxx/graph_view.hpp>
#include <ogxx/edge_list.hpp>

#include <stdexcept>


namespace ogxx
{

  class Graph_view_directed_edge_list : public Graph_view
  {
  public:
    Graph_view_directed_edge_list(Edge_list& el)
      : _el(el) {}

    // Constant interface

    [[nodiscard]] auto vertex_count() const noexcept override
      -> Scalar_size
    {
      return _el.max_vertex_index() + 1;
    }

    [[nodiscard]] auto edge_count() const noexcept override
      -> Scalar_size
    {
        return _el.size();
    }

    [[nodiscard]] auto iterate_edges() const override
      -> Vertex_pair_iterator_uptr
    {
       _el.iterate();
    }

    [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept override
      -> bool
    {
      return _el.find(edge) != npos;
    }


    // Non-constant interface

    void set_vertex_count(Scalar_size count) override
    {
      // Pending solution.
      throw std::invalid_operation("Graph_view_directed_edge_list::set_vertex_count: not implemented");
    }

    auto connect(Vertex_pair edge) override
    {
      _el.put(edge);
    }

    auto disconnect(Vertex_pair edge) override
      -> bool
    {
      // Данный метод можно реализовать, если Edge_list на самом деле реализует List.
      // Найти с помощью find и удалить по индексу с помощью take.
    }

  private:
    Edge_list & _el;
  };


  namespace directed
  {
    auto graph_view(Edge_list& el)
      -> Graph_view_uptr
    {
      return std::make_unique<Graph_view_directed_edge_list>(el);
    }
  }

}
