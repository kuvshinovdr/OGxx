// test_edge_list_io.cpp
// Test for edge list IO functions

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <ogxx/edge_list_io.hpp>
#include <sstream>

TEST_CASE("print edge list to arbitrary ostream")
{
	// create an edge list with three edges
	ogxx::Edge_list el{ {1, 2}, {0, 2}, {0, 3} };

	// create a string stream to hold the output
	std::stringstream ss;

	// print the edge list to the string stream using the default format
	ogxx::io::print(ss, el);

	// check if the output matches the expected string
	CHECK(ss.str() == "edge_list\n{\n  (1, 2)\n  (0, 2)\n  (0, 3)\n}\n");
}
