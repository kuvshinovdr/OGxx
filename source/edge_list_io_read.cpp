/// @file edge_list_io_read.hpp
/// @brief Implementation of functions 'read' from 'edge_list_io.hpp'
/// @author Chaplygin M.D.


#include <ogxx/edge_list_io.hpp>
#include "source/parsing_utils.hpp"

#include <vector>
#include <charconv>
#include <algorithm>

namespace ogxx::io
{

  auto read(string_view& in, ogxx::Edge_list& el, Edge_list_format const& format)
    -> bool
  {
    if (!util::accept_tokens(util::ltrim(in), format.list_open)) return false;

    std::vector<Vertex_pair> data;

    for (; !util::accept_tokens(util::ltrim(in), format.list_close);)
    {
      if (!util::accept_tokens(util::ltrim(in), format.pair_open) || in.empty()) 
        return false;

      Vertex_index u, v;
      auto opt = util::read<Vertex_index>(in);
      if (!opt || !util::accept_tokens(util::ltrim(in), format.pair_sep))
        return false;

      u = *opt;
      opt = util::read<Vertex_index>(in);
      if (!opt)
        return false;

      v = *opt;
      data.emplace_back(u, v);
      if (!util::accept_tokens(util::ltrim(in), format.pair_close))
        return false;
    }

    if (!data.empty())
    {
      //Remove repetitions
      sort(data.begin(), data.end());
      data.erase(unique(data.begin(), data.end()), data.end());
      
      for (auto vp: data)
        el.put(vp);
    }

    return true;
  }
}