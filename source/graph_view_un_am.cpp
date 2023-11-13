/// @file graph_view_un_am.cpp
/// @brief 
/// @author Soldatov D. V.
#include <ogxx/graph_view.hpp>
#include <ogxx/bit_matrix.hpp>
#include <cmath>

namespace ogxx
{
    class Graph_view_undirected_adjacency_matrix: public Graph_view
    {
        private:
        Bit_matrix &bit_m;
        public:
        Graph_view_undirected_adjacency_matrix(Bit_matrix &bit)
         : bit_m(bit){}
        [[nodiscard]] auto vertex_count() const noexcept
        -> Scalar_size override
        {
            return std::sqrt(bit_m.size()); //если я правильно понял, что size вернёт общее количество элементов
        }
        [[nodiscard]] auto edge_count() const noexcept
        -> Scalar_size override
        {
            Scalar_size sz = this->vertex_count();
            if (sz == 0) return 0;
            Scalar_size res = 0;
            for(Scalar_size i = 0; i < sz-1; ++i)
                for(Scalar_size j = i + 1; j < sz; ++j)
                    res += bit_m.get(i,j);
            return res;
        }
        [[nodiscard]] auto iterate_edges() const
        -> Vertex_pair_iterator_uptr override
        {

        }
        [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept
        -> bool override
        {
            return bit_m.get(edge.first, edge.second);
        }
        void set_vertex_count(Scalar_size count) override
        {

        }
        auto connect(Vertex_pair edge)
        -> bool override
        {
            return !bit_m.set(edge.first, edge.second);
        }
        auto disconnect(Vertex_pair edge)
        -> bool override
        {
            return !bit_m.reset(edge.first, edge.second);
        }

    };
}