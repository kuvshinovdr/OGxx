/// @file adjacency_list.hpp
/// @brief Adjacency list graph representation interface
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ADJACENCY_LIST_HPP_INCLUDED
#define OGXX_ADJACENCY_LIST_HPP_INCLUDED

#include <ogxx/st_set.hpp>
#include <ogxx/graph_view.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Representation of adjacent vertices of a vertex of a graph.
  /// Vertex degree is the size of the adjacency.
  class Adjacency 
    : public virtual Index_set
    , public virtual Sized_iterable<Scalar_index>
  {
  public:
    // Do we need to add anything here?
  };

  /// @brief Owning read-write Adjacency object pointer.
  using Adjacency_uptr = std::unique_ptr<Adjacency>;

  /// @brief Owning read-only Adjacency object pointer.
  using Adjacency_const_uptr = std::unique_ptr<Adjacency const>;

  /// Create a new empty Adjacency object based upon Index hashtable.
  [[nodiscard]] auto new_adjacency_hashtable()
    -> Adjacency_uptr;


  /// @brief Graph representation where, which maps vertex index to the adjacency of that vertex.
  class Adjacency_list 
    : public virtual List<Adjacency>
  {
  public:
    /// @brief Compute the sum of sizes of all adjacencies (vertex degrees).
    /// It is equivalent to quantity of arrows in a directed graph and twice the quantity of edges in an undirected graph.
    /// @return the sum of vertex degrees
    virtual auto degrees_sum() const noexcept
      -> Scalar_size = 0;

    /// @brief Add or remove vertices.
    /// When removing vertices remove all edges incident with the removed vertices.
    /// @param new_vertex_count how many vertices the list should represent after this call (vertices have indices 0, 1, ..., new_vertex_count - 1)
    virtual void set_vertex_count(Scalar_size new_vertex_count) = 0;
  };


  /// Directed graph facilities.
  namespace directed
  {

    /// @brief Create a read-only graph view for an adjacency list of a directed graph.
    /// @param al viewed adjacency list, must live while the result graph view is being used
    /// @return a graph view read-only object
    [[nodiscard]] auto graph_view(Adjacency_list const& al)
      -> Graph_view_const_uptr;

    /// @brief Create a read-write graph view for an adjacency list of a directed graph.
    /// @param al viewed adjacency list, must live while the result graph view is being used
    /// @return a graph view read-write object
    [[nodiscard]] auto graph_view(Adjacency_list& al)
      -> Graph_view_uptr;

  }

  /// Undirected graph facilities.
  namespace undirected
  {

    /// @brief Create a read-only graph view for an adjacency list of an undirected graph.
    /// @param al viewed adjacency list, must live while the result graph view is being used
    /// @return a graph view read-only object
    [[nodiscard]] auto graph_view(Adjacency_list const& al)
      -> Graph_view_const_uptr;

    /// @brief Create a read-write graph view for an adjacency list of an undirected graph.
    /// @param al viewed adjacency list, must live while the result graph view is being used
    /// @return a graph view read-write object
    [[nodiscard]] auto graph_view(Adjacency_list& al)
      -> Graph_view_uptr;

  }

}

#endif//OGXX_ADJACENCY_LIST_HPP_INCLUDED