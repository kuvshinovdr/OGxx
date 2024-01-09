/// @file subgraph_checks.hpp
/// @brief Given a set of vertex indices of a subgraph in a graph check if the subgraph is of a given class, has some property.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_SUBGRAPH_CHECKS_HPP_INCLUDED
#define OGXX_SUBGRAPH_CHECKS_HPP_INCLUDED

#include <ogxx/graph_view.hpp>

#include <optional>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Check if a set of vertices are connected into a chain.
  /// @param gv       a graph containing the vertices
  /// @param vertices an iterator enumerating vertex indices
  /// @return true if the vertices being enumerated are connected into a chain
  [[nodiscard]] auto is_chain(Graph_view const& gv, Index_iterator_uptr vertices)
    -> bool;

  /// @brief Check if a set of vertices are connected into a loop.
  /// @param gv       a graph containing the vertices
  /// @param vertices an iterator enumerating vertex indices
  /// @return true if the vertices being enumerated are connected into a loop
  [[nodiscard]] auto is_loop(Graph_view const& gv, Index_iterator_uptr vertices)
    -> bool;

  /// @brief Check if a subgraph (of an undirected graph) is a star.
  /// @param gv       a graph
  /// @param vertices an iterator enumerating vertex indices
  /// @return star center vertex index if the subgraph is a star, nothing otherwise
  [[nodiscard]] auto is_star(Graph_view const& gv, Index_iterator_uptr vertices)
    -> std::optional<Vertex_index>;


  /// @brief Directed graph facilities.
  namespace directed
  {
    /// @brief Check if a subgraph of a directed graph spanning over the given set of vertices is an independent set (that there are no edges between vertices in the graph).
    /// @param gv       a graph view representing the graph
    /// @param vertices an iterator listing vertex indices of the subgraph 
    /// @return true if the subraph is an independent set, false otherwise
    [[nodiscard]] auto is_independent_set(Graph_view const& gv, Index_iterator_uptr vertices)
      -> bool;
  }

  /// @brief Undirected graph facilities.
  namespace undirected
  {
    /// @brief Check if a subgraph of an undirected graph spanning over the given set of vertices is an independent set (that there are no edges between vertices in the graph).
    /// @param gv       a graph view representing the graph
    /// @param vertices an iterator listing vertex indices of the subgraph 
    /// @return true if the subraph is an independent set, false otherwise
    [[nodiscard]] auto is_independent_set(Graph_view const& gv, Index_iterator_uptr vertices)
      -> bool;
  }

}

#endif//OGXX_SUBGRAPH_CHECKS_HPP_INCLUDED
