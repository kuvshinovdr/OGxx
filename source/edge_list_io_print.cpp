// edge_list_io.cpp
// Implementation of edge list IO functions

#include <ogxx/edge_list_io.hpp>
#include <ogxx/string_utils.hpp>
#include <sstream>
#include <stdexcept>

namespace ogxx::io
{

    auto print(std::ostream& os, ogxx::Edge_list const& el, Edge_list_format const& format)
        -> std::ostream&
    {
        os << format.list_open; // print the opening token for the list
        for (auto const& edge : el) // iterate over the edges in the list
        {
            os << format.pair_open; // print the opening token for the edge
            os << edge.first << format.pair_sep << edge.second; // print the vertex indices separated by the separator
            os << format.pair_close; // print the closing token for the edge
        }
        os << format.list_close; // print the closing token for the list
        return os;
    }

    auto print(ogxx::Edge_list const& el, Edge_list_format const& format)
        -> std::ostream&
    {
        return print(std::cout, el, format); // print to the standard output stream
    }

    auto read(std::string_view& in, ogxx::Edge_list& el, Edge_list_format const& format)
        -> bool
    {
        el.clear(); // clear the edge list
        if (!string_utils::starts_with(in, format.list_open)) // check if the input starts with the opening token for the list
        {
            return false; // return false if not
        }
        in.remove_prefix(format.list_open.size()); // remove the opening token from the input
        while (!string_utils::starts_with(in, format.list_close)) // loop until the input starts with the closing token for the list
        {
            if (!string_utils::starts_with(in, format.pair_open)) // check if the input starts with the opening token for the edge
            {
                return false; // return false if not
            }
            in.remove_prefix(format.pair_open.size()); // remove the opening token from the input
            std::stringstream ss(std::string(in)); // create a stringstream from the input
            int u, v; // declare two integers for the vertex indices
            char sep; // declare a char for the separator
            if (!(ss >> u >> sep >> v) || sep != format.pair_sep[0]) // try to read the vertex indices and the separator from the stringstream
            {
                return false; // return false if failed
            }
            el.emplace_back(u, v); // add the edge to the list
            in.remove_prefix(ss.tellg()); // remove the read part from the input
            if (!string_utils::starts_with(in, format.pair_close)) // check if the input starts with the closing token for the edge
            {
                return false; // return false if not
            }
            in.remove_prefix(format.pair_close.size()); // remove the closing token from the input
        }
        in.remove_prefix(format.list_close.size()); // remove the closing token for the list from the input
        return true; // return true if successful
    }

}
