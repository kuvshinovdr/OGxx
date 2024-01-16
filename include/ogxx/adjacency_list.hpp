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

  // Adjacencies

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

  /// @brief Create a new empty Adjacency object based upon Index hashtable.
  [[nodiscard]] auto new_adjacency_hashtable()
    -> Adjacency_uptr;

  /// @brief Create a new Adjacency object based upon Index hashtable and fill it with indices provided by an iterator.
  [[nodiscard]] auto new_adjacency_hashtable(Index_iterator_uptr)
    -> Adjacency_uptr;


  /// @brief Create a new empty Adjacency object based upon Index bitvector.
  [[nodiscard]] auto new_adjacency_bitvector()
    -> Adjacency_uptr;

  /// @brief Create a new Adjacency object based upon Index bitvector and fill it with indices provided by an iterator.
  [[nodiscard]] auto new_adjacency_bitvector(Index_iterator_uptr items)
    -> Adjacency_uptr;


  /// @brief Create a new empty Adjacency object based upon Index sorted vector.
  [[nodiscard]] auto new_adjacency_sortedvector()
    -> Adjacency_uptr;

  /// @brief Create a new Adjacency object based upon Index sorted vector and fill it with indices provided by an iterator.
  [[nodiscard]] auto new_adjacency_sortedvector(Index_iterator_uptr items)
    -> Adjacency_uptr;


  // Adjacency lists

  /// @brief Entries describing an adjacency list via iterating it.
  struct Adjacency_list_entry
  {
    /// @brief Index of a vertex, which adjacency we've got.
    Vertex_index vertex    = npos;
    /// @brief Adjacency of the vertex (may be nullptr if the vertex is an isolated vertex).
    Adjacency*   adjacency = nullptr;
  };


  /// @brief Graph representation where, which maps vertex index to the adjacency of that vertex.
  class Adjacency_list
    : public virtual Indexed_iterable<Adjacency_list_entry>
  {
  public:
    /// @brief Remove everything making the list empty.
    virtual void clear() = 0;

    /// @brief Compute the sum of sizes of all adjacencies (vertex degrees).
    /// It is equivalent to quantity of arrows in a directed graph and twice the quantity of edges in an undirected graph.
    /// @return the sum of vertex degrees
    virtual auto degrees_sum() const noexcept
      -> Scalar_size = 0;

    /// @brief Get maximal known vertex index plus one.
    virtual auto get_vertex_count() const noexcept
      -> Scalar_size = 0;

    /// @brief Add or remove vertices.
    /// When removing vertices remove all edges incident with the removed vertices.
    /// @param new_vertex_count how many vertices the list should represent after this call (vertices have indices 0, 1, ..., new_vertex_count - 1)
    virtual void set_vertex_count(Scalar_size new_vertex_count) = 0;
  };


  /// @brief Owning pointer to an object of an adjacency list.
  using Adjacency_list_uptr = std::unique_ptr<Adjacency_list>;
  /// @brief Owning pointer to a read-only object of an adjacency list.
  using Adjacency_list_const_uptr = std::unique_ptr<Adjacency_list const>;

  /// @brief Create an empty adjacency list based upon a hashtable.
  /// @return An owning pointer to an Adjacency_list_hashtable object.
  [[nodiscard]] auto new_adjacency_list_hashtable()
    -> Adjacency_list_uptr;


  /// @brief Directed graph facilities.
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

  /// @brief Undirected graph facilities.
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
