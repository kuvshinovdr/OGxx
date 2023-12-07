/// @file adjacency_implementations.cpp
/// @brief ogxx::Adjacency implementations based upon different Index_set implementations
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/adjacency_list.hpp>
#include "index_set_hashtable.hpp"
#include "index_set_bitvector.hpp"
#include "index_set_sortedvector.hpp"


namespace ogxx
{

  // Adjacencies
  
  namespace
  {
    template <typename Base>
    class Adjacency_sized_iterable final
      : public Base
      , public Adjacency
    {
    public:
      using Base::Base;
      
      auto contains(Scalar_index item) const noexcept
        -> bool override { return Base::contains(item); }

      auto erase(Scalar_index item)
        -> bool override { return Base::erase(item); }

      auto insert(Scalar_index item)
        -> bool override { return Base::insert(item); }

      auto is_empty() const noexcept
        -> bool       override { return Base::is_empty(); }
      
      auto size() const noexcept
        -> Scalar_size  override { return Base::size(); }

      auto iterate() const
        -> Index_iterator_uptr override { return Base::iterate(); }
    };

    template <typename Base>
    class Adjacency_indexed_iterable final
      : public Base
      , public Adjacency
    {
    public:
      using Base::Base;

      auto contains(Scalar_index item) const noexcept
        -> bool override { return Base::contains(item); }

      auto erase(Scalar_index item)
        -> bool override { return Base::erase(item); }

      auto insert(Scalar_index item)
        -> bool override { return Base::insert(item); }

      auto is_empty() const noexcept
        -> bool       override { return Base::is_empty(); }

      auto size() const noexcept
        -> Scalar_size  override { return Base::size(); }

      auto iterate() const
        -> Index_iterator_uptr override { return Base::iterate(); }

      auto get(Scalar_index index) const
        -> See_by<Scalar_index>    override { return Base::get(index); }

      auto set(Scalar_index index, Pass_by<Scalar_index> value)
        -> Pass_by<Scalar_index> override { return Base::set(index, value); }
    };
  }

  using Adjacency_hashtable = Adjacency_sized_iterable<Index_set_hashtable>;
  using Adjacency_bitvector = Adjacency_sized_iterable<Index_set_bitvector>;
  using Adjacency_sortedvector = Adjacency_sized_iterable<Index_set_sortedvector>;

  

  auto new_adjacency_hashtable()
    -> Adjacency_uptr
  {
    return std::make_unique<Adjacency_hashtable>();
  }

  auto new_adjacency_hashtable(Index_iterator_uptr items)
    -> Adjacency_uptr
  {
    return std::make_unique<Adjacency_hashtable>(std::move(items));
  }


  auto new_adjacency_bitvector()
    -> Adjacency_uptr
  {
    return std::make_unique<Adjacency_bitvector>();
  }

  auto new_adjacency_bitvector(Index_iterator_uptr items)
    -> Adjacency_uptr
  {
    return std::make_unique<Adjacency_bitvector>(std::move(items));
  }


  auto new_adjacency_sortedvector()
    -> Adjacency_uptr
  {
    return std::make_unique<Adjacency_sortedvector>();
  }

  auto new_adjacency_sortedvector(Index_iterator_uptr items)
    -> Adjacency_uptr
  {
    return std::make_unique<Adjacency_sortedvector>(std::move(items));
  }


  // Adjacency lists

  // TODO: Adjacency_list_vector
  // TODO: Adjacency_list_hashtable

}
