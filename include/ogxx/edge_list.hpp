/// @file edge_list.hpp
/// @brief Graph edge list interface.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_EDGE_LIST_HPP_INCLUDED
#define OGXX_EDGE_LIST_HPP_INCLUDED

#include "primitive_definitions.hpp"
#include "iterator.hpp"


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
  class Edge_list
  {
  public:
    virtual ~Edge_list() {}

    /// @brief Get the size of the list.
    /// @return how many edges we store here
    virtual auto size() const noexcept
      -> Scalar_size = 0;

    /// @brief Get an edge description by its index in the list
    /// @param edge_index which edge we want to get
    /// @return the edge represented by a pair of vertex indices, TODO: throw on out of range?
    virtual auto get(Scalar_index edge_index) const
      -> Vertex_pair = 0;

    /// @brief Finds the index of an edge in the list
    /// @param edge the pair of indices of the vertices comprising the edge
    /// @return found index or npos if the edge has not been found
    virtual auto find(Vertex_pair edge) const noexcept
      -> Scalar_index = 0;

    /// @brief Create an iterator to go through all vertex pairs (edges) stored in the list.
    /// @return an owning pointer to an iterator
    virtual auto iterate() const
      -> Vertex_pair_iterator_uptr = 0;

  protected:
    Edge_list& operator=(Edge_list const&) = default;
    Edge_list& operator=(Edge_list&&) = default;
  };

}

#endif//OGXX_EDGE_LIST_HPP_INCLUDED
