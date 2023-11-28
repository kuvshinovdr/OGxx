/// @file symmetric_dense_st_matrix_test.cpp
/// @brief Tests for Symmetric_dense_st_matrix.
/// @author Martianov K.S
#include "testing_head.hpp"
#include <../source/symmetric_dense_st_matrix.cpp>


TEST_CASE("Testing Symmetric_dense_st_matrix") {
    ogxx::Symmetric_dense_st_matrix<int> matrix(5);

    SUBCASE("Testing shape") {
        CHECK(matrix.shape().rows == 5);
        CHECK(matrix.shape().cols == 5);
    }

    SUBCASE("Testing set and get") {
        matrix.set({2, 3}, 7);
        CHECK(matrix.get({2, 3}) == 7);
        CHECK(matrix.get({3, 2}) == 7); // Check symmetry
    }

    SUBCASE("Testing copy") {
        matrix.set({2, 3}, 7);
        auto window = Matrix_window{Matrix_index{1, 1}, Matrix_shape{3, 3}};
        auto copied_matrix = matrix.copy(window);
        CHECK(copied_matrix->get({1, 2}) == 7);
    }

    SUBCASE("Testing reshape") {
        matrix.reshape({3, 3});
        CHECK(matrix.shape().rows == 3);
        CHECK(matrix.shape().cols == 3);
    }
}