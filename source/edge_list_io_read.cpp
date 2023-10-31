/// @file edge_list_io_read.cpp
/// @brief ...
/// @author ...
#ifndef OGXX_EDGE_LIST_IO_CPP_INCLUDED
#define OGXX_EDGE_LIST_IO_CPP_INCLUDED

#include "edge_list_io.hpp"

auto read(std::istream& is, ogxx::Edge_list& el, Edge_list_format const& format)
-> std::istream&;

auto read(ogxx::Edge_list& el, Edge_list_format const& format)
-> std::istream&;


#endif//OGXX_EDGE_LIST_IO_CPP_INCLUDED