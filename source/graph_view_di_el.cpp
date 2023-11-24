/// @file graph_view_di_el.cpp
/// @brief Graph view implementation for directed graph represented by an edge list.
/// @author Abdullaeva Ainur
#include <ogxx/graph_view.hpp>
#include <ogxx/edge_list.hpp>
#include <ogxx/iterable.hpp>
#include <ogxx/st_set.hpp>

#include <stdexcept>


namespace ogxx
{

  class Graph_view_directed_edge_list : public Graph_view
  {
  public:
    Graph_view_directed_edge_list(Edge_list& el)
      : _el(el)
      , _as_set(dynamic_cast<St_set<Vertex_pair>*>(&el))
      , _as_list(dynamic_cast<List<Vertex_pair>*>(&el))
    {
    }

    // Constant interface

    [[nodiscard]] auto is_directed() const noexcept
      -> bool override { return true; }

    [[nodiscard]] auto vertex_count() const noexcept
      -> Scalar_size                        override
    {
      return _el.max_vertex_index() + 1;
    }

    [[nodiscard]] auto edge_count() const noexcept
      -> Scalar_size                      override
    {
        return _el.size();
    }

    [[nodiscard]] auto iterate_edges() const
      -> Vertex_pair_iterator_uptr     override
    {
       return _el.iterate();
    }

    [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept
      -> bool override { return _el.find(edge) != npos; }


    // Non-constant interface

    void set_vertex_count(Scalar_size count) override
    {
      // Ignored.
    }

    auto connect(Vertex_pair edge)
      -> bool override 
    {
      if (_as_set)
        return _as_set->insert(edge);

      _el.put(edge);
      return true;
    }


    auto disconnect(Vertex_pair edge)
      -> bool override
    {
      if (_as_set)
        return _as_set->erase(edge);

      if (_as_list)
      {
        auto const pos = _el.find(edge);
        if (pos == npos)
          return false;

        _as_list->take(pos);
        return true;
      }

      throw std::logic_error("Graph_view_directed_edge_list::disconnect: the attached edge list does not support List operations");
    }

  private:
    Edge_list           & _el;
    St_set<Vertex_pair> * _as_set  = nullptr;
    List<Vertex_pair>   * _as_list = nullptr;
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
