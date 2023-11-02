/// @file edge_list_io_read.cpp
/// @brief ...
/// @author ...
#ifndef OGXX_EDGE_LIST_IO_CPP_INCLUDED
#define OGXX_EDGE_LIST_IO_CPP_INCLUDED

#include <ogxx/edge_list_io.hpp>
#include "parsing_utils.hpp"


namespace ogxx::io
{

  auto read(std::string_view& in, Edge_list& el, Edge_list_format const& format)
    -> bool
  {
    using namespace ogxx::io::util;

  }

}

#endif//OGXX_EDGE_LIST_IO_CPP_INCLUDED