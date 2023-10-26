/// @file edge_list.hpp
/// @brief Graph edge list interface.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_EDGE_LIST_HPP_INCLUDED
#define OGXX_EDGE_LIST_HPP_INCLUDED

#include "vertex_pair.hpp"


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// @brief Interface (abstract base class) for storing an edge list of a graph.
  /// Indexed_iterable of Vertex_pair, throws on out-of-range?
  class Edge_list
    : public virtual List<Vertex_pair>
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

}

#endif//OGXX_EDGE_LIST_HPP_INCLUDED
