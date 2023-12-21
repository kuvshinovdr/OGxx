#include <ogxx/adjacency_list_io.hpp>

namespace ogxx::io
{
    std::ostream& print(
        std::ostream& ostr, 
        Adjacency_list const& adj_list,
        Adjacency_list_format const& format
      )
    {
        auto sz = adj_list.size();

        ostr << format.list_open;

        for (Scalar_index vertex_ind = 0; vertex_ind < sz; ++vertex_ind) {
            auto const neighbours = adj_list.get(vertex_ind);

            ostr << vertex_ind << format.adjacency_open;

            Scalar_size adj_sz = neighbours->size(), i = 1;

            auto iterator = neighbours->iterate();
            for (Scalar_index neighbour_index; iterator->next(neighbour_index);) {
                ostr << neighbour_index;
                if (i != adj_sz)
                    ostr << format.adjacency_sep;
                ++i;
            }

            ostr << format.adjacency_close;
        }

        return ostr << format.list_close;
    }
}
