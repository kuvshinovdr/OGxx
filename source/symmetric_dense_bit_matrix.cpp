/// @file symmetric_dense_bit_matrix.cpp
/// @brief Symmetric_dense_bit matrix implementation (of abstract matrix interface from matrix.hpp).
/// @author Shemyakin D.V.

#include <vector>
#include <ogxx/bit_matrix.hpp>

#include <stdexcept>
#include <climits>

namespace ogxx {

    class Symmetric_dense_bit_matrix : public Bit_matrix {
    public:

        // Возвращает размерность матрицы
        Matrix_shape shape() override {
            return _shape;
        }

        // Изменяет размерность матрицы
        void reshape(Matrix_shape shape) override {
            if (!shape.is_valid() || shape.rows != shape.cols) {
                throw std::invalid_argument("Symmetric_dense_bit_matrix::reshape: shape is invalid or not square")
            }

            auto const element_count = shape.element_count();

            // Изменение размера вектора, но не заботясь о содержимом
            // Теперь выделяем место только под нижнюю треугольную часть матрицы
            bit_contain.resize((element_count - shape.rows) / 2 + shape.rows);
            _shape = shape;
        }

        // Получить значение бита по позиции
        bool get(Matrix_index position) override {
            if (position.check_and_correct(_shape)) {
                auto const bit_index = position.row * _shape.cols + position.col;
                auto const symmetric_index = position.col * _shape.cols + position.row;
                auto const index = (position.row <= position.col) ? bit_index : symmetric_index;

                auto const word_index = index / word_bits;
                auto const bit_in_word = index % word_bits;
                return ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
            }

            return false;
        }

        // Установить значения бита по позиции
        bool set(Matrix_index position, bool value) override {
            if (position.check_and_correct(_shape)) {
                auto const bit_index = position.row * _shape.cols + position.col;
                auto const symmetric_index = position.col * _shape.cols + position.row;
                auto const index = (position.row <= position.col) ? bit_index : symmetric_index;

                auto const word_index = index / word_bits;
                auto const bit_in_word = bit_index % word_bits;

                bool const old = ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
                if (old != value)
                    bit_contain[word_index] ^= (Word(1) << bit_in_word);
                return old;
            }

            throw std::out_of_range("symmetric_dense_bit_matrix::set: invalid position")
        }

        // Инвертировать значение бита по позиции
        bool flip(Matrix_index position) override {
            if (position.row > _shape.rows || position.col > _shape.cols) return false;

            auto const bit_index = position.row * _shape.cols + position.col;
            auto const symmetric_index = position.col * _shape.cols + position.row;
            auto const index = (position.row <= position.col) ? bit_index : symmetric_index;

            bit_contain[index / word_bits] ^= (Word(1) << (index % word_bits));

            return true;
        }

        // Заполнить всю(половину) матрицу указанным значением
        void fill(bool value) override {
            auto const fill_val = value ? Word(-1) : 0;
            for (unsigned &word: bit_conrain) {
                word = fill_val;
            }
        }

        //Копируем только нижнюю часть матрицы
       auto copy(Matrix_window window) const
       -> Bit_matrix_uptr override {

            if (!window.is_valid() || window.start_row >= _shape.rows || window.start_col >= _shape.cols) {
                throw std::invalid_argument("Symmetric_dense_bit_matrix::copy: invalid window.");
            }

            auto new_rows = std::min(window.rows, _shape.rows - window.start_row);
            auto new_cols = std::min(window.cols, _shape.cols - window.start_col);

            auto new_matrix = std::make_unique<Symmetric_dense_bit_matrix>();

            new_matrix -> reshape({new_rows, new_cols});

            for(Scalar_index i = 0; i < new_rows; i++) {
                for(Scalar_index j = 0; j < new_cols; ++j) {
                    auto value = get({window.start_row + i, window.start_col + j});
                    new_matrix -> set({i, j}, value);
                }
            }
           return new_matrix;
        }

        auto iterate_row(Scalar_index row) const
        -> Basic_iterator_uptr<bool> override {
            throw std::logic_error("Symmetric_dense_bit_matrix:iterate_row: not implemented.");
        }

        auto iterate_col(Scalar_index col) const
        -> Basic_iterator_uptr<bool> override {
            throw std::logic_error("Symmetric_dense_bit_matrix::iterate_col: not implemented.");
        }

        auto view(Matrix_window window) const
        -> Basic_iterator_uptr<bool> override {
            throw std::logic_error("Symmetric_dense_matrix::view: not implemented.")
        }

        auto view(Matrix_window window)
        -> Basic_iterator_uptr override {
            throw std::logic_error("Symmetric_dense_matrix::view: not implemented.")
        }
    private:
        using Word = unsigned;
        static constexpr auto word_bits = sizeof(Word) * CHAR_BIT;

        std::vector<Word> bit_contain;
        Matrix_shape _shape;
    };
}

