/// @file floyd_warshall.cpp
/// @brief Graph view implementation for directed graph represented by an adjacency list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/floyd_warshall.hpp>
namespace ogxx
{

 template <typename ST>
    auto floyd_warshall_only_matrix_ST( const ogxx::St_matrix<ST>& distances, ST)
    {
        if(!distances.is_square()) 
    throw std::invalid_argument("floyd_warshall_only_matrix_ST::ctor: the matrix must be square."); 
        auto n = distances.shape();
        auto result = distance.copy();

            for (Scalar_index k = 0; k < n.cols; ++k)
                {
                    for (Scalar_index i = 0; i < n.rows; ++i)
                    {
                        for (Scalar_index j = 0; j < n.cols ++j)
                        {
                        auto member = min(result->get(i,j), result->get(i,k) + result->get(k,j));
                        result->set(i,j,member);
                        }
                    }
                }
        return result;
    }
    auto floyd_warshall_only_matrix(Int_matrix const& distances){
        return floyd_warshall_only_matrix_ST(distances, Int{}); 
    }

    auto floyd_warshall_only_matrix(Float_matrix const& distances){
        return floyd_warshall_only_matrix_ST(distances, Float{}); 
    }

}
