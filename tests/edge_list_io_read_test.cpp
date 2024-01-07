/// @file edge_list_io_read.hpp
/// @brief Test of ogxx::io::read from 'edge_list_io_read.cpp'
/// @author Chaplygin M.D.

#include "tests/testing_head.hpp"
#include <source/edge_list_vector.cpp>
#include <ogxx/edge_list_io.hpp>
#include <edge_list_io_read.cpp>

#include <string>
#include <string_view>
#include <sstream>
#include <vector>

namespace ogxx
{
	TEST_SUITE("edge_list_io_read_test")
	{
		TEST_CASE("read")
		{
			Edge_list_vector el1, el2, el3;
			io::Edge_list_format format;

			/*std::string in, temp;
			std::ifstream input("input.txt");
			while (input)
			{
				input >> temp;
				in += temp;
				if (temp == "{") break;
			}
			std::string_view test_in = in;*/

			std::string_view test_in1 = "edge_list\n{\n  (1, 2)\n  (2, 3)\n  (3, 4)\n  (4, 5)\n  (5, 6)\n}\n",
											 test_in2 = "edge_list\n{\n  (1, 2)\n  (2, 3)\n  (3, 4)\n  (4,5)\n  (5, 6)\n}\n",//Uncorrect format in 4th brackets.
											 test_in3 = "edge_list\n{\n}\n";//Empty list.

			CHECK(io::read(test_in1, el1, format));
			CHECK(!io::read(test_in2, el2, format));
			CHECK(io::read(test_in3, el3, format));
		}
	}
}