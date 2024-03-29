/// @file edge_list.hpp
/// @brief Graph edge list interface.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_EDGE_LIST_HPP_INCLUDED
#define OGXX_EDGE_LIST_HPP_INCLUDED

#include <ogxx/iterable.hpp>
#include <ogxx/graph_view.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Interface (abstract base class) for storing an edge list of a graph.
  class Edge_list
    : public virtual Bag<Vertex_pair>
  {
  public:
    /// @brief Finds the index of an edge in the list
    /// @param edge the pair of indices of the vertices comprising the edge
    /// @return found index or ogxx::npos if the edge has not been found
    virtual auto find(Vertex_pair edge) const noexcept
      -> Scalar_index = 0;

    /// @brief Compute maximal vertex index occuring in vertex pairs contained in this edge list.
    /// This method might have been implemented as an external function calling iterate instead.
    /// @return maximal vertex index >= 0 or -1 if the edge list is empty
    virtual auto max_vertex_index() const noexcept
      -> Vertex_index = 0;
  };

  
  /// @brief Owning pointer to an edge list.
  using Edge_list_uptr = std::unique_ptr<Edge_list>;

  /// @brief Owning pointer to a read-only edge list.
  using Edge_list_const_uptr = std::unique_ptr<Edge_list const>;

  
  /// @brief Create an empty edge list represented by an std::vector<Vertex_pair>.
  [[nodiscard]] auto new_edge_list_vector() 
    -> Edge_list_uptr;

  /// @brief Create an edge list represented by a std::vector of Vertex_pairs listed by the iterator.
  [[nodiscard]] auto new_edge_list_vector(Vertex_pair_iterator_uptr) 
    -> Edge_list_uptr;

  /// @brief Create an edge list represented by a std::vector of Vertex_pairs provided by the list.
  [[nodiscard]] auto new_edge_list_vector(std::initializer_list<Vertex_pair>) 
    -> Edge_list_uptr;


  /// @brief Create an empty edge list represented by an std::unordered_set<Vertex_pair>.
  [[nodiscard]] auto new_edge_list_hashtable() 
    -> Edge_list_uptr;

  /// @brief Create an edge list represented by a std::unordered_set of Vertex_pairs listed by the iterator.
  [[nodiscard]] auto new_edge_list_hashtable(Vertex_pair_iterator_uptr)
    -> Edge_list_uptr;

  /// @brief Create an edge list represented by a std::unordered_set of Vertex_pairs provided by the list.
  [[nodiscard]] auto new_edge_list_hashtable(std::initializer_list<Vertex_pair>) 
    -> Edge_list_uptr;


  /// Directed graph facilities.
  namespace directed
  {

    /// @brief Create a read-only graph view for an edge list as a directed graph.
    /// @param el viewed edge list, must live while the result graph view is being used
    /// @return a graph view read-only object
    [[nodiscard]] auto graph_view(Edge_list const& el)
      -> Graph_view_const_uptr;

    /// @brief Create a read-write graph view for an edge list as a directed graph.
    /// @param el viewed edge list, must live while the result graph view is being used
    /// @return a graph view read-write object
    [[nodiscard]] auto graph_view(Edge_list& el)
      -> Graph_view_uptr;

  }

  /// Undirected graph facilities.
  namespace undirected
  {

    /// @brief Create a read-only graph view for an edge list as an undirected graph.
    /// @param el viewed edge list, must live while the result graph view is being used
    /// @return a graph view read-only object
    [[nodiscard]] auto graph_view(Edge_list const& el)
      -> Graph_view_const_uptr;

    /// @brief Create a read-write graph view for an edge list as an undirected graph.
    /// @param el viewed edge list, must live while the result graph view is being used
    /// @return a graph view read-write object
    [[nodiscard]] auto graph_view(Edge_list& el)
      -> Graph_view_uptr;

  }

}

#endif//OGXX_EDGE_LIST_HPP_INCLUDED
