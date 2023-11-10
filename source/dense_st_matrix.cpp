/// @file dense_st_matrix.cpp
/// @brief Dense matrix implementation (of abstract matrix interface from matrix.hpp).
/// @author 
#include <ogxx/st_matrix.hpp>
#include <ogxx/stl_iterator.hpp>
#include <vector>
#include <algorithm>//fill

namespace ogxx
{

	template<typename ST>
	class Dense_st_matrix : public St_matrix<ST>
	{
	private:
		Matrix_shape shape_;
		std::vector<ST> matrix_;

	public:
		Dense_st_matrix(Dense_st_matrix const&) = default;
		Dense_st_matrix(Dense_st_matrix&&)      = default;
		Dense_st_matrix& operator=(Dense_st_matrix const&) = default;
		Dense_st_matrix& operator=(Dense_st_matrix&&)      = default;

		/// Создаёт пустую матрицу.
		Dense_st_matrix() = default;

		// Конструктор класса
		explicit Dense_st_matrix(Matrix_shape shape) {
			reshape(shape);
		}

		// Метод для получения размерности матрицы
		Matrix_shape shape() const noexcept override {
			return shape_;
		}

		// Метод для изменения размерности матрицы
		void reshape(Matrix_shape shape) override {
			matrix_.resize(shape.element_count());
			shape_ = shape;
		}

		Basic_iterator_uptr<ST> iterate() const override {
			return new_stl_iterator(matrix_);
		}

		bool is_empty() const noexcept {
			return matrix_.empty();
		}

		Scalar_size size() const noexcept {
			return static_cast<Scalar_size>(matrix_.size());
		}

		// Метод для получения значения элемента матрицы по позиции
		ST get(Matrix_index position) const noexcept override {
			if (shape_.check_and_correct(position))
				return matrix_[shape_.linear_index(position)];
			return {};
		}

		// Метод для установки значения элемента матрицы по позиции
		ST set(Matrix_index position, ST value) override {
			if (shape_.check_and_correct(position))
			{
				ST result = value;
				std::swap(result, matrix_[shape_.linear_index(position)]);
				return result;
			}

			throw std::out_of_range("Dense_st_matrix::set: invalid position");
		}

		// Метод для заполнения всей матрицы одним значением
		void fill(ST value = {}) noexcept override {
			std::fill(matrix_.begin(), matrix_.end(), value);
		}

		Basic_iterator_uptr<ST> iterate_row(Scalar_index row) const override {
			throw std::logic_error("St_matrix::iterate_row: not implemented");
		}

		Basic_iterator_uptr<ST> iterate_col(Scalar_index col) const override {
			throw std::logic_error("St_matrix::iterate_col: not implemented");
		}

		St_matrix_const_uptr<ST> view(Matrix_window window) const override {
			throw std::logic_error("St_matrix::view(const): not implemented");
		}

		St_matrix_uptr<ST> view(Matrix_window window) override {
			throw std::logic_error("St_matrix::view: not implemented");
		}

		St_matrix_uptr<ST> copy(Matrix_window window) override {
			if (!shape_.check_and_correct(window.position))
				throw std::out_of_range("Dense_st_matrix::copy: invalid window position");
			
			if (!shape_.contains({ window.position.row + window.shape.rows - 1,
				                     window.position.col + window.shape.cols - 1 }))
				throw std::out_of_range("Dense_st_matrix::copy: window does fit into the matrix");

			auto  result = std::make_unique<Dense_st_matrix<ST>>(window.shape);
			auto& sub    = static_cast<Dense_st_matrix<ST>&>(*result);

			// Copy elements from this->matrix_ to sub.matrix_
			Scalar_index rp = window.position.row * shape_.rows + window.position.col;
			for (Scalar_index row = 0, wp = 0; row < window.shape.rows; ++row, rp += shape_.cols) {
				for (Scalar_index col = 0; col < window.shape.cols; ++col, ++wp) {
					sub.matrix_[wp] = this->matrix_[rp + col];
				}
			}

			return result;
		}
	};


	template<> auto new_dense_st_matrix<Int>(Matrix_shape shape)
		-> St_matrix_uptr<Int>
	{
		return std::make_unique<Dense_st_matrix<Int>>(shape);
	}

	template<> auto new_dense_st_matrix<Float>(Matrix_shape shape)
		-> St_matrix_uptr<Float>
	{
		return std::make_unique<Dense_st_matrix<Float>>(shape);
	}

}
