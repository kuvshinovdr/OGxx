/// @file edge_list_io_read.hpp
/// @brief Test of ogxx::io::read from 'edge_list_io_read.cpp'
/// @author Chaplygin M.D.

#include "testing_head.hpp"
#include <ogxx/edge_list_io.hpp>

#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>


namespace
{
	bool only_ws(std::string_view s)
	{
		return std::all_of(s.begin(), s.end(), 
			[](char ch) { return std::isspace(static_cast<unsigned char>(ch)); });
	}
}

TEST_SUITE("edge_list_io_read_test")
{
	TEST_CASE("empty")
	{
		auto el = new_edge_list_vector();

		std::string_view in = "edge_list{}";
		CHECK(io::read(in, *el, io::Edge_list_format{}));
		CHECK(el->size() == 0);
		CHECK(in.size() == 0);
	}

	TEST_CASE("good")
	{
		std::string_view const inputs[]
		{
			"edge_list\n{\n  (1, 2)\n  (2, 3)\n  (3, 4)\n  (4, 5)\n  (5, 6)\n}\n",
			"edge_list\t{  (1,\n2)\n  (2,\t3)\n  (3,4)\t  (4,5)  (5, 6)\n}    ",
			"edge_list{(1,2)(2,3)(3,4)(4,5)(5,6)}"
		};

		Vertex_pair const ref[]
		{
			{ 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }
		};

		for (auto in: inputs)
		{
			auto el = new_edge_list_vector();
			CHECK(io::read(in, *el, io::Edge_list_format{}));
			CHECK(only_ws(in));
			CHECK(el->size() == 5);
			CHECK(el->max_vertex_index() == 6);
				
			auto it = el->iterate();
			size_t i = 0;
			for (Vertex_pair vp; it->next(vp); ++i)
			{
				REQUIRE(i < std::size(ref));
				auto const [u, v] = ref[i];
				CHECK(vp.first == u);
				CHECK(vp.second == v);
			}
		}
	}

	TEST_CASE("bad")
	{
		std::string_view const inputs[]
		{
			"{\n(1,2)\n(2,3)\n(3,4)\n(4,5)\n(5,6)\n}\n",
			"ege_list\n{\n(1,2)\n(2,3)\n(3,4)\n(4,5)\n(5,6)\n}\n"
		};

		auto el = new_edge_list_vector();
		for (auto in: inputs)
			CHECK(!io::read(in, *el, io::Edge_list_format{}));
	}
}
