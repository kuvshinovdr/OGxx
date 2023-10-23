/// @file adjacency_list.hpp
/// @brief Adjacency list graph representation interface
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_ADJACENCY_LIST_HPP_INCLUDED
#define OGXX_ADJACENCY_LIST_HPP_INCLUDED

#include "iterable.hpp"
#include "st_set.hpp"


namespace ogxx
{

  class Adjacency : public virtual Index_set, public virtual Sized_iterable<Scalar_index>
  {
  public:
    //
  };

  class Adjacency_list : public virtual Indexed_iterable<Adjacency*>
  {
  public:
    //
  };

}

#endif//OGXX_ADJACENCY_LIST_HPP_INCLUDED
