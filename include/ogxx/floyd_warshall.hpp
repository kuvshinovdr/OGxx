/// @file floyd_warshall.hpp
/// @brief Floyd-Warshall algorithm for Int_matrix and Float_matrix
/// @author Timahev R.E. 
#ifndef OGXX_ST_MATRIX_IO_HPP_INCLUDED
#define OGXX_ST_MATRIX_IO_HPP_INCLUDED

#include <ogxx/st_matrix.hpp>

namespace ogxx
{

/// @brief            Run integer Floyd-Warshall algorithm.
/// @param distances  edge length matrix for a graph, must be square
/// @return           shortest path distance matrix
auto floyd_warshall_only_matrix(Int_matrix const& distances) -> Int_matrix_uptr;

/// @brief            Run floating-point Floyd-Warshall algorithm.
/// @param distances  edge length matrix for a graph, must be square
/// @return           shortest path distance matrix
auto floyd_warshall_only_matrix(Float_matrix const& distances) -> Float_matrix_uptr;
}

#endif//OGXX_ST_MATRIX_IO_HPP_INCLUDED