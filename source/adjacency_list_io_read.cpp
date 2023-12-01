/// @file adjacency_list_io_read.cpp
/// @brief Implementation of ogxx::io::read function for Adjacency_list.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/adjacency_list_io.hpp>
#include "parsing_utils.hpp"

#include <vector>
#include <unordered_map>


namespace ogxx::io
{

  auto read(std::string_view& in, ogxx::Adjacency_list& al, Adjacency_list_format const& format)
    -> bool
  {
    if (!util::accept_tokens(in, format.list_open))
      return false;

    using Adj = std::vector<Scalar_index>;
    using Adj_list = std::unordered_map<Scalar_index, Adj>;

    Adj_list list;

    Scalar_index max_vertex_index = 0;
    while (!util::accept_tokens(in, format.list_close))
    {
      auto opt_from = util::read<Scalar_index>(in);
      if (!opt_from || !util::accept_tokens(in, format.adjacency_open))
        return false;

      auto const from = *opt_from;
      max_vertex_index = std::max(max_vertex_index, from);

      for (auto& adj = list[from]; !util::accept_tokens(in, format.adjacency_close);)
      {
        auto opt_to = util::read<Scalar_index>(in);
        if (!opt_to)
          return false;

        auto const to = *opt_to;
        max_vertex_index = std::max(max_vertex_index, to);
        adj.push_back(to);
      }
    }

    al.clear();
    al.set_vertex_count(max_vertex_index + 1);
    for (auto&& [u, vs] : list)
    {
      auto const adj = al.get(u);
      for (auto v: vs)
        adj->insert(v);
    }

    return true;
  }

}
