/// @file edge_list_io.hpp
/// @brief Textual input-output for edge list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_EDGE_LIST_IO_HPP_INCLUDED
#define OGXX_EDGE_LIST_IO_HPP_INCLUDED

#include "io_head.hpp"
#include "edge_list.hpp"


/// IO operations for OGxx objects
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

  // An example of an edge list provided in the default format as stated above:
  // 
  //>   edge_list
  //>   {
  //>     (1, 2)
  //>     (0, 2)
  //>     (0, 3)
  //>   }

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
