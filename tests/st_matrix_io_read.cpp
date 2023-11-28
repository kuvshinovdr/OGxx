/// @file tests/st_matrix_io_read.cpp
/// @brief St_matrix io::read function tests
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include "testing_head.hpp"
#include <ogxx/st_matrix_io.hpp>
using namespace std;

TEST_SUITE("St_matrix io::read")
{
  TEST_CASE("input 1")
  {
    string_view in =
      "matrix{"
      "1, 2, 3, 4;\n"
      "5, 6, 7;\n"
      ";\n"
      "}"sv;

    auto m = new_dense_st_matrix<Int>();
    CHECK(io::read(in, *m, {}));
    CHECK(in.empty());
    CHECK(m->shape().rows == 4);
    CHECK(m->shape().cols == 4);
    
    int const mm[4][4]
    {
      1, 2, 3, 4,
      5, 6, 7, 0,
      0, 0, 0, 0,
      0, 0, 0, 0,
    };

    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        CHECK(m->get(i, j) == mm[i][j]);
  }

  TEST_CASE("input 2")
  {
    string_view in =
      "open matrix "
      "1 ; 2 ; 3 ; 4 //\n"
      "5 ; 6 ; 7 ; 8 ; 9\n"
      "end matrix"sv;

    auto m = new_dense_st_matrix<Int>();
    CHECK(io::read(in, *m, 
      io::St_matrix_format
      { 
        .matrix_open  = "open matrix"sv,
        .matrix_close = "end matrix"sv,
        .column_sep   = ";"sv,
        .row_sep      = "//"sv
      }));

    CHECK(in.empty());
    CHECK(m->shape().rows == 2);
    CHECK(m->shape().cols == 5);

    int const mm[2][5]
    {
      1, 2, 3, 4, 0,
      5, 6, 7, 8, 9,
    };

    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 5; ++j)
        CHECK(m->get(i, j) == mm[i][j]);
  }

  TEST_CASE("fail 1")
  {
    string_view in =
      "{ 1, 2, 3, 5 "
      "5, 6, 7, 8}"sv;

    auto m = new_dense_st_matrix<Int>();
    CHECK(!io::read(in, *m,
      io::St_matrix_format
      {
        .matrix_open  = "{"sv,
        .matrix_close = "}"sv,
        .column_sep   = ","sv,
      }));

    CHECK(in == "5, 6, 7, 8}"sv);
  }
}
