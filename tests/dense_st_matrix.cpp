/// @file dense_st_matrix.cpp
/// @brief A helper file to be included in each testing cpp.
/// @author mx2-lubnin-e-v
#include "testing_head.hpp"
#include <ogxx/st_matrix.hpp>

TEST_SUITE("Dense_st_matrix")
{
  TEST_CASE("copy method test") {
      // Создаем исходную матрицу
      auto matrix_ptr = new_dense_st_matrix<Int>({3, 3});
      auto& matrix = *matrix_ptr;
      matrix.set({ 0, 0 }, 1);
      matrix.set({ 0, 1 }, 2);
      matrix.set({ 0, 2 }, 3);
      matrix.set({ 1, 0 }, 4);
      matrix.set({ 1, 1 }, 5);
      matrix.set({ 1, 2 }, 6);
      matrix.set({ 2, 0 }, 7);
      matrix.set({ 2, 1 }, 8);
      matrix.set({ 2, 2 }, 9);

      // Создаем окно размером 2x2
      Matrix_window window({ 0, 0 }, { 2, 2 });

      // Копируем окно из исходной матрицы
      auto result = matrix.copy(window);

      // Проверяем, что копия окна соответствует ожидаемым значениям
      CHECK(result->get({ 0, 0 }) == 1);
      CHECK(result->get({ 0, 1 }) == 2);
      CHECK(result->get({ 1, 0 }) == 4);
      CHECK(result->get({ 1, 1 }) == 5);

      window.position = { 1, 1 };
      result = matrix.copy(window);
      CHECK(result->get({ 0, 0 }) == 5);
      CHECK(result->get({ 0, 1 }) == 6);
      CHECK(result->get({ 1, 0 }) == 8);
      CHECK(result->get({ 1, 1 }) == 9);
  }

  TEST_CASE("copy method throw exception test") {
      // Создаем исходную матрицу
      auto matrix_ptr = new_dense_st_matrix<Int>({ 2, 2 });

      // Создаем окно, которое не помещается в матрицу
      Matrix_window window({ 0, 0 }, { 4, 4 });

      // Проверяем, что при копировании окна, выбрасывается исключение std::out_of_range
      Int_matrix_uptr suppress;
      CHECK_THROWS_AS(suppress = matrix_ptr->copy(window), std::out_of_range);
  }
}
