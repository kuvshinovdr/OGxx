/// @file test_dense_st_matrix.cpp
/// @brief A helper file to be included in each testing cpp.
/// @author mx2-lubnin-e-v


#include "testing_head.hpp"
using namespace ogxx;

TEST_CASE("copy method test") {
    // Создаем исходную матрицу
    Dense_st_matrix<Int> matrix;
    matrix.set(0, 0, 1);
    matrix.set(0, 1, 2);
    matrix.set(0, 2, 3);
    matrix.set(1, 0, 4);
    matrix.set(1, 1, 5);
    matrix.set(1, 2, 6);
    matrix.set(2, 0, 7);
    matrix.set(2, 1, 8);
    matrix.set(2, 2, 9);

    // Создаем окно размером 2x2
    Matrix_window window({ 0, 0 }, { 2, 2 });

    // Копируем окно из исходной матрицы
    auto result = matrix.copy(window);

    // Проверяем, что копия окна соответствует ожидаемым значениям
    CHECK(result.get(0, 0) == 1);
    CHECK(result.get(0, 1) == 2);
    CHECK(result.get(1, 0) == 4);
    CHECK(result.get(1, 1) == 5);
}

TEST_CASE("copy method throw exception test") {
    // Создаем исходную матрицу
    Dense_st_matrix<Int> matrix;

    // Создаем окно, которое не помещается в матрицу
    Matrix_window window({ 0, 0 }, { 4, 4 });

    // Проверяем, что при копировании окна, выбрасывается исключение std::out_of_range
    CHECK_THROWS_AS(matrix.copy(window), std::out_of_range);
}

