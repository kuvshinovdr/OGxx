/// @file graph_view.hpp
/// @brief Graph view interface that may be used for graph representation coversion.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_GRAPH_VIEW_HPP_INCLUDED
#define OGXX_GRAPH_VIEW_HPP_INCLUDED

#include <ogxx/vertex_pair.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Generic graph interface to provide a common facade over concrete graph representations.
  class Graph_view
  {
  public:
    virtual ~Graph_view() {}

    // Constant interface

    /// Get the count of vertices in the graph, vertex indices are 0, 1, ..., vertex_count() - 1.
    [[nodiscard]] virtual auto vertex_count() const noexcept
      -> Scalar_size = 0;

    /// Get the count of edges in the graph, edge indices are 0, 1, ..., edge_count() - 1.
    /// The iterator returned by iterate_edges() should make edge_count() steps.
    [[nodiscard]] virtual auto edge_count() const noexcept
      -> Scalar_size = 0;

    /// @brief Iterate through edges represented by vertex index pairs.
    /// Iterator should make edge_count() steps.
    /// @return iterator object iterating through (Vertex_index, Vertex_index) pairs.
    [[nodiscard]] virtual auto iterate_edges() const
      -> Vertex_pair_iterator_uptr = 0;

    /// @brief Check if two vertices of the graph are connected by an edge.
    /// @param edge a pair of vertex indices to be checked
    /// @return true if the two vertices are connected by an edge, false otherwise (including the case of an invalid vertex index)
    [[nodiscard]] virtual auto are_connected(Vertex_pair edge) const noexcept
      -> bool = 0;

    /// @brief Check if two vertices of the graph are connected by an edge.
    /// @param from the index of the outcoming vertex
    /// @param to   the index of the incoming vertex
    /// @return true if the two vertices are connected by an edge, false otherwise (including the case of an invalid vertex index)
    [[nodiscard]] auto are_connected(Vertex_index from, Vertex_index to) const noexcept
      -> bool { return are_connected(Vertex_pair{ from, to }); }

    // Non-constant interface

    /// @brief Provide the would-be vertex count. May be used to reserve memory in advance.
    /// @param count how many vertices the graph should contain
    virtual void set_vertex_count(Scalar_size count) = 0;

    /// @brief Connect the vertices of the pair edge.
    /// @param edge (first, second) pair of vertex indices
    /// @return true if edge has been added, false otherwise (e.g. the edge already exists)
    virtual auto connect(Vertex_pair edge)
      -> bool = 0;

    /// @brief Add edge from -> to.
    /// @param from the index of the outcoming vertex
    /// @param to   the index of the incoming vertex
    /// @return true if edge has been added, false otherwise (e.g. the edge already exists)
    auto connect(Vertex_index from, Vertex_index to)
      -> bool { return connect(Vertex_pair{ from, to }); }

    /// @brief Disconnect the vertices of the pair edge
    /// @param edge (first, second) pair of vertex indices
    /// @return true if edge has been removed, false otherwise (e.g. there was no such edge)
    virtual auto disconnect(Vertex_pair edge)
      -> bool = 0;

    /// @brief Remove edge from -> to.
    /// @param from the index of the outcoming vertex
    /// @param to   the index of the incoming vertex
    /// @return true if edge has been removed, false otherwise (e.g. there was no such edge) 
    auto disconnect(Vertex_index from, Vertex_index to)
      -> bool { return disconnect(Vertex_pair{ from, to }); }

    /// @brief Copy all edges of gv into this graph.
    /// @param gv source graph object
    /// @return how many edges of gv have been inserted into this graph
    auto copy_from(Graph_view const& gv)
      -> Scalar_size
    {
      Scalar_size added_edges = 0;
      Scalar_size const verts = max(vertex_count(), gv.vertex_count());
      set_vertex_count(verts);

      auto gv_edge_iter = gv.iterate_edges();
      for (Vertex_pair vp; gv_edge_iter->next(vp);)
        if (connect(vp))
          ++added_edges;

      return added_edges;
    }

  protected:
    Graph_view& operator=(Graph_view const&) = default;
    Graph_view& operator=(Graph_view&&) = default;
  };


  /// @brief Read-write graph view object owning pointer.
  using Graph_view_uptr = std::unique_ptr<Graph_view>;

  /// @brief Read-only graph view object owning pointer.
  using Graph_view_const_uptr = std::unique_ptr<Graph_view const>;

}

#endif//OGXX_GRAPH_VIEW_HPP_INCLUDED
