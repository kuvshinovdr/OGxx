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
    class Adjacency_sized_iterable
      : public Base
      , public Adjacency
    {
    public:
      using Base::Base;
      using Base::contains;
      using Base::erase;
      using Base::insert;
      using Base::is_empty;
      using Base::iterate;
      using Base::size;
    };

    template <typename Base>
    class Adjacency_indexed_iterable
      : public Base
      , public Adjacency
    {
    public:
      using Base::Base;
      using Base::contains;
      using Base::erase;
      using Base::insert;
      using Base::is_empty;
      using Base::iterate;
      using Base::size;
      using Base::set;
      using Base::get;
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
