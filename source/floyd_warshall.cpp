/// @file floyd_warshall.cpp
/// @brief Graph view implementation for directed graph represented by an adjacency list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/floyd_warshall.hpp>
namespace ogxx
{

 template <typename ST>
    auto floyd_warshall_only_matrix( const ogxx::St_matrix<ST>& distances)
    {
        auto n = distances.shape();
        auto result = distance.copy();

            for (int k = 0; k < n.cols; ++k)
                {
                    for (int i = 0; i < n.rows; ++i)
                    {
                        for (int j = 0; j < n.cols ++j)
                        {
                            result.get(i,j) = min(result.get(i,j), result.get(i,k) + result.get(k,j));
                        }
                    }
                }
        return result;
    }

}
