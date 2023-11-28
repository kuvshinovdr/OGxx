/// @file io_head.hpp
/// @brief Shared things for *_io.hpp files.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_IO_HEAD_HPP_INCLUDED
#define OGXX_IO_HEAD_HPP_INCLUDED

#include <string_view>
#include <ostream>


/// IO operations for OGxx objects
namespace ogxx::io
{
  using std::string_view;
  using namespace std::string_view_literals;
}

#endif//OGXX_IO_HEAD_HPP_INCLUDED
