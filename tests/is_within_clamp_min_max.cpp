/// @file is_within_clamp_min_max.cpp
/// @brief Tests for is_within, clamp, min and max functions.
/// @author Kuvshinov D.R kuvshinovdr at yandex.ru
#include "testing_head.hpp"
#include <ogxx/primitive_definitions.hpp>
#include <cmath>

TEST_SUITE("is_within, clamp, min and max")
{
  TEST_CASE("is_within")
  {
    CHECK(is_within(10, 0, 15));
    CHECK(is_within(10, 10, 15));
    CHECK(is_within(15, 10, 15));
    CHECK(is_within(2., 2, 2.));
    CHECK(is_within(infinity, -infinity, infinity));
    CHECK(!is_within(0, -10., -1.f));
    CHECK(!is_within(10, 15, 15));
    CHECK(!is_within(5, 0, 2));
    CHECK(!is_within(std::numeric_limits<Float>::quiet_NaN(), -infinity, infinity));
  }

  TEST_CASE("clamp")
  {
    CHECK(10 == clamp(10, 0, 15));
    CHECK(10 == clamp(10, 10, 15));
    CHECK(15 == clamp(15, 10, 15));
    CHECK(15 == clamp(10, 15, 15));
    CHECK(2. == clamp(2., 2, 2.));
    CHECK(2. == clamp(2, -2, 2.));
    CHECK(infinity == clamp(infinity, -infinity, infinity));
    CHECK(-1. == clamp(0, -10., -1.f));
    CHECK(2 == clamp(5, 0, 2));
    CHECK(std::isnan(clamp(std::numeric_limits<Float>::quiet_NaN(), -infinity, infinity)));
  }

  TEST_CASE("min")
  {
    CHECK(1. == min(1, 2.));
    CHECK(1. == min(3, 2, 1.));
    CHECK(0. == min(1., 2, 0, 3, 4, 100, infinity));
    
    int a = 1, b = 2, c = 3;
    CHECK(&a == &min(b, a, c));

    a = 2;
    CHECK(&a == &min(a, b, c));
    CHECK(&a == &min(a, c, b));
    CHECK(&a == &min(c, a, b));
  }

  TEST_CASE("max")
  {
    CHECK(2. == max(1, 2.));
    CHECK(3. == max(2, 3, 1.));
    CHECK(infinity == max(1., 2, 0, 3, 4, 100, infinity));

    int a = 1, b = 2, c = 3;
    CHECK(&c == &max(b, a, c));

    a = 2;
    c = 1;
    CHECK(&b == &max(a, b, c));
    CHECK(&b == &max(a, c, b));
    CHECK(&b == &max(c, a, b));
  }
}
