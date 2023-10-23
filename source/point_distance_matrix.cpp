#include <iostream>
#include <vector>
#include <algorithm>
#include "ogxx/st_matrix.hpp"

// Функция, которая возвращает итератор на первый нулевой элемент в строке
std::vector<int>::iterator find_first_zero(std::vector<int>& row) {
    return std::find(row.begin(), row.end(), 0);
}

// Функция, которая переносит нули в начало строки и сдвигает остальные элементы вправо
void rotate_row(std::vector<int>& row) {
    auto first_zero = find_first_zero(row);
    if (first_zero == row.end()) {
        // Если нулей в строке нет, то ничего делать не нужно
        return;
    }

    for (auto it = first_zero + 1; it != row.end(); ++it) {
        if (*it != 0) {
            std::rotate(first_zero, it, row.end());
            // Обновляем значение итератора на первый нулевой элемент
            first_zero = find_first_zero(row);
        }
    }
}

int main() {
    // Создаем матрицу 3x3 и заполняем ее случайными значениями
    std::vector<std::vector<int>> matrix {{1, 2, 0}, {0, 3, 4}, {5, 0, 6}};

    // Печатаем исходную матрицу
    std::cout << "Original matrix:\n";
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }

    // Сдвигаем элементы в каждой строке так, чтобы нули оказались на главной диагонали
    for (auto& row : matrix) {
        rotate_row(row);
    }

    // Печатаем полученную матрицу
    std::cout << "\nTransformed matrix:\n";
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }

    return 0;
}