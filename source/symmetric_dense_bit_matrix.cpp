/// @file symmetric_dense_bit_matrix.cpp
/// @brief Symmetric_dense_bit matrix implementation (of abstract matrix interface from matrix.hpp).
/// @author Shemyakin D.V.
#include <ogxx/bit_matrix.hpp>

#include <vector>
#include <climits>

namespace ogxx {

    class Symmetric_dense_bit_matrix : public Bit_matrix {
    public:

        Symmetric_dense_bit_matrix() = default;

        Symmetric_dense_bit_matrix(Scalar_size n)
        {
            reshape({ n, n });
        }

        // Возвращает размерность матрицы
        Matrix_shape shape() const noexcept override {
            return _shape;
        }

        auto iterate() const
          -> Bit_iterator_uptr override
        {
            return new_dense_bit_iterator(
                bit_contain.data(), 0, size());
        }

        auto is_empty() const noexcept
          -> bool override
        {
            return bit_contain.empty();
        }

        auto size() const noexcept
          -> Scalar_size override
        {
            return _shape.element_count();
        }

        // Изменяет размерность матрицы
        void reshape(Matrix_shape shape) override {
            if (!shape.is_valid() || !shape.is_square()) {
                throw std::invalid_argument("Symmetric_dense_bit_matrix::reshape: shape is invalid or not square");
            }

            auto const element_count = shape.element_count();

            // Изменение размера вектора, но не заботясь о содержимом
            // Теперь выделяем место только под нижнюю треугольную часть матрицы
            bit_contain.resize(
              ((element_count - shape.rows) / 2 + word_bits - 1) / word_bits);
            
            _shape = shape;
        }

        // Получить значение бита по позиции.
        bool get(Matrix_index position) const noexcept override {
            if (_shape.check_and_correct(position)) {
                // Вычисляем значение бита.
                auto const index = _shape.unmd_index(position);

                auto const word_index = index / word_bits;
                auto const bit_in_word = index % word_bits;
                return ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
            }

            return false;
        }

        // Установить значения бита по позиции
        bool set(Matrix_index position, bool value) override {
            if (_shape.check_and_correct(position)) {
                auto const index = _shape.unmd_index(position);

                auto const word_index = index / word_bits;
                auto const bit_in_word = index % word_bits;

                bool const old = ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
                if (old != value)
                    bit_contain[word_index] ^= (Word(1) << bit_in_word);
                return old;
            }

            throw std::out_of_range("symmetric_dense_bit_matrix::set: invalid position");
        }

        // Инвертировать значение бита по позиции
        bool flip(Matrix_index position) override {
          if (_shape.check_and_correct(position)) {
            auto const index = _shape.unmd_index(position);

            auto const word_index = index / word_bits;
            auto const bit_in_word = index % word_bits;

            bool const old = ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
            bit_contain[word_index] ^= (Word(1) << bit_in_word);
            return old;
          }

          throw std::out_of_range("symmetric_dense_bit_matrix::flip: invalid position");
        }

        // Заполнить всю(половину) матрицу указанным значением
        void fill(bool value) override {
            auto const fill_val = value ? Word(-1) : 0;
            for (unsigned &word: bit_contain) {
                word = fill_val;
            }
        }

        //Копируем только нижнюю часть матрицы
       auto copy(Matrix_window window) const
        -> Bit_matrix_uptr override {

            if (!window.fits_into(_shape)) {
                throw std::invalid_argument("Symmetric_dense_bit_matrix::copy: invalid window.");
            }

            auto new_matrix = new_dense_bit_matrix(window.shape);

            for(Scalar_index i = 0; i < window.shape.rows; i++) {
                for(Scalar_index j = 0; j < window.shape.cols; ++j) {
                  auto value = get({ window.position.row + i, window.position.col + j });
                    new_matrix->set(i, j, value);
                }
            }

            return new_matrix;
        }

        auto iterate_row(Scalar_index row) const
        -> Bit_iterator_uptr override {
            throw std::logic_error("Symmetric_dense_bit_matrix:iterate_row: not implemented.");
        }

        auto iterate_col(Scalar_index col) const
        -> Bit_iterator_uptr override {
            throw std::logic_error("Symmetric_dense_bit_matrix::iterate_col: not implemented.");
        }

        auto view(Matrix_window window) const
        -> Bit_matrix_const_uptr override {
            throw std::logic_error("Symmetric_dense_matrix::view: not implemented.");
        }

        auto view(Matrix_window window)
        -> Bit_matrix_uptr override {
            throw std::logic_error("Symmetric_dense_matrix::view: not implemented.");
        }

    private:
        using Word = unsigned;
        static constexpr auto word_bits = sizeof(Word) * CHAR_BIT;

        std::vector<Word> bit_contain;
        Matrix_shape _shape;
    };


    auto new_symmetric_dense_bit_matrix(Scalar_size size)
      -> Bit_matrix_uptr
    {
      return std::make_unique<Symmetric_dense_bit_matrix>(size);
    }

}

