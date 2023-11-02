/// write doc comment (file/brief/author)
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
      // TODO
    }

    [[nodiscard]] auto iterate_edges() const override
      -> Vertex_pair_iterator_uptr
    {
      // TODO
    }

    [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept override
      -> bool
    {
      // TODO
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
      // TODO
    }

  private:
    Edge_list & _el;
  };

}
