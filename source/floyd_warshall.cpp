/// @file floyd_warshall.cpp
/// @brief Graph view implementation for directed graph represented by an adjacency list.
/// @author Timashev R.E. 
#include <ogxx/floyd_warshall.hpp>
namespace ogxx
{

 template <typename ST>
    auto floyd_warshall_only_matrix_ST( const ogxx::St_matrix<ST>& distances)
    {
        if(!distances.shape().is_square()) 
            throw std::invalid_argument("floyd_warshall_only_matrix_ST::ctor: the matrix must be square."); 
        auto n = distances.shape();
        auto result = distances.copy();

            for (Scalar_index k = 0; k < n.cols; ++k)
                {
                    for (Scalar_index i = 0; i < n.rows; ++i)
                    {
                        for (Scalar_index l = 0; l < n.cols; ++l)
                        {
                        auto member = min(result->get(i,l), result->get(i,k) + result->get(k,l));
                        result->set(i,l,member);
                        }
                    }
                }
        return result;
    }
    auto floyd_warshall_only_matrix(Int_matrix const& distances) -> Int_matrix_uptr{
        return floyd_warshall_only_matrix_ST(distances); 
    }

    auto floyd_warshall_only_matrix(Float_matrix const& distances) -> Float_matrix_uptr{
        return floyd_warshall_only_matrix_ST(distances); 
    }

}
