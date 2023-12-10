/// @file index_set_sortedvector.cpp
/// @brief Testing Index_set_sortedvector class.
#include "testing_head.hpp"
#include <ogxx/st_set.hpp>
#include <ogxx/iterator_algorithms.hpp>
#include <iterator>

TEST_SUITE("Index_set_sortedvector")
{
  TEST_CASE("Routine 1")
  {
    auto isp = new_index_set_sortedvector(); // empty
    auto isit = dynamic_cast<Indexed_iterable<Scalar_index>*>(isp.get());
    CHECK(isit != nullptr);
    CHECK(isit->size() == 0);
    
    CHECK(isp->insert(1));
    CHECK(isp->contains(1));
    CHECK(!isp->contains(0));
    CHECK(isit->size() == 1);
    
    CHECK(isp->insert(10));
    CHECK(isp->contains(10));
    CHECK(isit->size() == 2);
    
    CHECK(!isp->insert(1));
    CHECK(isit->size() == 2);
    CHECK(!isp->erase(0));
    CHECK(isit->size() == 2);
    CHECK(isp->insert(5));
    CHECK(isp->insert(3));
    CHECK(isp->insert(0));
    CHECK(isp->insert(11));
    CHECK(isit->size() == 6);

    Scalar_index const ref[] { 0, 1, 3, 5, 10, 11 };
    for (size_t i = 0; i < size(ref); ++i)
      CHECK(ref[i] == isit->get(i));

    CHECK(equal(isit->iterate(), new_stl_iterator(ref)));
  }
}
TEST_SUITE("Index_set_sortedvector")
{
  TEST_CASE("Routine 1")
  {
    auto isp = new_index_set_sortedvector(); // empty
    auto isit = dynamic_cast<Indexed_iterable<Scalar_index>*>(isp.get());
    CHECK(isit != nullptr);
    CHECK(isit->size() == 0);
    
    CHECK(isp->insert(1));
    CHECK(isp->contains(1));
    CHECK(!isp->contains(0));
    CHECK(isit->size() == 1);
    
    CHECK(isp->insert(10));
    CHECK(isp->contains(10));
    CHECK(isit->size() == 2);
    
    CHECK(!isp->insert(1));
    CHECK(isit->size() == 2);
    CHECK(!isp->erase(0));
    CHECK(isit->size() == 2);
    CHECK(isp->insert(5));
    CHECK(isp->insert(3));
    CHECK(isp->insert(0));
    CHECK(isp->insert(11));
    CHECK(isit->size() == 6);

    Scalar_index const ref[] { 0, 1, 3, 5, 10, 11 };
    for (size_t i = 0; i < size(ref); ++i)
      CHECK(ref[i] == isit->get(i));

    CHECK(equal(isit->iterate(), new_stl_iterator(ref)));
  }
  
  TEST_CASE("Routine 2")
  {
    Scalar_index const test[] {};
    auto isp = new_index_set_sortedvector(new_stl_iterator(test));
    auto isit = dynamic_cast<Indexed_iterable<Scalar_index>*>(isp.get());
    CHECK(isit != nullptr);
    CHECK(isit->size() == 0);
    
    CHECK(isp->insert(4));
    CHECK(isp->insert(2));
    CHECK(isp->contains(4));
    CHECK(isp->contains(2));
    CHECK(!isp->contains(1));
    CHECK(isit->size() == 2);
    
    CHECK(isp->insert(12));
    CHECK(isp->contains(12));
    CHECK(isit->size() == 3);
    
    CHECK(!isp->insert(2));
    CHECK(isit->size() == 3);
    CHECK(!isp->erase(1));
    CHECK(isit->size() == 3);
    CHECK(isp->insert(46));
    CHECK(isp->insert(20));
    CHECK(isp->insert(16));
    CHECK(isp->insert(33));
    CHECK(isit->size() == 7);

    Scalar_index const ref[] { 2, 4, 12, 16, 20, 33, 46 };
    for (size_t i = 0; i < size(ref); ++i)
      CHECK(ref[i] == isit->get(i));
  }
}




