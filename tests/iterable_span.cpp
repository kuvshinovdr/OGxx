/// @file iterable_span.hpp
/// @brief Testing code for ogxx/iterable_span.hpp.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include "testing_head.hpp"
#include <ogxx/iterable_span.hpp>
#include <ogxx/st_set.hpp>

#include <iterator>

TEST_SUITE("iterable_span")
{
  TEST_CASE("non abstract, not strided")
  {
    Scalar_index data[]
    {
      1, 3, 5, 8, 9, 10
    };

    auto its = new_iterable_span<Scalar_index>(std::begin(data), std::end(data));
    CHECK(!its->is_empty());
    CHECK(its->size() == std::size(data));

    Scalar_index i = 0, item;
    for (auto it = its->iterate(); it->next(item); ++i)
    {
      CHECK(item == data[i]);
      CHECK(data[i] == its->get(i));
    }
    
    CHECK(its->set(2, 7) == 5);
    CHECK(data[2] == 7);
  }

  TEST_CASE("non abstract, strided")
  {
    Scalar_index data[]
    {
      1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    Scalar_index ref[]
    {
      1, 4, 7
    };

    auto its = new_iterable_span<Scalar_index>(std::begin(data), std::end(data), 3);
    CHECK(!its->is_empty());
    CHECK(its->size() == std::size(ref));

    Scalar_index i = 0, item;
    for (auto it = its->iterate(); it->next(item); ++i)
    {
      CHECK(item == ref[i]);
      CHECK(ref[i] == its->get(i));
    }

    CHECK(its->set(2, 5) == ref[2]);
    CHECK(data[6] == 5);
  }

  TEST_CASE("abstract, not strided")
  {
    Index_set_uptr data[3] {};
    for (auto& ptr: data)
      ptr = new_index_set_sortedvector();

    auto its = new_iterable_span<Index_set>(std::begin(data), std::end(data));

    CHECK(!its->is_empty());
    CHECK(its->size() == 3);

    Scalar_index rounds = 1;
    auto it = its->iterate();
    for (Index_set* item; it->next(item); ++rounds)
      for (Scalar_index i = 0; i < rounds; ++i)
        item->insert(i);

    CHECK(data[0]->contains(0));
    CHECK(data[1]->contains(0));
    CHECK(data[2]->contains(0));
    CHECK(data[1]->contains(1));
    CHECK(data[2]->contains(1));
    CHECK(data[2]->contains(2));
    CHECK(!data[0]->contains(1));
    CHECK(!data[1]->contains(2));
  }
}
