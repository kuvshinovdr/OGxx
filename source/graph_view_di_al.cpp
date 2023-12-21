/// @file graph_view_di_al.cpp
/// @brief Graph view implementation for directed graph represented by an adjacency list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/graph_view.hpp>
#include <ogxx/adjacency_list.hpp>
#include <ogxx/stl_iterator.hpp>

namespace ogxx
{

  namespace
  {

    class Vertex_pair_iterator_di_al
      : public Basic_iterator<Vertex_pair>
    {
    public:
      Vertex_pair_iterator_di_al(Adjacency_list const& al)
        : _al(al), _al_size(_al.size()), _cur_from(0)
      {
        if (_cur_from < _al_size)
        {
          if (auto const adj_ptr = _al.get(_cur_from).adjacency)
            _adj = adj_ptr->iterate();
        }
      }


      auto next(Vertex_pair& out_item) noexcept
        -> bool                        override
      {
        if (_cur_from >= _al_size)
          return false;

        for (;;)
        {
          if (Vertex_index to; _adj->next(to))
          {
            out_item = Vertex_pair{ _cur_from, to };
            return true;
          }

          if (++_cur_from == _al_size)
            return false;
          
          if (auto const adj_ptr = _al.get(_cur_from).adjacency)
            _adj = adj_ptr->iterate();
        }
      }

    private:
      Adjacency_list const&             _al;
      Scalar_size                       _al_size;
      Scalar_index                      _cur_from;
      Basic_iterator_uptr<Scalar_index> _adj;
    };


    template <bool is_constant>
    class Graph_view_directed_adjacency_list
      : public Graph_view
    {
    public:
      using Adjacency_list_ref = 
        std::conditional_t<is_constant,
                           Adjacency_list const&,
                           Adjacency_list&>;

      explicit Graph_view_directed_adjacency_list(Adjacency_list_ref al)
        : _al(al) {}

      
      // Constant interface

      [[nodiscard]] auto is_directed() const noexcept
        -> bool
      {
        return true;
      }

      [[nodiscard]] auto vertex_count() const noexcept
        -> Scalar_size                  override
      {
        return _al.get_vertex_count();
      }

      [[nodiscard]] auto edge_count() const noexcept
        -> Scalar_size                override
      {
        return _al.degrees_sum();
      }

      [[nodiscard]] auto iterate_edges() const
        -> Vertex_pair_iterator_uptr     override
      {
        return std::make_unique<Vertex_pair_iterator_di_al>(_al);
      }

      [[nodiscard]] auto iterate_neighbors(Vertex_index from) const
        -> Index_iterator_uptr                                override
      {
        if (auto const adj_ptr = _al.get(from).adjacency)
          return adj_ptr->iterate();

        static Scalar_index const dummy;
        return new_stl_iterator(&dummy, &dummy);
      }

      [[nodiscard]] auto are_connected(Vertex_pair edge) const noexcept
        -> bool                                          override
      {
        auto const [from, to] = edge;
        if (max(from, to) >= _al.size())
          return false;

        if (auto const adj_ptr = _al.get(from).adjacency)
          return adj_ptr->contains(to);
        return false;
      }

     
      // Non-constant interface

      void set_vertex_count(Scalar_size count) override
      {
        if constexpr (is_constant)
        {
          throw std::logic_error("Graph_view::set_vertex_count: constness violation.");
        }
        else
        {
          _al.set_vertex_count(count);
        }
      }

      auto connect(Vertex_pair edge)
        -> bool override
      {
        if constexpr (is_constant)
        {
          throw std::logic_error("Graph_view::connect: constness violation.");
        }
        else
        {
          auto const [from, to] = edge;

          auto adj_ptr = _al.get(from).adjacency;
          Adjacency_uptr adj_storage;
          if (!adj_ptr)
          {
            adj_storage = new_adjacency_sortedvector();
            adj_ptr     = adj_storage.get();
          }

          auto const result = adj_ptr->insert(to);

          if (adj_storage)
            _al.set(from, { from, adj_storage.release() });

          return result;
        }
      }

      auto disconnect(Vertex_pair edge)
        -> bool override
      {
        if constexpr (is_constant)
        {
          throw std::logic_error("Graph_view::disconnect: constness violation.");
        }
        else
        {
          auto const [from, to] = edge;
          if (auto const adj_ptr = _al.get(from).adjacency)
            return adj_ptr->erase(to);
          return false;
        }
      }

    private:
      Adjacency_list_ref _al;
    };

  }


  namespace directed
  {
    auto graph_view(Adjacency_list const& al)
      -> Graph_view_const_uptr
    {
      return std::make_unique<Graph_view_directed_adjacency_list<true>>(al);
    }

    auto graph_view(Adjacency_list& al)
      -> Graph_view_uptr
    {
      return std::make_unique<Graph_view_directed_adjacency_list<false>>(al);
    }
  }

}
