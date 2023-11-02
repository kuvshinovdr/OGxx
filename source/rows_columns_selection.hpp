/// doc comment
/// include guards

#include <ogxx/matrix.hpp>
#include <vector>

typedef struct {
    size_t row;
    size_t col;
} Scalar_index;

typedef struct {
    size_t row;
    size_t col;
} Shape;

// namespace ogxx

class Rows_columns_selection {
private:
    std::vector<bool> selected_rows;
    std::vector<bool> selected_columns;

    std::vector<size_t> _rows;
    std::vector<size_t> _cols;
public:

    friend class Rows_columns_union; // remove it
    
    // constructor with two arguments
    Rows_columns_selection(
            const std::vector<bool> &s_rows,
            const std::vector<bool> &s_columns) :
            selected_rows(s_rows),
            selected_columns(s_columns) {

        // calculate _rows
        for (size_t r : selected_rows) // push index of a true value
            if (selected_rows[r])
                _rows.push_back(r);

        // calculate _cols
        for (size_t c : selected_columns) // push index of a true value
            if (selected_columns[c])
                _cols.push_back(c);
    }

    // find Matrix_shape of new matrix
    Shape new_matrix_shape() {
        return Shape({_rows.size(), _cols.size()});
    }

    // add operator()(Matrix_index) -> Matrix_index
    // new to old by _rows[row], _cols[col]
};

class Rows_columns_union {
public:
    std::vector<Scalar_index> convert_indices_new_to_old(const Rows_columns_selection &rcs) {
        std::vector<Scalar_index> temp_convert_matrix;
        for (size_t r = 0; r < rcs.selected_rows.size(); r++)
            for (size_t c = 0; c < rcs.selected_columns.size(); c++)
                temp_convert_matrix.push_back({rcs.selected_rows[r], rcs.selected_columns[c]});
        return temp_convert_matrix;
    }
};
