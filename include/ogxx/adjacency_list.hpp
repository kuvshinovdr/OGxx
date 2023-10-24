/// @file adjacency_list.hpp
/// @brief Adjacency list graph representation interface
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ADJACENCY_LIST_HPP_INCLUDED
#define OGXX_ADJACENCY_LIST_HPP_INCLUDED

#include "iterable.hpp"
#include "st_set.hpp"


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
    
  };


  /// @brief Graph representation where, which maps vertex index to the adjacency of that vertex.
  class Adjacency_list 
    : public virtual Indexed_iterable<Adjacency*>
  {
  public:
    /// @brief Compute the sum of sizes of all adjacencies (vertex degrees).
    /// It is equivalent to quantity of arrows in a directed graph and twice the quantity of edges in an undirected graph.
    /// @return the sum of vertex degrees
    virtual auto degrees_sum() const noexcept
      -> Scalar_size = 0;
  };

}

#endif//OGXX_ADJACENCY_LIST_HPP_INCLUDED
