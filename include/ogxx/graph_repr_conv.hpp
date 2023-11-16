/// @file graph_repr_conv.hpp
/// @brief Graph representation conversion operations.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
/// E.g. we have an Edge_list el and an Adjacency_list al, then we can convert from el to al using the call:
///   undirected::convert::from(el).to(al)
/// if el stores an undirected graph.
/// Can we remove the duplication directed-undirected (the same-looking code calls different functions graph_view)?
#ifndef OGXX_GRAPH_REPR_CONV_HPP_INCLUDED
#define OGXX_GRAPH_REPR_CONV_HPP_INCLUDED

#include <ogxx/graph_view.hpp>
#include <ogxx/adjacency_list.hpp>
#include <ogxx/bit_matrix.hpp>
#include <ogxx/edge_list.hpp>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /// Directed graph conversion.
  namespace directed::convert
  {

    /// @brief A flow-interface implementation, holds "from" adapter graph view and does "to" directed graph conversion.
    class Convertor
    {
    public:
      /// @brief Initialize the "from" adapter graph view.
      /// @param from graph view read-only object with ownership translation
      Convertor(Graph_view_const_uptr from) noexcept
        : _from(std::move(from)) {}

      /// @brief Convert to an adjacency list.
      /// @param al an adjacency list object to be filled
      void to(Adjacency_list& al) const
      {
        graph_view(al)->copy_from(*_from);
      }

      /// @brief Convert to an adjacency matrix.
      /// @param am a bit matrix representing the adjacency matrix to be filled
      void to(Bit_matrix& am) const
      {
        graph_view(am)->copy_from(*_from);
      }

      /// @brief Convert to an edge list.
      /// @param el an edge list object to be filled
      void to(Edge_list& el) const
      {
        graph_view(el)->copy_from(*_from);
      }

    private:
      Graph_view_const_uptr _from;
    };


    /// @brief Convert from an adjacency list to another representation.
    /// @param al a reference to an adjacency list object
    /// @return Convertor object (then use .to(target))
    [[nodiscard]] inline auto from(Adjacency_list const& al)
      -> Convertor { return { graph_view(al) }; }

    /// @brief Convert from an adjacency matrix to another representation.
    /// @param al a reference to an adjacency matrix (Bit_matrix) object
    /// @return Convertor object (then use .to(target))
    [[nodiscard]] inline auto from(Bit_matrix const& am)
      -> Convertor { return { graph_view(am) }; }

    /// @brief Convert from an edge list to another representation.
    /// @param al a reference to an edge list object
    /// @return Convertor object (then use .to(target))
    [[nodiscard]] inline auto from(Edge_list const& el)
      -> Convertor { return { graph_view(el) }; }

  }

  /// Undirected graph conversion.
  namespace undirected::convert
  {

    /// @brief A flow-interface implementation, holds "from" adapter graph view and does "to" directed graph conversion.
    class Convertor
    {
    public:
      /// @brief Initialize the "from" adapter graph view.
      /// @param from graph view read-only object with ownership translation
      Convertor(Graph_view_const_uptr from) noexcept
        : _from(std::move(from)) {}

      /// @brief Convert to an adjacency list.
      /// @param al an adjacency list object to be filled
      void to(Adjacency_list& al) const
      {
        graph_view(al)->copy_from(*_from);
      }

      /// @brief Convert to an adjacency matrix.
      /// @param am a bit matrix representing the adjacency matrix to be filled
      void to(Bit_matrix& am) const
      {
        graph_view(am)->copy_from(*_from);
      }

      /// @brief Convert to an edge list.
      /// @param el an edge list object to be filled
      void to(Edge_list& el) const
      {
        graph_view(el)->copy_from(*_from);
      }

    private:
      Graph_view_const_uptr _from;
    };


    /// @brief Convert from an adjacency list to another representation.
    /// @param al a reference to an adjacency list object
    /// @return Convertor object (then use .to(target))
    [[nodiscard]] inline auto from(Adjacency_list const& al)
      -> Convertor { return { graph_view(al) }; }

    /// @brief Convert from an adjacency matrix to another representation.
    /// @param al a reference to an adjacency matrix (Bit_matrix) object
    /// @return Convertor object (then use .to(target))
    [[nodiscard]] inline auto from(Bit_matrix const& am)
      -> Convertor { return { graph_view(am) }; }

    /// @brief Convert from an edge list to another representation.
    /// @param al a reference to an edge list object
    /// @return Convertor object (then use .to(target))
    [[nodiscard]] inline auto from(Edge_list const& el)
      -> Convertor { return { graph_view(el) }; }

  }

}

#endif//OGXX_GRAPH_REPR_CONV_HPP_INCLUDED
