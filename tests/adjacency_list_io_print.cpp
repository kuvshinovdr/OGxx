#include "testing_head.hpp"
#include <ogxx/adjacency_list_io.hpp>
#include <sstream>
using namespace std;

TEST_SUITE("Adjacency_list print")
{
    TEST_CASE("output 1")
    {
    ogxx::Adjacency_list al;

    //Initializing adjacency_list
    vector<vector<Scalar_index>> adj_list{
        {1, 2, 3},
        {0, 3},
        {0, 3},
        {0, 1, 2},
    };

    for (size_t u = 0; u < adj_list.size(); ++u) {
        auto adj = al.get(u);
        for (Scalar_index v: adj_list[u]) {
            adj->insert(v);
        }
    }

    std::ostringstream oss;

    io::print(oss, al, io::Adjacency_list_format{});
    }
}
