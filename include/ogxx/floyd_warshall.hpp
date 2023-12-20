
/// @file floyd_warshall.hpp
/// @brief algorithm floyd_warshall for Int_matrix and Float_matrix
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ST_MATRIX_IO_HPP_INCLUDED
#define OGXX_ST_MATRIX_IO_HPP_INCLUDED

#include <ogxx/st_matrix.hpp>

namespace ogxx
{
template <typename ST>
auto floyd_warshall_only_matrix(ogxx::St_matrix<ST> const & distances)-> St_matrix_uptr<ST>;
}

#endif//OGXX_ST_MATRIX_IO_HPP_INCLUDED