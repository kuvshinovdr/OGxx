/// @file index_set_bitvector.cpp
/// @author Ivan I. Martynov <7martyn1>
/// @brief Testing Index_set_bitvector class.
#include "testing_head.hpp"
#include <ogxx/st_set.hpp>
#include <ogxx/iterator_algorithms.hpp>
#include <iterator>

TEST_SUITE("Index_set_bitvector")
{
  TEST_CASE("Routine 1")
  {
    auto isp = new_index_set_bitvector(); // empty
    auto isit = dynamic_cast<Indexed_iterable<Scalar_index>*>(isp.get());
    CHECK(isit != nullptr);
    CHECK(isit->size() == 0);
    
    CHECK(isp->insert(0));
    CHECK(isp->contains(0));
    CHECK(!isp->contains(1));
    CHECK(isit->size() == 1);
    
    CHECK(isp->insert(1));
    CHECK(isp->contains(1));
    CHECK(isit->size() == 2);
    
    CHECK(!isp->insert(0));
    CHECK(isit->size() == 2);
    CHECK(!isp->erase(0));
    CHECK(isit->size() == 2);
    CHECK(isp->insert(0));
    CHECK(isp->insert(1));
    CHECK(isp->insert(1));
    CHECK(isp->insert(0));
    CHECK(isit->size() == 6);

    Scalar_index const ref[] { 0, 1, 0, 1, 1, 0 };
    for (size_t i = 0; i < std::size(ref); ++i)
      CHECK(ref[i] == isit->get(i));

    CHECK(equal(isit->iterate(), new_stl_iterator(ref)));
  }
}
TEST_SUITE("Index_set_bitvector")
{
  TEST_CASE("Routine 1")
  {
    auto isp = new_index_set_bitvector(); // empty
    auto isit = dynamic_cast<Indexed_iterable<Scalar_index>*>(isp.get());
    CHECK(isit != nullptr);
    CHECK(isit->size() == 0);
    
    CHECK(isp->insert(0));
    CHECK(isp->contains(0));
    CHECK(!isp->contains(1));
    CHECK(isit->size() == 1);
    
    CHECK(isp->insert(1));
    CHECK(isp->contains(1));
    CHECK(isit->size() == 2);
    
    CHECK(!isp->insert(0));
    CHECK(isit->size() == 2);
    CHECK(!isp->erase(0));
    CHECK(isit->size() == 2);
    CHECK(isp->insert(0));
    CHECK(isp->insert(1));
    CHECK(isp->insert(1));
    CHECK(isp->insert(0));
    CHECK(isit->size() == 6);

    Scalar_index const ref[] { 0, 1, 0, 1, 1, 0 };
    for (size_t i = 0; i < std::size(ref); ++i)
      CHECK(ref[i] == isit->get(i));

    CHECK(equal(isit->iterate(), new_stl_iterator(ref)));
  }
  
  TEST_CASE("Routine 2")
  {
    Scalar_index const test[1] {};
    auto isp = new_index_set_bitvector(new_stl_iterator(test + 0, test + 0));
    auto isit = dynamic_cast<Indexed_iterable<Scalar_index>*>(isp.get());
    CHECK(isit != nullptr);
    CHECK(isit->size() == 0);
    
    CHECK(isp->insert(0));
    CHECK(isp->insert(0));
    CHECK(isp->contains(0));
    CHECK(isp->contains(0));
    CHECK(!isp->contains(1));
    CHECK(isit->size() == 2);
    
    CHECK(isp->insert(1));
    CHECK(isp->contains(1));
    CHECK(isit->size() == 3);
    
    CHECK(!isp->insert(2));
    CHECK(isit->size() == 3);
    CHECK(!isp->erase(1));
    CHECK(isit->size() == 3);
    CHECK(isp->insert(1));
    CHECK(isp->insert(1));
    CHECK(isp->insert(0));
    CHECK(isp->insert(1));
    CHECK(isit->size() == 7);

    Scalar_index const ref[] { 0, 0, 1, 1, 1, 0, 1 };
    for (size_t i = 0; i < std::size(ref); ++i)
      CHECK(ref[i] == isit->get(i));
  }
}