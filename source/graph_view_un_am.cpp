/// @file graph_view_un_am.cpp
/// @brief Adjacency matrix of undirected graph adapter.
/// @author Soldatov D. V.
#include <ogxx/graph_view.hpp>
#include <ogxx/bit_matrix.hpp>


namespace ogxx
{
    class Undirected_adjacency_matrix_edge_iter
        : public Vertex_pair_iterator
    {
    public:
      Undirected_adjacency_matrix_edge_iter(Bit_matrix& bit) noexcept
        : bit_m(bit)
      {
          sz = bit_m.shape().rows;
      }

      auto next(Vertex_pair& out_item) noexcept
        -> bool override
      {
          for (;; ++col)
          {
              if (col == sz)
                  col = ++row + 1;
        
              if (row == sz)
                  return false;
          
              if (bit_m.get(row, col))
              {
                  out_item = Vertex_pair(row, col); // u < v
                  return true;
              }
          }
      }

    private:
        Bit_matrix&  bit_m;
        Scalar_index row = 0, col = 1, sz = 0;
    };


    class Graph_view_undirected_adjacency_matrix
        : public Graph_view
    {
    public:
        Graph_view_undirected_adjacency_matrix(Bit_matrix &bit)
          : bit_m(bit)
        {
          if (!bit.shape().is_square())
            throw std::invalid_argument("Graph_view_undirected_adjacency_matrix::ctor: the matrix must be square.");
        }

        [[nodiscard]] auto vertex_count() const noexcept
          -> Scalar_size override
        {
            return bit_m.shape().rows;
        }

        [[nodiscard]] auto edge_count() const noexcept
        -> Scalar_size override
        {
            Scalar_size sz = this->vertex_count();
            if (sz == 0) return 0;
            Scalar_size res = 0;
            for(Scalar_size i = 0; i < sz-1; ++i)
                for(Scalar_size j = i + 1; j < sz; ++j)
                    res += (bit_m.get(i,j)? 1: 0);
            return res;
        }

        [[nodiscard]] auto iterate_edges() const
          -> Vertex_pair_iterator_uptr override
        {
          return std::make_unique<Undirected_adjacency_matrix_edge_iter>(bit_m);
        }

        [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept
          -> bool override
        {
            if (edge.second < edge.first)
              std::swap(edge.first, edge.second);

            return bit_m.get(edge.first, edge.second);
        }

        void set_vertex_count(Scalar_size count) override
        {
            bit_m.reshape(Matrix_shape::square(count));
            bit_m.fill(false);
        }

        auto connect(Vertex_pair edge)
          -> bool override
        {
            // TODO: what if edge.first == edge.second?
            // TODO: symmetric case: set(second, first)?
            return !bit_m.set(edge.first, edge.second);
        }
        
        auto disconnect(Vertex_pair edge)
          -> bool override
        {
            // TODO: what if edge.first == edge.second?
            // TODO: symmetric case: set(second, first)?
            return !bit_m.reset(edge.first, edge.second);
        }

    private:
        Bit_matrix& bit_m;
    };


    namespace undirected
    {
        auto graph_view(Bit_matrix& am)
          -> Graph_view_uptr
        {
          return std::make_unique<Graph_view_undirected_adjacency_matrix>(am);
        }
    }

}
