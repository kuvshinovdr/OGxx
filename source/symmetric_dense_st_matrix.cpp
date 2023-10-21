
#include <ogxx/st_matrix.hpp>
#include <vector>
#include <stdexcept>
namespace ogxx
{
  
  template <typename ST>
  class Symmetric_dense_st_matrix : public St_matrix<ST>
  {
  private:
    std::vector<ST> data;
    size_t size;

  public:
    Symmetric_dense_st_matrix(size_t size): data(size * (size + 1) / 2, ST{}), size(size)
    {
      if (size == 0)
        throw std::invalid_argument("Matrix size must be greater than 0.");
    }

    // Метод Shape
    [[nodiscard]] Matrix_shape shape() const noexcept override
    {
      return { size, size};
    }

    // Метод reshape
    void reshape(Matrix_shape new_shape) override
    {
      if (new_shape.rows != new_shape.cols)
        throw std::invalid_argument("Symmetric matrix must have equal rows and cols.");
      
      size = new_shape.rows;
      data.resize(size * (size + 1) / 2, ST{});
    }

    // Метод get
    [[nodiscard]] auto get(Matrix_index position) const noexcept -> ST override
    {
      if (position.row >= size || position.col >= size)
        return ST{}; // Значение по умолчанию, когда оно выходит за пределы диапазона

      if (position.row > position.col)
        std::swap(position.row, position.col); // Убедитесь, что row <= col для симметрии

      return data[position.row * size - (position.row - 1) * position.row / 2 + position.col - position.row];
    }

    // Метод set
    auto set(Matrix_index position, ST value) -> ST override
    {
      if (position.row >= size || position.col >= size)
        throw std::out_of_range("Matrix position out of range.");

      if (position.row > position.col)
        std::swap(position.row, position.col); // Обеспечиваем row <= col для симметрии

      auto index = position.row * size - (position.row - 1) * position.row / 2 + position.col - position.row;
      auto old_value = data[index];
      data[index] = value;
      return old_value;
    }

    // Реализация метода переворота
    void flip(Matrix_index position)
    {
      auto current_value = get(position);
      set(position, !current_value);
    }

    // Реализация метода заполнения
    void fill(ST value) noexcept override
    {
      std::fill(data.begin(), data.end(), value);
    }
  };
}
