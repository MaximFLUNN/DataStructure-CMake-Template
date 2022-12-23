// Copyright 2022 Filatov Maxim

//

#include <gtest/gtest.h>
#include "../../LIBS/lib_Matrix/matrix.h"

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) {
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) {
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) { // (Как задумывалось) был size_t неопределённое поведение!
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix) {
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) {
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(1);
	EXPECT_NE(m, n);
	n = TDynamicMatrix<int>(m);
	EXPECT_EQ(m, n);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) {
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(1);
	EXPECT_NE(m, n);
	n = TDynamicMatrix<int>(m);
	EXPECT_EQ(m, n);
}

TEST(TDynamicMatrix, can_get_size) { // (Как задумывалось) есть тест только на возможность вызова но не на правльность
	ASSERT_NO_THROW(TDynamicMatrix<int> (5).size());
}

TEST(TDynamicMatrix, can_set_and_get_element) {  // (Как задумывалось) проверка только на возможность вызова но не на правильность
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m[0][0]);
	ASSERT_NO_THROW(m[0][1] = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) { // (Как задумывалось) нет проверки на гет 
	ASSERT_ANY_THROW(TDynamicMatrix<int> (5).at(-1).at(1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) {
	ASSERT_ANY_THROW(TDynamicMatrix<int>(5).at(5).at(1) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself) {
	TDynamicMatrix<int> m(5);
	m = m;
	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) { // (Как задумывалось) нет проверки на корректность
	ASSERT_NO_THROW(TDynamicMatrix<int> (1) = TDynamicMatrix<int>(2));
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) { // (Как задумывалось) нет проверки на корректность
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(m.size(), 5);
	m.resize(4);
	EXPECT_EQ(m.size(), 4);
	EXPECT_EQ(m[0].size(), 4);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size) {
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(1);
	EXPECT_NE(m, n);
	n = m;
	EXPECT_EQ(m, n);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true) {
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(5);
	EXPECT_EQ(m, n);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) {
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) {
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(4);
	EXPECT_NE(m, n);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size) { // (Как задумывалось) нет проверки на корректность
	TDynamicMatrix<int> m(5);
	m[0][0] = 1;
	TDynamicMatrix<int> n(5);
	ASSERT_NO_THROW(m + n);
	n = n + m;
	EXPECT_EQ(n[0][0], 1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) { 
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(4);
	ASSERT_ANY_THROW(m + n);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) { // (Как задумывалось) нет проверки на корректность
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(5);
	ASSERT_NO_THROW(m + n);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) {
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(4);
	ASSERT_ANY_THROW(m + n);
}
