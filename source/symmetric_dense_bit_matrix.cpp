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
            bit_contain.resize((element_count  + word_bits -1) / word_bits);
            _shape = shape;
        }

        // Получить значение бита по позиции
        bool get(Matrix_index position) override{
            if(position.check_and_correct(_shape)){
                auto const bit_index = position.row * _shape.cols + position.col;
                if(position.row <= position.col) {
                    auto const word_index = bit_index / word_bits;
                    auto const bit_in_word = bit_index % word_bits;
                    return ((bit.contain[word_index] >> bit_in_word) & 1) == 1;
                }

                else{
                    // Доступ к симметричной части матрицы
                    auto const symmetric_index = position.col * _shape.cols + position.row;
                    auto const word_index = symmetric_index / word_bits;
                    auto const bit_in_word = symmetric_index % word_bits;
                    return ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
                }
            }
            return false;
        }
        // Установить значения бита по позиции
        bool set(Matrix_index position, bool value) override {
            if (position.check_and_correct(_shape)) {
                auto const bit_index = position.row * _shape.cols + position.col;
                auto const word_index = bit_index / word_bits;
                auto const word = bit_contain[word_index];
                auto const bit_in_word = bit_index % word_bits;

                if (position.row <= position.col) {
                    bool const old = ((word >> bit_in_word) & 1) == 1;
                    if (old != value)
                        bit_contain[word_index] = word ^ (Word(1) << bit_in_word);
                    return old;
                } else {
                    //Установить симметричную часть матрицы
                    auto const symmetric_index = position.col * _shape.cols + position.row;
                    auto const symmetric_word_index = symmetric_index / word_bits;
                    auto const symmetric_bit_in_word = symmetric_index % word_bits;
                    bool const old = ((bit_contain[symmetric_word_index] >> symmetric_bit_in_word) & 1) == 1;
                    if (old != value)
                        bit_contain[symmetric_word_index] = word ^ (Word(1) << symmetric_bit_in_word);
                    return old;
                }
            }
            throw std::out_of_range("symmetric_dense_bit_matrix::set: invalid position")
        }
        // Инвертировать значение бита по позиции
        bool flip(Matrix_index position) override{
            if (position.row > _shape.rows || position.col > _shape.cols) return false;

            if (position.row <= position.col) {
                bit_contain[position.row * _shape.cols + position.col] =
                        !bit_contain[position.row * _shape.cols + position.col];
            } else {
                // Перевернуть симметричную часть матрицы
                auto const symmetric_index = position.col * _shape.cols + position.row;
                bit_contain[symmetric_index / word_bits] ^= (Word(1) << (symmetric_index % word_bits));
            }
            return true;
        }

        // Заполнить всю(половину) матрицу указанным значением
        void fill(bool value) override {
            auto const fill_val = value ? Word(-1) : 0;
            for (unsigned& word : bit_conrain) {
                word = fill_val;
            }
        }
    private:
        using Word = unsigned;
        static constexpr auto word_bits = sizeof(Word) * CHAR_BIT;

        std::vector<Word> bit_contain;
        Matrix_shape _shape;
    };
}

