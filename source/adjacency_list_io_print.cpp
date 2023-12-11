#include "ogxx/adjacency_list_io.hpp"

void ogxx::io::print(std::ostream& ostr, ogxx::Adjacency_list const& adj_list) {
    auto sz = adj_list.size();

    for (Scalar_index vertex_ind = 0; vertex_ind < sz; ++vertex_ind) {
        auto const neighbours = adj_list.get(vertex_ind);

        ostr << "Neighbours for vertex " << vertex_ind << ": ";

        auto iterator = neighbours->iterate();
        for (Scalar_index neighbour_index; iterator->next(neighbour_index);) {
            ostr << neighbour_index <<  ", ";
        }
        ostr << "\n";
    }
}