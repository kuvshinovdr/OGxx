/// @file stl_iterator_and_iterator_algorithms.cpp
/// @brief Testing Stl_iterator and iterator_algorithms.hpp
/// @author Chaplygin M.D.

#include "testing_head.hpp"

#include <ogxx/stl_iterator.hpp>
#include <ogxx/iterator_algorithms.hpp>

#include <string>
#include <sstream>
#include <vector>
// Можно добавить #include стандартной библиотеки, если понадобятся.


TEST_SUITE("stl_iterator and iterator_algorithms")
{

  // Пример теста.
  TEST_CASE("for_each")
  {
    int const
      data[]{ 1, 2, 3, 4, 5, 6 },
      data1[]{ 1 };
    std::vector<int> v;

    std::ostringstream out, out1, out2;
    out2 << "no changes";

    for_each(new_stl_iterator(data), 
      [&](int x) { out << ' ' << x; });

    for_each(new_stl_iterator(data1),
      [&](int x) { out1 << ' ' << x; });

    for_each(new_stl_iterator(v),
      [&](int x) { out2 << ' ' << x; });

    CHECK(out.str() == " 1 2 3 4 5 6");
    CHECK(out1.str() == " 1");
    CHECK(out2.str() == "no changes");
  }

  TEST_CASE("skip_n")
  {
    int const data[]{ 1, 2, 3, 4, 5, 6 };
    std::ostringstream out, out1, out2;

    out2 << "no_changes";

    Int_iterator_uptr
      p = new_stl_iterator(data),
      p1 = new_stl_iterator(data),
      p2 = new_stl_iterator(data);

    skip_n(p, 2);
    skip_n(p1, 0);
    skip_n(p2, 6);

    for_each(std::move(p), [&](int x) { x -= 5; out << ' ' << x;  });
    for_each(std::move(p1), [&](int x) { x -= 5; out1 << ' ' << x; });
    for_each(std::move(p2), [&](int x) { x -= 5; out2 << ' ' << x; });

    CHECK(out.str() == " -2 -1 0 1");
    CHECK(out1.str() == " -4 -3 -2 -1 0 1");
    CHECK(out2.str() == "no_changes");
  }

  TEST_CASE("count")
  {
    int const data[]{ 1, 2, 3, 1, 2, 3, 27, 9, 4, 5, 6, 12, 1, 1};
    CHECK(count(new_stl_iterator(data), 1) == 4);
    CHECK(count(new_stl_iterator(data), 3) == 2);
  }

  TEST_CASE("count_if")
  {
    int const data[]{ 1, 2, 3, 1, 2, 3, 27, 9, 4, 5, 6, 12, 1, 1 };
    CHECK(count_if(new_stl_iterator(data),[](int x) {return x % 2 == 0; }) == 5);
    CHECK(count_if(new_stl_iterator(data), [](int x) {return x % 3 == 0; }) == 6);
  }

  TEST_CASE("find")
  {
    int const data[]{ 666, 1, 2, 3, 1, 2, 3, 27, 9, 4, 5, 6, 12, 1, 1 };
    auto p = find(new_stl_iterator(data), 27);
    auto p1 = find(new_stl_iterator(data), 66);
    CHECK(p.first == 7);
    CHECK(p1.first == 15);
  }

  TEST_CASE("find_if")
  {
    int const data[]{ 666, 1, 2, 3, 1, 2, 3, 27, 9, 4, 5, 6, 12, 1, 1 };
    auto p = find_if(new_stl_iterator(data), [](int x) { return x * 5 == 15; });
    auto p1 = find_if(new_stl_iterator(data), [](int x) { return x * 0 == 1; });
    CHECK(p.first == 3);
    CHECK(p1.first == 15);
  }

  TEST_CASE("find_not")
  {
    int const
      data[]{ 1, 1, 1, 1, 1, 1, 3, 27, 9, 4, 5, 6, 12, 1, 1 },
      data1[]{ 2, 2, 2, 2, 2 };
    auto p = find_not(new_stl_iterator(data), 1);
    auto p1 = find_not(new_stl_iterator(data1), 2);
    CHECK(p.first == 6);
    CHECK(p1.first == 5);
  }

  TEST_CASE("find_if_not")
  {
    int const
      data[]{ 81, 291, 4551, 12, 18, 921, 3, 27, 9, 4, 5, 6, 12, 1, 1 },
      data1[]{ 2, 2, 2, 2, 2 };
    auto p = find_if_not(new_stl_iterator(data), [](int x) { return x % 3 == 0; });
    auto p1 = find_if_not(new_stl_iterator(data1), [](int x) { return x % 2 == 0; });
    CHECK(p.first == 9);
    CHECK(p1.first == 5);
  }

  TEST_CASE("all_of")
  {
    int const
      data[]{ 31, 31, 31, 31, 31, 31, 31 },
      data1[]{ 2, 2, 3, 4, 4, 6};
    CHECK(all_of(new_stl_iterator(data), [](int x) { return x % 31 == 0; }));
    CHECK(!all_of(new_stl_iterator(data1), [](int x) { return x % 2 == 0; }));
  }

  TEST_CASE("any_of")
  {
    int const
      data[]{ 31, 31, 31, 17, 31, 31, 31 },
      data1[]{ 2, 2, 3, 4, 4, 6 };
    CHECK(any_of(new_stl_iterator(data), [](int x) { return x % 17 == 0; }));
    CHECK(!any_of(new_stl_iterator(data1), [](int x) { return x % 17 == 0; }));
  }

  TEST_CASE("none_of")
  {
    int const
      data[]{ 31, 31, 31, 17, 31, 31, 31 },
      data1[]{ 2, 2, 3, 4, 4, 6 };
    CHECK(none_of(new_stl_iterator(data), [](int x) { return x % 400 == 0; }));
    CHECK(!none_of(new_stl_iterator(data1), [](int x) { return x % 3 == 0; }));
  }

  TEST_CASE("equal(both versions)")
  {
    int const
      data[]{ 16, 8, 4, 2, 1, 16, 8 },
      data1[]{ 2, 2, 3, 4, 4, 6 },
      data2[]{ 16, 32, 64, 128, 256, 16, 32 };
    std::vector<int>
      v{ 16, 32, 64, 128, 256, 16, 32},
      v1, v2;

    CHECK(!equal(new_stl_iterator(data), new_stl_iterator(v)));
    CHECK(!equal(new_stl_iterator(data1), new_stl_iterator(v)));
    CHECK(equal(new_stl_iterator(data2), new_stl_iterator(v)));
    CHECK(equal(new_stl_iterator(v1), new_stl_iterator(v2)));
    CHECK(!equal(new_stl_iterator(v1), new_stl_iterator(v)));
    //second version
    CHECK(ogxx::equal(new_stl_iterator(data), new_stl_iterator(v), [](int x, int y) { return x * y == 256; }));
  }

  TEST_CASE("accumulate(both versions)")
  {
    int const data[]{ 16, 8, 4, 2, 1, 16, 8 };
    std::string const text[]{ "pri", "ved", "med", "ved" };
    int accum1 = 1;
    std::string accum2;

    CHECK(accumulate(new_stl_iterator(data), accum1) == 56);
    CHECK(accumulate(new_stl_iterator(text), accum2) == "privedmedved");
    //second version
    CHECK(accumulate(new_stl_iterator(data), accum1, [](int accum1, int x) { return accum1 * x; }) == 131072);
  }


  TEST_CASE("inner_product(all versions)")
  {
    int const
      data1[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
      data2[]{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int accum = 0;

    //first version
    CHECK(ogxx::inner_product(
      new_stl_iterator(data1),
      new_stl_iterator(data2),
      accum,
      [](int x, int y) { return x + y; },
      [](int x, int y) { return x * y; }) == 220);
    //second version
    CHECK(ogxx::inner_product(
      new_stl_iterator(data1),
      new_stl_iterator(data2),
      accum,
      [](int x, int y) { return x * y; }) == 220);
    //third version
    CHECK(ogxx::inner_product(
      new_stl_iterator(data1),
      new_stl_iterator(data2),
      accum) == 220);
  }
  // TODO: TEST_CASE для каждого алгоритма из iterator_algorithms.hpp.
}
