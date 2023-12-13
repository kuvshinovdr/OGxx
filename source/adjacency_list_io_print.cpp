#include "ogxx/adjacency_list_io.hpp"

void ogxx::io::print(std::ostream& ostr, ogxx::Adjacency_list const& adj_list, Adjacency_list_format const& format = {}) {
    auto sz = adj_list.size();

    ostr << format.list_open;

    for (Scalar_index vertex_ind = 0; vertex_ind < sz; ++vertex_ind) {
        auto const neighbours = adj_list.get(vertex_ind);

        ostr << vertex_ind << format.adjacency_open;

        auto iterator = neighbours->iterate();
        for (Scalar_index neighbour_index; iterator->next(neighbour_index);) {
            ostr << neighbour_index <<  format.adjacency_sep;
        }

        ostr << format.adjacency_close;
    }

    ostr << format.list_close;
}
