/// @file testing_head.hpp
/// @brief A helper file to be included in each testing cpp.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_TESTING_HEAD_HPP_INCLUDED
#define OGXX_TESTING_HEAD_HPP_INCLUDED

#ifndef OGXX_TESTING_BUILD
#define OGXX_TESTING_BUILD
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#endif//OGXX_TESTING_BUILD

#include <doctest/doctest.h>
#include <ogxx/primitive_definitions.hpp>
using namespace ogxx;

#endif//OGXX_TESTING_HEAD_HPP_INCLUDED
