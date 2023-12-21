/// @file bit_matrix_io_print.cpp
/// @brief Bit_matrix printing operations.
/// @author 

#include <ogxx/bit_matrix_io.hpp>
#include <iostream>


/// IO operations for OGxx objects
namespace ogxx::io
{

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
  auto print(std::ostream& os, ogxx::Bit_matrix const& bm, Bit_matrix_format const& format)
    -> std::ostream&
    {
        auto shape = bm.shape();
        Matrix_index position {};
        os<<format.matrix_open;
        for (;position.row < shape.rows; ++position.row)
        {
            for(;position.col < shape.cols; ++position.col)
            {

                os<<(bm.get(position)? format.one : format.zero);
                if ((position.col +1) % format.column_stride == 0 && position.col != shape.cols -1 )
                    os<<' ';

            }
            os<<'\n';
        
        }
        os<<format.matrix_close;
        return os;
    }
  /// @brief Print a bit matrix representation into cout (standard output).
  /// @param bm      the Bit_matrix object being printed
  /// @param format  bit matrix format description
  /// @return reference to std::cout
  auto print(ogxx::Bit_matrix const& bm, Bit_matrix_format const& format)
    -> std::ostream&
    {
        return print(std::cout , bm, format);
    } 

}
