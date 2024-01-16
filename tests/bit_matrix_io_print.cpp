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
    Matrix_shape _shape {3, 7};
    Bit_matrix_uptr bm = new_dense_bit_matrix(_shape);
    bm->fill(1);
    bm->set(1,1, 0);
    bm->set(2,2, 0);
    bm->set(0,4, 0);
    bm->set(2,6, 0);

    std::ostringstream os;
    io::print(os, *bm);
    auto result = os.str();
    CHECK(result == 
"bit_matrix\n\
{\n\
1111 011\n\
1011 111\n\
1101 110\n\
}\n" );
  }
}
