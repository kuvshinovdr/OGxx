/// @file symmetric_dense_st_matrix.cpp
/// @brief Implementation of a class for compact storage of a symmetric matrix.
/// @author Martianov.K 
#include <ogxx/st_matrix.hpp>
#include <ogxx/stl_iterator.hpp>

#include <vector>
#include <stdexcept>
 
namespace ogxx
{
  /// @class Symmetric_dense_st_matrix
  /// @brief A class that represents a symmetric matrix in dense storage format.
  /// @tparam ST The type of elements stored in the matrix.
  template <typename ST>
  class Symmetric_dense_st_matrix : public St_matrix<ST>
  {
  private:
    std::vector<ST> data_; ///< The vector that stores the elements of the matrix.
    size_t size_;          ///< The size of the matrix.

  public:
    /// @brief Constructor that initializes the matrix with a given size.
    /// @param size The size of the matrix.
    Symmetric_dense_st_matrix(size_t size)
      : data_( (size + (size & 1)) / 2 * (size + (~size & 1)) ), size_(size)
    {
      // TODO: check size overflow.
      if (size == 0)
        throw std::invalid_argument("Matrix size must be greater than 0.");
    }

    /// @brief Returns the shape of the matrix.
    /// @return The shape of the matrix.
    [[nodiscard]] Matrix_shape shape() const noexcept override
    {
      return { size_, size_};
    }

    /// @brief Reshapes the matrix to a new shape.
    /// @param new_shape The new shape of the matrix
    void reshape(Matrix_shape new_shape) override
    {
      if (new_shape.rows != new_shape.cols)
        throw std::invalid_argument("Symmetric matrix must have equal rows and cols.");
      
      size_ = new_shape.rows;
      data_.resize(size_ * (size_ + 1) / 2); // TODO: check overflow.
    }

    auto iterate() const
      -> Basic_iterator_uptr<ST> override
    {
    return new_stl_iterator(data_);
    }

    auto is_empty() const noexcept
      -> bool override
    {
    return data_.empty();
    }
    
    auto size() const noexcept
      -> Scalar_size override
    {
    return data_.size();
    }
   
    auto iterate_col(Scalar_index col) const
      -> Basic_iterator_uptr<ST> override
    {
      if (col >= size_)
        throw std::out_of_range("Symmetric_dense_st_matrix::iterate_col: col index out of range.");

      // TODO: implement later.
      throw std::logic_error("Symmetric_dense_st_matrix::iterate_col: not implemented");
    }
   
    auto iterate_row(Scalar_index row) const
      -> Basic_iterator_uptr<ST> override
    {
      if (row >= size_)
        throw std::out_of_range("Symmetric_dense_st_matrix::iterate_row: row index out of range.");

      // TODO: implement later.
      throw std::logic_error("Symmetric_dense_st_matrix::iterate_row: not implemented");
    }
    
    auto view(Matrix_window window) const
      -> St_matrix_const_uptr<ST> override
    {
    throw std::logic_error("Symmetric_dense_st_matrix::view not implemented.");
    }
    
    auto view(Matrix_window window)
      -> St_matrix_uptr<ST> override
    {
    throw std::logic_error("Symmetric_dense_st_matrix::view not implemented.");
    }

    /// @brief Make a copy of a window of the matrix into a separate matrix object.
    /// @param window the region to copy
    /// @return a separate ST matrix object
    auto copy(Matrix_window window)
        -> St_matrix_uptr<ST> override
    {
        if (!window.fits_into({ size_, size_ })) {
            throw std::out_of_range("Symmetric_dense_st_matrix::copy: invalid matrix window.");
        }
    
        // Создаем новую матрицу с размером окна
        auto copied_matrix = new_dense_st_matrix<ST>(window.shape);
    
        // Копируем данные из исходной матрицы в новую
        for (size_t i = 0; i < window.shape.rows; ++i) {
            for (size_t j = 0; j < window.shape.cols; ++j) {
                copied_matrix->set(i, j, this->get(i, j));
            }
        }
    
        return copied_matrix;
    }

    
    [[nodiscard]] auto get(Matrix_index position) const noexcept -> ST override
    {
      Matrix_shape const shape{ size_, size_ };
      if (shape.check_and_correct(position))
        return data_[shape.upper_index(position)];// так вроде верно. Отсчет с 0.
      return ST{}; // Значение по умолчанию, когда оно выходит за пределы диапазона
    }

    // Метод set
    auto set(Matrix_index position, ST value) -> ST override
    {
      Matrix_shape const shape{ size_, size_ };
      if (shape.check_and_correct(position))
        throw std::out_of_range("Symmetric_dense_st_matrix::set: matrix position out of range.");

      auto index = shape.upper_index(position);
      auto old_value = data_[index];
      data_[index] = value;
      return old_value;
    }

    // Реализация метода заполнения
    void fill(ST value) noexcept override
    {
      std::fill(data_.begin(), data_.end(), value);
    }
  };

}