/// ... make file doc comment (file/brief/author)
#include <vector>
#include <ogxx/bit_matrix.hpp>

#include <stdexcept>
#include <climits>


namespace ogxx {
   class Dense_bit_matrix : public Bit_matrix{
     public:
       
        // Возвращает размерность матрицы
        Matrix_shape shape() override {
            return _shape;
        }

        // Изменяет размерность матрицы
        void reshape(Matrix_shape shape) override {
            if (!shape.is_valid())
              throw std::invalid_argument("Dense_bit_matrix::reshape: shape is invalid");
            
            auto const element_count = _shape.element_count();

            // Изменяем размер вектора, но не заботимся о содержимом
            bit_contain.resize((element_count + word_bits - 1) / word_bits);
            _shape = shape;
        }

        // Получить значение бита по позиции
        bool get(Matrix_index position)  override {
            if (position.check_and_correct(_shape))
            {
                auto const bit_index   = position.linear_index(_shape);
                auto const word_index  = bit_index / word_bits;
                auto const bit_in_word = bit_index % word_bits;
                return ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
            }
            
            return false;
        }

        // Установить значение бита по позиции
        bool set(Matrix_index position, bool value) override {
          if (position.check_and_correct(_shape))
          {
            auto const bit_index   = position.linear_index(_shape);
            auto const word_index  = bit_index / word_bits;
            auto const word        = bit_contain[word_index];
            auto const bit_in_word = bit_index % word_bits;
            bool const old         = ((word >> bit_in_word) & 1) == 1;
            if (old != value)
                bit_contain[word_index] = word ^ (Word(1) << bit_in_word);

            return old;
          }

          throw std::out_of_range("Dense_bit_matrix::set: invalid position");
        }

        // Инвертировать значение бита по позиции
        bool flip(Matrix_index position) override {
			if (position.check_and_correct(_shape)) {
				auto const bit_index   = position.linear_index(_shape);
				auto const word_index  = bit_index / word_bits;
				auto const word        = bit_contain[word_index];
				auto const bit_in_word = bit_index % word_bits;
				bool const old = ((word >> bit_in_word) & 1) == 1;

				// Инвертировать значение бита
				bit_contain[word_index] = word ^ (Word(1) << bit_in_word);

				return old;
			}

			throw std::out_of_range("Dense_bit_matrix::flip: invalid position");
		}

            

        // Заполнить всю матрицу указанным значением
        void fill(bool value) override {
            auto const fill_val = value? Word(-1): 0;
            for (unsigned& word : bit_contain) {
                word = fill_val;
            }
        }
		
        //временная заглушка функции
        auto iterate_row(Scalar_index row)override {
        auto iterator = std::make_unique<bool>(true);
        return iterator;
        }
         //временная заглушка функции
        auto iterate_col(Scalar_index col)override {
        auto iterator = std::make_unique<bool>(true);
        return iterator;
        }
        auto view(Matrix_window window) override {
        
        auto bitMatrix = std::make_unique<Bit_matrix_const>();
        return bitMatrix;
        }
        
};


       
    private:
        using Word = unsigned;
        static constexpr auto word_bits = sizeof(Word) * CHAR_BIT;

        std::vector<Word> bit_contain;
        Matrix_shape _shape;
   }
}

