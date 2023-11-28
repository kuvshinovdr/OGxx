/// @file adjacency_implementations.cpp
/// @brief ogxx::Adjacency implementations based upon different Index_set implementations
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include "index_set_hashtable.hpp"
#include <ogxx/adjacency_list.hpp>

namespace ogxx
{
  
  class Adjacency_hashtable
    : public Index_set_hashtable
    , public Adjacency
  {
  public:
    using Index_set_hashtable::contains;
    using Index_set_hashtable::erase;
    using Index_set_hashtable::insert;
    using Index_set_hashtable::is_empty;
    using Index_set_hashtable::iterate;
    using Index_set_hashtable::size;
  };
  

  auto new_adjacency_hashtable()
    -> Adjacency_uptr
  {
    return std::make_unique<Adjacency_hashtable>();
  }

}
