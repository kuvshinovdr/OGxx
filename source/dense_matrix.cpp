#ifndef OGXX_BIT_MATRIX_HPP_INCLUDED
#define OGXX_BIT_MATRIX_HPP_INCLUDED

#include <vector>
#include <ogxx/bit_matrix.hpp>

namespace ogxx {
   Dense_bit_matrix : public Bit_matrix{
     public:
       
          // Возвращает размерность матрицы
        Matrix_shape shape() override {
            return {rows, cols};
        }

        // Изменяет размерность матрицы
        void reshape(Matrix_shape shape) override {
            rows = shape.rows;
            cols = shape.cols;
            // Изменяем размер вектора, но не заботимся о содержимом
            bit_contain.resize(rows * cols);
        }

        // Получить значение бита по позиции
        bool get(Matrix_index position)  override {
            if(position.row > rows || position.col > cols) return false;
            return bit_contain[position.row * cols + position.col];
            return true;
        }

        // Установить значение бита по позиции
        bool set(Matrix_index position, bool value) override {
            if(position.row > rows || position.col > cols) return false;
            bit_contain[position.row * cols + position.col] = value;
            return true;
        }

        // Инвертировать значение бита по позиции
        bool flip(Matrix_index position) override {
            if(position.row > rows || position.col > cols) return false;
            bit_contain[position.row * cols + position.col] = !data[position.row * cols + position.col];
            return true;
        }

        // Заполнить всю матрицу указанным значением
        void fill(bool value) override {
            for (unsigned& bit : bit_contain) {
                bit = value;
            }
        }

    private:
        std::vector<unsigned> bit_contain;
      
   }
}

#endif
