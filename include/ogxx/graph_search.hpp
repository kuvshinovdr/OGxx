/// @file ogxx/graph_search.hpp
/// @brief Generic (unweighted) graph search facility.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_GRAPH_SEARCH_HPP_INCLUDED
#define OGXX_GRAPH_SEARCH_HPP_INCLUDED
#include <ogxx/iterable.hpp>
#include <ogxx/st_set.hpp>
#include <ogxx/graph_view.hpp>

namespace ogxx
{
 
  // Predeclaration.
  class Graph_search_controller {};
  using Graph_search_controller_uptr = std::unique_ptr<Graph_search_controller>;

  /// @brief Generic unweighted graph search.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param visited_vertices   the storage for already visited vertices, it may be used to prohibit visiting certain vertices in ahead
  /// @param vertex_order       the storage for open vertices, it defines the order of searching
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto graph_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Index_set_uptr visited_vertices,
    Index_bag_uptr vertex_order,
    Graph_search_controller_uptr controller
  ) -> bool;


  /// @brief Generic unweighted graph search.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param vertex_order       the storage for open vertices, it defines the order of searching
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto graph_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Index_bag_uptr vertex_order,
    Graph_search_controller_uptr controller
  ) -> bool;


  /// @brief Depth-first graph search, equivalent to graph_search using a stack for vertex_order.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param visited_vertices   the storage for already visited vertices, it may be used to prohibit visiting certain vertices in ahead
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto depth_first_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Index_set_uptr visited_vertices,
    Graph_search_controller_uptr controller
  ) -> bool;


  /// @brief Depth-first graph search, equivalent to graph_search using a stack for vertex_order.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto depth_first_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Graph_search_controller_uptr controller
  ) -> bool;


  /// @brief Breadth-first graph search, equivalent to graph_search using a queue for vertex_order.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param visited_vertices   the storage for already visited vertices, it may be used to prohibit visiting certain vertices in ahead
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto breadth_first_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Index_set_uptr visited_vertices,
    Graph_search_controller_uptr controller
  ) -> bool;


  /// @brief Breadth-first graph search, equivalent to graph_search using a queue for vertex_order.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto breadth_first_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Graph_search_controller_uptr controller
  ) -> bool;


  /// @brief Random-first graph search, equivalent to graph_search using a randomly selecting bag for vertex_order.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param visited_vertices   the storage for already visited vertices, it may be used to prohibit visiting certain vertices in ahead
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto random_first_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Index_set_uptr visited_vertices,
    Graph_search_controller_uptr controller
  ) -> bool;


  /// @brief Random-first graph search, equivalent to graph_search using a randomly selecting bag for vertex_order.
  /// @param start_index        the vertex to start from
  /// @param graph              the graph on which we search (using iterate_neighbors method)
  /// @param controller         the object whom the search reports enumerated edges to, it may finish the search before exhaustion
  /// @return true if the search has been finished by the controller, false if the search has been finished by exhaustion
  auto random_first_search(
    Vertex_index start_index,
    Graph_view const& graph,
    Graph_search_controller_uptr controller
  ) -> bool;

}

#endif//OGXX_GRAPH_SEARCH_HPP_INCLUDED
