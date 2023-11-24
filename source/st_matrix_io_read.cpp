/// @file st_matrix_io_read.cpp
/// @brief Implementation of st_matrix_io.hpp's read function.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include <ogxx/st_matrix_io.hpp>
#include "parsing_utils.hpp"

#include <vector>
#include <charconv>
#include <ranges>
#include <algorithm>


namespace ogxx::io
{

  namespace impl
  {
    // The same algorithm for Item == Int and Item == Float, so doing it a template.
    template <typename Item>
    auto read(std::string_view& in, ogxx::St_matrix<Item>& m, St_matrix_format const& format)
      -> bool
    {
      // The opening sequence.
      if (!util::accept_tokens(in, format.matrix_open))
        return false;

      using Row = std::vector<Item>;
      std::vector<Row> data;

    open_:
      if (util::accept_tokens(in, format.matrix_close))
        goto finish_;

      if (util::accept_tokens(in, format.row_sep))
      {
        data.emplace_back();
        goto open_;
      }

      goto item_;
      
    after_:
      if (util::accept_tokens(in, format.matrix_close))
        goto finish_;

      if (util::accept_tokens(in, format.row_sep))
      {
        data.emplace_back();
        goto open_;
      }
      
      if (!util::accept_tokens(in, format.column_sep))
        return false;

    item_:
      {
        if (auto opt_val = util::read<Item>(in))
        {
          if (data.empty())
            data.emplace_back();

          data.back().push_back(*opt_val);
        }
        else
        {
          return false;
        }
      }

      goto after_;

    finish_:
      // Find the resulting matrix shape.
      Matrix_shape const shape
      {
        .rows = static_cast<Scalar_size>(data.size()),
        .cols = static_cast<Scalar_size>(std::ranges::max(data | std::views::transform(&Row::size)))
      };

      // Fill the matrix with the items we've read.
      m.reshape(shape);
      m.fill();

      for (Scalar_index row = 0; row < shape.rows; ++row)
      {
        auto const& data_row = data[row];
        auto const  cols     = static_cast<Scalar_index>(data_row.size());
        for (Scalar_index col = 0; col < cols; ++col)
          m.set(row, col, data_row[col]);
      }

      return true;
    }
  }


  auto read(std::string_view& in, ogxx::Int_matrix& m, St_matrix_format const& format)
    -> bool
  {
    return impl::read(in, m, format);
  }

  auto read(std::string_view& in, ogxx::Float_matrix& m, St_matrix_format const& format)
    -> bool
  {
    return impl::read(in, m, format);
  }

}
