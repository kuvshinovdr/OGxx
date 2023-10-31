/// @file stl_iterator_and_iterator_algorithms.cpp
/// @brief Testing Stl_iterator and iterator_algorithms.hpp

#include "testing_head.hpp"

#include <ogxx/stl_iterator.hpp>
#include <ogxx/iterator_algorithms.hpp>

#include <string>
#include <sstream>
// ����� �������� #include ����������� ����������, ���� �����������.


TEST_SUITE("stl_iterator and iterator_algorithms")
{

  // ������ �����.
  TEST_CASE("for_each")
  {
    int const data[]{ 1, 2, 3, 4, 5, 6 };
    std::ostringstream out;
    for_each(new_stl_iterator(data), 
      [&](int x) { out << ' ' << x; });

    CHECK(out.str() == " 1 2 3 4 5 6");
  }

  // TODO: TEST_CASE ��� ������� ��������� �� iterator_algorithms.hpp.

}
