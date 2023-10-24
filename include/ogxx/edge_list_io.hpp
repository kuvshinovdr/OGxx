/// @file edge_list_io.hpp
/// @brief Textual input-output for edge list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_EDGE_LIST_IO_HPP_INCLUDED
#define OGXX_EDGE_LIST_IO_HPP_INCLUDED

#include "edge_list.hpp"

#include <string_view>
#include <istream>
#include <ostream>


/// IO operations for OGxx objects
namespace ogxx::io
{
  using std::string_view;
  using namespace std::string_view_literals;


  /// @brief Description of Edge_list IO format.
  struct Edge_list_format
  {
    string_view list_open   = "edge_list\n{\n"sv; ///< the opening token for the entire list
    string_view list_close  = "}\n"sv;            ///< the closing token for the entire list
    string_view pair_open   = "  ("sv;            ///< the opening token for an edge (a pair of vertex indices)
    string_view pair_close  = ")\n"sv;            ///< the closing token for an edge
    string_view pair_sep    = ", "sv;             ///< the separator inserted between vertex indices in the pair
  };


  /// @brief Print an edge list representation into an ostream object.
  /// @param os      the output stream object, to which the printing is done
  /// @param el      the Edge_list object being printed
  /// @param format  edge list format description
  /// @return os
  auto print(std::ostream& os, ogxx::Edge_list const& el, Edge_list_format const& format = {})
    -> std::ostream&;

  /// @brief Print an edge list representation into cout (standard output).
  /// @param el      the Edge_list object being printed
  /// @param format  edge list format description
  /// @return reference to std::cout
  auto print(ogxx::Edge_list const& el, Edge_list_format const& format = {})
    -> std::ostream&;

}

#endif//OGXX_EDGE_LIST_IO_HPP_INCLUDED
