/// @file adjacency_list_io.hpp
/// @brief Textual input-output for adjacency list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ADJACENCY_LIST_IO_HPP_INCLUDED
#define OGXX_ADJACENCY_LIST_IO_HPP_INCLUDED

#include <ogxx/io_head.hpp>
#include <ogxx/adjacency_list.hpp>


/// IO operations for OGxx objects
namespace ogxx::io
{

  /// @brief Description of Adjacency_list IO format.
  struct Adjacency_list_format
  {
    string_view list_open  = "adjacency_list\n{\n"sv; ///< the opening token for the entire list
    string_view list_close = "}\n"sv;                 ///< the closing token for the entire list
    string_view adjacency_open  = "  ["sv;            ///< the opening token for an adjacency (a sequence of vertex indices)
    string_view adjacency_close = "]\n"sv;            ///< the closing token for an adjacency
    string_view adjacency_sep   = ", "sv;             ///< the separator inserted between vertex indices inside the adjacency
  };

  // An example of an adjacency list provided in the default format as stated above:
  // 
  //>   adjacency_list
  //>   {
  //>     0 [1, 2, 3]
  //>     1 [0, 3]
  //>     2 [0, 3]
  //>     3 [0, 1, 2]
  //>   }

  /// @brief Print an adjacency list representation into an ostream object.
  /// @param os      the output stream object, to which the printing is done
  /// @param al      the Adjacency_list object being printed
  /// @param format  adjacency list format description
  /// @return os
  auto print(std::ostream& os, ogxx::Adjacency_list const& al, Adjacency_list_format const& format = {})
    -> std::ostream&;

  /// @brief Print an adjacency list representation into cout (standard output).
  /// @param el      the Adjacency_list object being printed
  /// @param format  adjacency list format description
  /// @return reference to std::cout
  auto print(ogxx::Adjacency_list const& al, Adjacency_list_format const& format = {})
    -> std::ostream&;

  /// @brief Read (parse) an adjacency list representation from a string_view object by clearing and putting vertex pairs.
  /// @param in      the input character sequence, remove the prefix that was read
  /// @param al      the Adjacency_list object being filled with the edges read from in
  /// @param format  the adjacency list format description
  /// @return true on successful reading, false otherwise
  auto read(std::string_view& in, ogxx::Adjacency_list& al, Adjacency_list_format const& format)
    -> bool;

}

#endif//OGXX_ADJACENCY_LIST_IO_HPP_INCLUDED
