/// ... make file doc comment (file/brief/author)
#include <ogxx/bit_matrix.hpp>
#include <ogxx/stl_iterator.hpp>

#include <vector>
#include <climits>


namespace ogxx {
   class Dense_bit_matrix : public Bit_matrix{
     public:

       Dense_bit_matrix() = default;

       Dense_bit_matrix(Matrix_shape shape)
       {
          reshape(shape);
       }
       
       auto iterate() const
         -> Bit_iterator_uptr override
       {
         return new_dense_bit_iterator(
           bit_contain.data(), 0, size());
       }

       auto is_empty() const noexcept
         -> bool
       {
         return bit_contain.empty();
       }

       auto size() const noexcept
         -> Scalar_size override
       {
         return _shape.element_count();
       }

        // Возвращает размерность матрицы
        Matrix_shape shape() const noexcept override {
            return _shape;
        }

        // Изменяет размерность матрицы
        void reshape(Matrix_shape shape) override {
            if (!shape.is_valid())
              throw std::invalid_argument("Dense_bit_matrix::reshape: shape is invalid");
            
            auto const element_count = shape.element_count();

            // Изменяем размер вектора, но не заботимся о содержимом
            bit_contain.resize((element_count + word_bits - 1) / word_bits);
            _shape = shape;
        }

        // Получить значение бита по позиции
        bool get(Matrix_index position) const noexcept override {
            if (_shape.check_and_correct(position))
            {
                auto const bit_index   = _shape.linear_index(position);
                auto const word_index  = bit_index / word_bits;
                auto const bit_in_word = bit_index % word_bits;
                return ((bit_contain[word_index] >> bit_in_word) & 1) == 1;
            }
            
            return false;
        }

        // Установить значение бита по позиции
        bool set(Matrix_index position, bool value) override {
          if (_shape.check_and_correct(position))
          {
            auto const bit_index   = _shape.linear_index(position);
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
			    if (_shape.check_and_correct(position))
          {
				    auto const bit_index   = _shape.linear_index(position);
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
        auto iterate_row(Scalar_index row) const
          -> Basic_iterator_uptr<bool> override 
        {
          throw std::logic_error("Dense_bit_matrix::iterate_row: not implemented");
        }

         //временная заглушка функции
        auto iterate_col(Scalar_index col) const
          -> Basic_iterator_uptr<bool> override
        {
          throw std::logic_error("Dense_bit_matrix::iterate_col: not implemented");
        }

        auto view(Matrix_window window) const
          -> Bit_matrix_const_uptr override 
        {
          throw std::logic_error("Dense_bit_matrix::view: not implemented");
        }

        auto view(Matrix_window window)
          -> Bit_matrix_uptr override
        {
          throw std::logic_error("Dense_bit_matrix::view: not implemented");
        }

        auto copy(Matrix_window window) const
          -> Bit_matrix_uptr override
        {
          if (!window.fits_into(_shape))
            throw std::out_of_range("Dense_bit_matrix::copy: window does not fit into the shape of the matrix");

          auto copy = new_dense_bit_matrix(window.shape);

          for (Scalar_index i = 0; i < window.shape.rows; i++) {
            for (Scalar_index j = 0; j < window.shape.cols; ++j) {
              auto value = get({ window.position.row + i, window.position.col + j });
              copy->set(i, j, value);
            }
          }

          return copy;
        }
        
    private:
        using Word = unsigned;
        static constexpr auto word_bits = sizeof(Word) * CHAR_BIT;

        std::vector<Word> bit_contain;
        Matrix_shape _shape;
   };


   auto new_dense_bit_matrix(Matrix_shape shape)
     -> Bit_matrix_uptr
   {
     return std::make_unique<Dense_bit_matrix>(shape);
   }

}

