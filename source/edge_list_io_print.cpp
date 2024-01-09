// edge_list_io.cpp
// Implementation of edge list IO functions

#include <ogxx/edge_list_io.hpp>

#include <iostream>
#include <stdexcept>

namespace ogxx::io
{

    auto print(std::ostream& os, ogxx::Edge_list const& el, Edge_list_format const& format)
        -> std::ostream&
    {
        os << format.list_open; // print the opening token for the list
        auto edges = el.iterate();
        for (Vertex_pair edge; edges->next(edge);) // iterate over the edges in the list
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

}
