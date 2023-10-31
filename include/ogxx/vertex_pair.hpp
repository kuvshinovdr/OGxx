/// @file vertex_pair.hpp
/// @brief Vertex pair related type declarations.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_VERTEX_PAIR_HPP_INCLUDED
#define OGXX_VERTEX_PAIR_HPP_INCLUDED

#include "primitive_definitions.hpp"
#include "iterable.hpp"


/// Root namespace of the OGxx library.
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

}

#endif//OGXX_VERTEX_PAIR_HPP_INCLUDED
