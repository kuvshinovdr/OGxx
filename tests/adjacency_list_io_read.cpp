/// @file tests/adjacency_list_io_read.cpp
/// @brief Adjacency list io::read function tests
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include "testing_head.hpp"
#include <ogxx/adjacency_list_io.hpp>
using namespace std;

TEST_SUITE("Adjacency_list read")
{
  TEST_CASE("input 1")
  {
    string_view in = 
      "adjacency_list\n"
      "{\n"
      "   0 [1, 2, 3]\n"
      "   1 [0, 3]\n"
      "   2 [0, 3]\n"
      "   3 [0, 1, 2]\n"
      "}\n"sv;

    std::unique_ptr<Adjacency_list> al;
    io::read(in, *al, io::Adjacency_list_format{});
  }
}
