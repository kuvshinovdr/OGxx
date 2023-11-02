/// @file bit_matrix_io.hpp
/// @brief Bit_matrix reading and printing operations.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_BIT_MATRIX_IO_HPP_INCLUDED
#define OGXX_BIT_MATRIX_IO_HPP_INCLUDED

#include <ogxx/io_head.hpp>
#include <ogxx/bit_matrix.hpp>


/// IO operations for OGxx objects
namespace ogxx::io
{

  /// @brief Description of Bit_matrix IO format.
  struct Bit_matrix_format
  {
    string_view matrix_open   = "bit_matrix\n{\n"sv; ///< the opening token for the entire matrix
    string_view matrix_close  = "}\n"sv;             ///< the closing token for the entire matrix
    char        zero          = '0';                 ///< representation of "false" cell value
    char        one           = '1';                 ///< representation of "true" cell value
    int         column_stride = 4;                   ///< insert a space in a row after each four columns
  };

  // An example of a bit matrix (3x6) provided in the default format as stated above:
  // 
  //>   bit_matrix
  //>   {
  //>     0100 01
  //>     1011 00
  //>     0110 01
  //>   }

  /// @brief Print a bit matrix representation into an ostream object.
  /// @param os      the output stream object, to which the printing is done
  /// @param bm      the Bit_matrix object being printed
  /// @param format  bit matrix format description
  /// @return os
  auto print(std::ostream& os, ogxx::Bit_matrix const& bm, Bit_matrix_format const& format = {})
    -> std::ostream&;

  /// @brief Print a bit matrix representation into cout (standard output).
  /// @param bm      the Bit_matrix object being printed
  /// @param format  bit matrix format description
  /// @return reference to std::cout
  auto print(ogxx::Bit_matrix const& bm, Bit_matrix_format const& format = {})
    -> std::ostream&;

  /// @brief Read (parse) a bit matrix representation from an istream object.
  /// @param in      the input character sequence, remove the prefix that was read (on success)
  /// @param bm      the Bit_matrix object being filled with the ones and zeroes from is
  /// @param format  bit matrix format description
  /// @return true on successful reading, false otherwise
  auto read(std::string_view& in, ogxx::Bit_matrix& bm, Bit_matrix_format const& format)
    -> bool;

}

#endif//OGXX_BIT_MATRIX_IO_HPP_INCLUDED
