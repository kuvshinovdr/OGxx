/// @file edge_list.hpp
/// @brief Graph edge list interface.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_EDGE_LIST_HPP_INCLUDED
#define OGXX_EDGE_LIST_HPP_INCLUDED

#include "primitive_definitions.hpp"
#include "iterable.hpp"


namespace ogxx
{

  /// @brief Unique identifier of a vertex within a graph.
  using Vertex_index = Scalar_index;

  /// @brief Edge of a graph may be represented by a pair of vertices.
  using Vertex_pair = std::pair<Vertex_index, Vertex_index>;

  /// @brief Iterator object for enumerating a vertex pair (edge) list.
  using Vertex_pair_iterator = Basic_iterator<Vertex_pair>;

  /// @brief An owning pointer to a Vertex_pair_iterator object.
  using Vertex_pair_iterator_uptr = std::unique_ptr<Vertex_pair_iterator>;

  /// @brief Interface (abstract base class) for storing an edge list of a graph.
  /// Indexed_iterable of Vertex_pair, throws on out-of-range?
  class Edge_list: public Indexed_iterable<Vertex_pair>
  {
  public:
    virtual ~Edge_list() {}

    /// @brief Finds the index of an edge in the list
    /// @param edge the pair of indices of the vertices comprising the edge
    /// @return found index or ogxx::npos if the edge has not been found
    virtual auto find(Vertex_pair edge) const noexcept
      -> Scalar_index = 0;
  };

}

#endif//OGXX_EDGE_LIST_HPP_INCLUDED
