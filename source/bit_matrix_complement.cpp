#include <ogxx/bit_matrix.hpp>

class ogxx::Bit_matrix_complement: public ogxx::Bit_matrix {
public:
    Bit_matrix_complement(ogxx::Bit_matrix& orig) {
        this->_orig = make_unique(&orig);
    }

    [[nodiscard]] virtual auto get(Matrix_index position) const noexcept
    -> bool {
        return !_orig->get(position);
    };

    [[nodiscard]] auto get(Scalar_index row, Scalar_index col) const noexcept
    -> bool { return get(Matrix_index{ row, col }); }

    virtual auto set(Matrix_index position, bool value = true) {
        _orig->set(!value);
    }

    auto set(Scalar_index row, Scalar_index col, bool value = true)
    -> bool { return set(Matrix_index{row, col}, value); }

    auto reset(Matrix_index position)
    -> bool { return set(position, false); }

    auto reset(Scalar_index row, Scalar_index col)
    -> bool { return reset(Matrix_index{ row, col }); }

    virtual auto flip(Matrix_index position)
    -> bool = 0;

    auto flip(Scalar_index row, Scalar_index col)
    -> bool { return flip(Matrix_index{ row, col }); }

    virtual void fill(bool value) = 0;

    [[nodiscard]] virtual auto iterate_row(Scalar_index row) const
    -> Basic_iterator_uptr<bool> = 0;

    [[nodiscard]] virtual auto iterate_col(Scalar_index col) const
    -> Basic_iterator_uptr<bool> = 0;

    [[nodiscard]] virtual auto view(Matrix_window window) const
    -> Bit_matrix_const_uptr = 0;

    [[nodiscard]] virtual auto view(Matrix_window window)
    -> Bit_matrix_uptr = 0;

    [[nodiscard]] virtual auto copy(Matrix_window window) const
    -> Bit_matrix_uptr = 0;

    [[nodiscard]] auto copy() const
    -> Bit_matrix_uptr { return copy(Matrix_window::main(shape())); }
};
private:
    ogxx::Bit_matrix_uptr _orig;
};