// Copyright 2022 Filatov Maxim
#include "../../LIBS/lib_bitfield/bitfield.h"
#include <gtest/gtest.h>

#pragma region TEST_constructors

TEST(tbitfield_constructor_tests, constructor_default_can) {
	ASSERT_NO_THROW(TBitField());
}

TEST(tbitfield_constructor_tests, constructor_initialize_can_positive_value) {
	ASSERT_NO_THROW(TBitField(10));
	ASSERT_NO_THROW(TBitField(100));
	ASSERT_NO_THROW(TBitField(1000));
}

TEST(tbitfield_constructor_tests, constructor_initialize_correctly_positive_value) {
	EXPECT_EQ(TBitField(1).size(), 1);
	EXPECT_EQ(TBitField(5).size(), 5);
	EXPECT_EQ(TBitField(10).size(), 10);;
}

TEST(tbitfield_constructor_tests, constructor_initialize_cant_negetive_value_and_NULL_value) {
	ASSERT_ANY_THROW(TBitField(-10000));
	ASSERT_ANY_THROW(TBitField(-5000));
	ASSERT_ANY_THROW(TBitField(0x0));
}

TEST(tbitfield_constructor_tests, constructor_copy_can) {
	ASSERT_NO_THROW(TBitField a = TBitField(3));
}

TEST(tbitfield_constructor_tests, constructor_copy_correctly) {
	if (sizeof(elem_type) == sizeof(unsigned char)) { // более глубокая проверка для unsigned char
		TBitField a = TBitField(3);
		a.setbit(1);
		TBitField b = TBitField(a);
		EXPECT_EQ(b.getbit(0), 0);
		EXPECT_EQ(b.getbit(1), 1);
		EXPECT_EQ(b.getbit(2), 0);
	}
	else { // обычная проверка
		TBitField a = TBitField(1);
		a.setbit(0);
		TBitField b = TBitField(a);
		EXPECT_EQ(b.getbit(0), 1);
	}
}

TEST(tbitfield_constructor_tests, constructor_move_appropriation_can) {
	TBitField a = CreateTBitField(TBitField(1));	// срабатывает конструктор перемещения
}

TEST(tbitfield_constructor_tests, constructor_move_appropriation_correctly) {
	if (sizeof(elem_type) == sizeof(unsigned char)) { // более глубокая проверка для unsigned char
		TBitField a = CreateTBitField(TBitField(3));
		TBitField b = CreateTBitField(TBitField(5));
		a.setbit(1);
		b = a;
		EXPECT_EQ(b.size(), 3);
		EXPECT_EQ(b.getbit(0), 0);
		EXPECT_EQ(b.getbit(1), 1);
		EXPECT_EQ(b.getbit(2), 0);
	}
	else { // обычная проверка
		TBitField a = CreateTBitField(TBitField(1));
		TBitField b = CreateTBitField(TBitField(10000));
		a.setbit(0);
		b = a;
		EXPECT_EQ(b.size(), 1);
		EXPECT_EQ(b.getbit(0), 1);
	}
}

#pragma endregion

#pragma region TEST_methods

TEST(tbitfield_methods_tests, method_size_can_return_value) {
	ASSERT_NO_THROW(TBitField(10).size());
	ASSERT_NO_THROW(TBitField(100).size());
	ASSERT_NO_THROW(TBitField(1000).size());
}

TEST(tbitfield_methods_tests, method_size_correctly_return_value) {
	EXPECT_EQ(TBitField(1).size(), 1);
	EXPECT_EQ(TBitField(5).size(), 5);
	EXPECT_EQ(TBitField(10).size(), 10);
}

TEST(tbitfield_methods_tests, method_getbit_can) {
	TBitField a = TBitField(1);
	ASSERT_NO_THROW(a.getbit(0));
}

TEST(tbitfield_methods_tests, method_getbit_correctly) {
	TBitField a = TBitField(1);
	EXPECT_EQ(a.getbit(0), 0);
	a.setbit(0);
	EXPECT_EQ(a.getbit(0), 1);
}

TEST(tbitfield_methods_tests, method_getbit_cant_by_invalid_value) {
	TBitField a = TBitField(1);
	ASSERT_ANY_THROW(a.getbit(-1));
	ASSERT_ANY_THROW(a.getbit(1));
	ASSERT_ANY_THROW(a.getbit(2));
}

TEST(tbitfield_methods_tests, method_setbit_can) {
	ASSERT_NO_THROW(TBitField(1).setbit(0));
}

TEST(tbitfield_methods_tests, method_setbit_correctly) {
	if (sizeof(elem_type) == sizeof(unsigned char)) { // более глубокая проверка для unsigned char
		TBitField a = TBitField(2);
		a.setbit(0);
		EXPECT_EQ(a.getbit(0), 1);
		EXPECT_EQ(a.getbit(1), 0);
	}
	else { // обычная проверка
		TBitField a = TBitField(1);
		a.setbit(0);
		EXPECT_EQ(a.getbit(0), 1);
	}
}

TEST(tbitfield_methods_tests, method_setbit_cant_by_invalid_value) {
	ASSERT_ANY_THROW(TBitField(1).setbit(-1));
	ASSERT_ANY_THROW(TBitField(1).setbit(1));
	ASSERT_ANY_THROW(TBitField(1).setbit(2));
}

TEST(tbitfield_methods_tests, method_resetbit_can) {
	ASSERT_NO_THROW(TBitField(1).resetbit(0));
}

TEST(tbitfield_methods_tests, method_resetbit_correctly) {
	if (sizeof(elem_type) == sizeof(unsigned char)) { // более глубокая проверка для unsigned char
		TBitField a = TBitField(2);
		a.setbit(0);
		a.setbit(1);
		a.resetbit(0);
		EXPECT_EQ(a.getbit(0), 0);
		EXPECT_EQ(a.getbit(1), 1);
	}
	else { // обычная проверка 
		TBitField a = TBitField(1);
		a.setbit(0);
		a.resetbit(0);
		EXPECT_EQ(a.getbit(0), 0);
	}
}

TEST(tbitfield_methods_tests, method_resetbit_cant_by_invalid_value) {
	ASSERT_ANY_THROW(TBitField(1).resetbit(-1));
	ASSERT_ANY_THROW(TBitField(1).resetbit(1));
	ASSERT_ANY_THROW(TBitField(1).resetbit(2));
}

#pragma endregion

#pragma region TEST_appropriation

TEST(tbitfield_appropriation_tests, appropriation_can) {
	TBitField a = TBitField(5);
	TBitField b = TBitField(3);
	ASSERT_NO_THROW(a = b);
}

TEST(tbitfield_appropriation_tests, appropriation_correctly) {
	if (sizeof(elem_type) == sizeof(unsigned char)) { // более глубокая проверка для unsigned char
		TBitField a = TBitField(5);
		TBitField b = TBitField(3);
		b.setbit(1);
		a = b;
		EXPECT_EQ(a.size(), 3);
		EXPECT_EQ(a.getbit(0), 0);
		EXPECT_EQ(a.getbit(1), 1);
		EXPECT_EQ(a.getbit(2), 0);
	}
	else { // обычная проверка
		TBitField a = TBitField(55555555);
		TBitField b = TBitField(1);
		b.setbit(0);
		a = b;
		EXPECT_EQ(a.size(), 1);
		EXPECT_EQ(a.getbit(0), 1);
	}
}

TEST(tbitfield_appropriation_tests, move_appropriation_can) {
	TBitField a = CreateTBitField(TBitField(1));	// срабатывает конструктор перемещения
	TBitField b = a;								// срабатывает конструктор копирования
	b = CreateTBitField(TBitField(1));				// срабатывает конструктор перемещения, затем оператор перемещения
	b = a;											// срабатывает оператор присваивания
}

TEST(tbitfield_appropriation_tests, move_appropriation_correctly) {
	if (sizeof(elem_type) == sizeof(unsigned char)) { // более глубокая проверка для unsigned char
		TBitField a = CreateTBitField(TBitField(3));
		TBitField b = CreateTBitField(TBitField(5));
		a.setbit(1);
		b = a;
		EXPECT_EQ(b.size(), 3);
		EXPECT_EQ(b.getbit(0), 0);
		EXPECT_EQ(b.getbit(1), 1);
		EXPECT_EQ(b.getbit(2), 0);
	}
	else { // обычная проверка
		TBitField a = CreateTBitField(TBitField(1));
		TBitField b = CreateTBitField(TBitField(555555555));
		a.setbit(0);
		b = a;
		EXPECT_EQ(b.size(), 1);
		EXPECT_EQ(b.getbit(0), 1);
	}
}

#pragma endregion

#pragma region TEST_comparison

TEST(tbitfield_comparison_tests, comparison_can_eq) {
	ASSERT_NO_THROW(TBitField(3) == TBitField(3));
}

TEST(tbitfield_comparison_tests, comparison_correctly_eq) {
	TBitField a = TBitField(3);
	TBitField b = TBitField(3);
	EXPECT_EQ(TBitField(3) == TBitField(5), false);
	EXPECT_EQ(TBitField(3) == TBitField(3), true);
	a.setbit(1);
	EXPECT_EQ(a == b, false);
	b.setbit(1);
	EXPECT_EQ(a == b, true);
}

TEST(tbitfield_comparison_tests, comparison_can_not_eq) {
	ASSERT_NO_THROW(TBitField(3) != TBitField(3));
}

TEST(tbitfield_comparison_tests, comparison_correctly_not_eq) {
	TBitField a = TBitField(3);
	TBitField b = TBitField(3);
	EXPECT_EQ(TBitField(3) != TBitField(5), true);
	EXPECT_EQ(TBitField(3) != TBitField(3), false);
	a.setbit(1);
	EXPECT_EQ(a != b, true);
	b.setbit(1);
	EXPECT_EQ(a != b, false);
}

#pragma endregion

#pragma region TEST_bit_operations

TEST(tbitfield_bit_operations_tests, bit_operation__OR__can) {
	ASSERT_NO_THROW(TBitField(3) | TBitField(3));
}

TEST(tbitfield_bit_operations_tests, bit_operation__OR__correctly) {
	TBitField a = TBitField(3);
	TBitField b = TBitField(3);
	a.setbit(2);
	TBitField c = a | b;
	EXPECT_EQ(c.getbit(0), 0);
	EXPECT_EQ(c.getbit(1), 0);
	EXPECT_EQ(c.getbit(2), 1);
}

TEST(tbitfield_bit_operations_tests, bit_operation__AND__can) {
	ASSERT_NO_THROW(TBitField(3) & TBitField(3));
}

TEST(tbitfield_bit_operations_tests, bit_operation__AND__correctly) {
	TBitField a = TBitField(3);
	TBitField b = TBitField(3);
	b.setbit(2);
	a.setbit(0);
	a.setbit(1);
	a.setbit(2);
	TBitField c = a & b;
	EXPECT_EQ(c.getbit(0), 0);
	EXPECT_EQ(c.getbit(1), 0);
	EXPECT_EQ(c.getbit(2), 1);
}

TEST(tbitfield_bit_operations_tests, bit_operation__inversion__can) {
	ASSERT_NO_THROW(~TBitField(3));
}

TEST(tbitfield_bit_operations_tests, bit_operation__inversion__correctly) {
	if (sizeof(elem_type) == sizeof(unsigned char)) { // более глубокая проверка для unsigned char
		TBitField a = TBitField(3);
		a.setbit(1);
		a = ~a;
		EXPECT_EQ(a.getbit(0), 1);
		EXPECT_EQ(a.getbit(1), 0);
		EXPECT_EQ(a.getbit(2), 1);
	}
	else { // обычная проверка
		TBitField a = TBitField(1);
		a.setbit(0);
		a = ~a;
		EXPECT_EQ(a.getbit(0), 0);
	}
}

#pragma endregion
