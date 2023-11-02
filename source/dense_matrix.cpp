/// @file dense_matrix.cpp
/// @brief Dense matrix implementation (of abstract matrix interface from matrix.hpp).
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#include "matrix.hpp"

namespace ogxx
{

template<typename ST>
class Dense_st_matrix : public St_matrix<ST>
{
private:
	Matrix_shape shape_;
	std::vector<ST> matrix_;
public:
	// Конструктор класса
	Dense_st_matrix(Matrix_shape shape) {
		reshape(shape);
	}
	// Метод для получения размерности матрицы
	Matrix_shape shape() const {
		return shape_;
	}
	// Метод для изменения размерности матрицы
	void reshape(Matrix_shape shape) {
		shape_ = shape;
		matrix_.resize(shape.rows * shape.columns);
	}
	// Метод для получения значения элемента матрицы по позиции
	ST get(Matrix_index position) const {
		// TODO: Добавьте проверку на корректность позиции
		return matrix_[position.row * shape_.columns + position.column];
	}
	// Метод для установки значения элемента матрицы по позиции
	void set(Matrix_index position, ST value) {
		// TODO: Добавьте проверку на корректность позиции
		matrix_[position.row * shape_.columns + position.column] = value;
	}
	// Метод для заполнения всей матрицы одним значением
	void fill(ST value) {
		std::fill(matrix_.begin(), matrix_.end(), value);
	}
};

}
