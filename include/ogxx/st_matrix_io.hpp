/// @file st_matrix_io.hpp
/// @brief St_matrix reading and printing operations.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ST_MATRIX_IO_HPP_INCLUDED
#define OGXX_ST_MATRIX_IO_HPP_INCLUDED

#include "io_head.hpp"
#include "st_matrix.hpp"


/// IO operations for OGxx objects
namespace ogxx::io
{

  /// @brief Description of St_matrix IO format.
  struct St_matrix_format
  {
    string_view matrix_open  = "matrix\n{\n"sv; ///< the opening token for the entire matrix
    string_view matrix_close = "}\n"sv;         ///< the closing token for the entire matrix
    string_view column_sep   = ", ";             ///< column separator inserted between elements
    string_view row_sep      = ";\n";            ///< row separator inserted between rows
    int precision            = 0;                ///< precision for floats, 0 means use the default one
    int element_width        = 0;                ///< how many characters use for element value, 0 means minimal
  };

  // An example of an integer matrix (4x3) provided in the default format as stated above:
  // 
  //>   matrix
  //>   {
  //>     1,  5,  16;
  //>     13, 1,  -60;
  //>     1,  0,  0;
  //>     80, 33, 345
  //>   }

  /// @brief Print an integer matrix representation into an ostream object.
  /// @param os      the output stream object, to which the printing is done
  /// @param bm      the Int_matrix object being printed
  /// @param format  matrix format description
  /// @return os
  auto print(std::ostream& os, ogxx::Int_matrix const& bm, St_matrix_format const& format = {})
    -> std::ostream&;

  /// @brief Print an integer matrix representation into cout (standard output).
  /// @param bm      the Int_matrix object being printed
  /// @param format  matrix format description
  /// @return reference to std::cout
  auto print(ogxx::Int_matrix const& bm, St_matrix_format const& format = {})
    -> std::ostream&;

  /// @brief Read (parse) an integer matrix representation from an istream object.
  /// @param is      the input stream object
  /// @param bm      the Int_matrix object being read
  /// @param format  matrix format description
  /// @return is
  auto read(std::istream& is, ogxx::Int_matrix& bm, St_matrix_format const& format)
    -> std::istream&;

  /// @brief Read (parse) an integer matrix representation from std::cin.
  /// @param bm      the Int_matrix object being read
  /// @param format  matrix format description
  /// @return reference to std::cin
  auto read(ogxx::Int_matrix& bm, St_matrix_format const& format)
    -> std::istream&;

  /////////////////////////////////////////////////////////////////////////////

  /// @brief Print a float matrix representation into an ostream object.
  /// @param os      the output stream object, to which the printing is done
  /// @param bm      the Float_matrix object being printed
  /// @param format  matrix format description
  /// @return os
  auto print(std::ostream& os, ogxx::Float_matrix const& bm, St_matrix_format const& format = {})
    -> std::ostream&;

  /// @brief Print a float matrix representation into cout (standard output).
  /// @param bm      the Float_matrix object being printed
  /// @param format  matrix format description
  /// @return reference to std::cout
  auto print(ogxx::Float_matrix const& bm, St_matrix_format const& format = {})
    -> std::ostream&;

  /// @brief Read (parse) a float matrix representation from an istream object.
  /// @param is      the input stream object
  /// @param bm      the Float_matrix object being read
  /// @param format  matrix format description
  /// @return is
  auto read(std::istream& is, ogxx::Float_matrix& bm, St_matrix_format const& format)
    -> std::istream&;

  /// @brief Read (parse) a float matrix representation from std::cin.
  /// @param bm      the Float_matrix object being read
  /// @param format  matrix format description
  /// @return reference to std::cin
  auto read(ogxx::Float_matrix& bm, St_matrix_format const& format)
    -> std::istream&;

}

#endif//OGXX_ST_MATRIX_IO_HPP_INCLUDED
