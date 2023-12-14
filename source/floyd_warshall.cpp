/// @file graph_view_di_al.cpp
/// @brief Graph view implementation for directed graph represented by an adjacency list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/floyd_warshall.hpp>
namespace ogxx
{


auto floyd_warshall_only_matrix( const ogxx::Int_matrix& distances)
{
auto n = distances.shape();
auto result = ogxx::new_dense_st_matrix<Int>(n);

for (int k = 0; k < n.cols; ++k)
{
    for (int i = 0; i < n.rows; ++i)
    {
        for (int j = 0; j < n.cols ++j)
        {
           
         }
        }
    }
}

return result;
}
