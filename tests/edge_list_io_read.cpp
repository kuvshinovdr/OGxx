/// @file edge_list_io_read.cpp
/// @brief Testing the function "read" in the edge_list_io_read.cpp
/// /// @author Artemenko I.V
/// 
#include "testing_head.hpp"
#include <parsing_utils.hpp>
#include <edge_list_io.hpp>
#include <sstream>
#include <doctest/doctest.h>


TEST_CASE("read reads edge list from input stream")
{
	// Create an input stream with the edge list representation
	std::istringstream iss("edge_list\n{\n  (1, 2)\n  (2, 3)\n}");

	// Create an empty Edge_list object
	ogxx::Edge_list el;

	// Call the read function
	ogxx::io::Edge_list_format format;
	ogxx::io::read(iss, el, format);
	
	// Check that the Edge_list object contains the expected edges
	CHECK(el.size() == 2);
	CHECK(el[0].first == 1);
	CHECK(el[0].second == 2);
	CHECK(el[1].first == 2);
	CHECK(el[1].second == 3);
}


