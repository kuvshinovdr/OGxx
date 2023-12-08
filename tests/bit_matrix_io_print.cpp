/// @file bit_matrix_io_print.cpp
/// @brief test for print bit matrix
/// @author Mansurov Sh.
#include "testing_head.hpp"
//#include <source/dense_bit_matrix.cpp>
#include <ogxx/bit_matrix_io.hpp>
#include <sstream>

TEST_SUITE("print")
{
  TEST_CASE("print")
  {
    Matrix_shape _shape = {2, 3};
    Bit_matrix_uptr bm = new_dense_bit_matrix(_shape);
    bm->fill(1);
    bm->set(1,1,0);
    std::ostringstream os;
    io::print(os, *bm);
    CHECK(os.str() == "bit_matrix
    {
      0100 01
      1011 00
      0110 01
      }
      " );
  }
}
