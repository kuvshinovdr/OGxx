/// @file matrix_index_shape_window.cpp
/// @brief Tests Matrix_index, Matrix_shape, Matrix_window structs.
/// @author Kuvshinov D.R kuvshinovdr at yandex.ru
#include "testing_head.hpp"
#include <ogxx/matrix.hpp>

TEST_SUITE("Matrix_shape")
{
  TEST_CASE("is_valid")
  {
    Matrix_shape s{ 0, 0 };
    CHECK(s.is_valid());
    s.rows = 1;
    CHECK(!s.is_valid());
    s.cols = 10;
    CHECK(s.is_valid());
    s.rows = 0;
    CHECK(!s.is_valid());
    s.rows = -10;
    CHECK(!s.is_valid());
    s.cols = -15;
    CHECK(!s.is_valid());
    s.rows = 100;
    CHECK(!s.is_valid());
    s.cols = 100;
    CHECK(s.is_valid());
  }

  TEST_CASE("element_count")
  {
    Matrix_shape s{};
    CHECK(s.element_count() == 0);
    s.rows = 100;
    s.cols = 222;
    CHECK(s.element_count() == 100*222);
    s.rows = -10;
    CHECK_THROWS_AS((void)(s.element_count() != 0), std::out_of_range);

    constexpr auto BIG = std::numeric_limits<Scalar_size>::max() / 14;
    s.rows = s.cols = BIG;
    CHECK_THROWS_AS((void)(s.element_count() != 0), std::out_of_range);
    s.rows = 7;
    CHECK(s.element_count() == 7*BIG);
    s.rows = 15;
    CHECK_THROWS_AS((void)(s.element_count() != 0), std::out_of_range);
  }
}
