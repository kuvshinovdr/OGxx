#ifndef OGXX_EDGE_LIST_IO_HPP_INCLUDED
#define OGXX_EDGE_LIST_IO_HPP_INCLUDED
#include "io_head.hpp"
#include "edge_list.hpp"

namespace ogxx::io
{

  /// @brief Description of Edge_list IO format.
  struct Edge_list_format
  {
    string_view list_open   = "edge_list\n{\n"sv; ///< the opening token for the entire list
    string_view list_close  = "}\n"sv;            ///< the closing token for the entire list
    string_view pair_open   = "  ("sv;            ///< the opening token for an edge (a pair of vertex indices)
    string_view pair_close  = ")\n"sv;            ///< the closing token for an edge
    string_view pair_sep    = ", "sv;             ///< the separator inserted between vertex indices in the pair
  };

  /// @brief Read (parse) an edge list representation from an istream object by clearing and putting vertex pairs.
  /// @param is      the input stream object
  /// @param el      the Edge_list object being filled with the edges read from is
  /// @param format  edge list format description
  /// @return is
  auto read(std::istream& is, ogxx::Edge_list& el, Edge_list_format const& format)
    -> std::istream&;

  /// @brief Read (parse) an edge list representation from std::cin by clearing and putting vertex pairs.
  /// @param el      the Edge_list object being filled with the edges read from is
  /// @param format  edge list format description
  /// @return reference to std::cin
  auto read(ogxx::Edge_list& el, Edge_list_format const& format)
    -> std::istream&;

}
#endif//OGXX_EDGE_LIST_IO_HPP_INCLUDED