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
      util::accept_tokens(util::ltrim(in), format.pair_open);
      if (in.empty()) return false;

      std::vector<Scalar_index> temp;
      Scalar_index t = 0;
      do
      {
        in = util::ltrim(in);
        auto [ptr, ec] = std::from_chars(in.data(), in.data() + in.size(), t);
        if (ec != std::errc{}) return false;

        in.remove_prefix(ptr - in.data());

        temp.push_back(t);
      } while (util::accept_tokens(util::ltrim(in), format.pair_sep));
      
      if (temp.size() != 2) return false;
      Vertex_pair value;
      value.first = temp[0];
      value.second = temp[1];
      data.push_back(value);
      util::accept_tokens(util::ltrim(in), format.pair_close);
    }

    if(!data.empty())
    {
      //Remove repetitions
      sort(data.begin(), data.end());
      data.erase(unique(data.begin(), data.end()), data.end());

      Scalar_size size = data.size();
      for (Scalar_index i = 0; i < size; ++i) el.put(data[i]);
    }

    return true;
  }
}