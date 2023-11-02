/// @file edge_list_io_read.cpp
/// @brief ...
/// @author ...
#ifndef OGXX_EDGE_LIST_IO_CPP_INCLUDED
#define OGXX_EDGE_LIST_IO_CPP_INCLUDED

#include <ogxx/edge_list_io.hpp>
#include "parsing_utils.hpp"
#include <iostream>


namespace ogxx::io
{

  auto read(std::istream& is, Edge_list& el, Edge_list_format const& format)
    -> std::istream&
  {
    using namespace ogxx::io::util;

  }

  auto read(Edge_list& el, Edge_list_format const& format)
    -> std::istream&
  {
    return read(std::cin, el, format);
  }

}

#endif//OGXX_EDGE_LIST_IO_CPP_INCLUDED