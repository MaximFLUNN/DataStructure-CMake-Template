// Copyright 2022 Filatov Maxim
#include "../../LIBS/lib_set/set.h"
#include <gtest/gtest.h>

#pragma region TEST_constructor

TEST(TSet_constructor_tests, constructor_initialization_can) {
	ASSERT_NO_THROW(TSet a = TSet(10));
	ASSERT_NO_THROW(TSet a = TSet(100));
	ASSERT_NO_THROW(TSet a = TSet(1000));
}

TEST(TSet_constructor_tests, constructor_initialization_cant_with_invalid_value) {
	ASSERT_ANY_THROW(TSet a = TSet(-1));
	ASSERT_ANY_THROW(TSet a = TSet(0));
}

TEST(TSet_constructor_tests, constructor_initialization_correcttly) {
	TSet a = TSet(3);
	a.InsElem(1);
	EXPECT_EQ(a.IsMember(1), true);
}

#pragma endregion

#pragma region TEST_methods

TEST(TSet_methods_tests, method_getMaxPower_can) {
	ASSERT_NO_THROW(TSet(3).GetMaxPower());
}

TEST(TSet_methods_tests, method_getMaxPower_correctly) {
	TSet a = TSet(3);
	EXPECT_EQ(a.GetMaxPower(), 3);
}

TEST(TSet_methods_tests, method_IsMember_can) {
	ASSERT_NO_THROW(TSet(3).IsMember(1));
}

TEST(TSet_methods_tests, method_IsMember_correctly) {
	TSet a = TSet(3);
	EXPECT_EQ(a.IsMember(0), false);
	a.InsElem(0);
	EXPECT_EQ(a.IsMember(0), true);
}

TEST(TSet_methods_tests, method_InsElem_can) {
	ASSERT_NO_THROW(TSet(3).InsElem(1));
}

TEST(TSet_methods_tests, method_InsElem_correctly) {
	TSet a = TSet(3);
	EXPECT_EQ(a.IsMember(1), false);
	a.InsElem(1);
	EXPECT_EQ(a.IsMember(1), true);
}

TEST(TSet_methods_tests, method_InsElem_cant_with_invalid_value) {
	ASSERT_ANY_THROW(TSet(3).InsElem(-1));
}

TEST(TSet_methods_tests, method_DelElem_can) {
	ASSERT_NO_THROW(TSet(3).DelElem(0));
}

TEST(TSet_methods_tests, method_DelElem_correctly) {
	TSet a = TSet(3);
	EXPECT_EQ(a.IsMember(0), false);
	a.InsElem(0);
	EXPECT_EQ(a.IsMember(0), true);
	a.DelElem(0);
	EXPECT_EQ(a.IsMember(0), false);
}

#pragma endregion

#pragma region TEST_operators

TEST(TSet_operators_tests, method__plus__can) {
	ASSERT_NO_THROW(TSet(3) + 1);
}

TEST(TSet_operators_tests, method__plus__correctly) {
	TSet a = TSet(3);
	EXPECT_EQ(a.IsMember(1), false);
	a = a + 1;
	EXPECT_EQ(a.IsMember(1), true);
}

TEST(TSet_operators_tests, method__plus__cant_with_invalid_value) {
	ASSERT_ANY_THROW(TSet(3) + 100);
}

TEST(TSet_operators_tests, method__minus__can) {
	ASSERT_NO_THROW(TSet(3) - 1);
}

TEST(TSet_operators_tests, method__minus__correctly) {
	TSet a = TSet(3);
	EXPECT_EQ(a.IsMember(1), false);
	a = a + 1;
	EXPECT_EQ(a.IsMember(1), true);
	a = a - 1;
	EXPECT_EQ(a.IsMember(1), false);
}

TEST(TSet_operators_tests, method__minus__cant_with_invalid_value) {
	ASSERT_ANY_THROW(TSet(3) - 100);
}

TEST(TSet_operators_tests, method__plus_set__can) {
	ASSERT_NO_THROW(TSet(3) + TSet(3));
}

TEST(TSet_operators_tests, method__plus_set__correctly) {
	TSet a = TSet(3);
	TSet b = TSet(3);
	EXPECT_EQ(a.IsMember(0), false);
	EXPECT_EQ(b.IsMember(2), false);
	a = a + 0;
	b = b + 2;
	EXPECT_EQ(a.IsMember(0), true);
	EXPECT_EQ(b.IsMember(2), true);
	a = a + b;
	EXPECT_EQ(a.IsMember(0), true);
	EXPECT_EQ(a.IsMember(1), false);
	EXPECT_EQ(a.IsMember(2), true);
}

TEST(TSet_operators_tests, method__cross_set__can) {
	ASSERT_NO_THROW(TSet(3) * TSet(3));
}

TEST(TSet_operators_tests, method__cross_set__correctly) {
	TSet a = TSet(3);
	TSet b = TSet(3);
	TSet c = TSet(5);
	EXPECT_EQ(a.IsMember(0), false);
	EXPECT_EQ(a.IsMember(1), false);
	EXPECT_EQ(b.IsMember(2), false);
	EXPECT_EQ(b.IsMember(1), false);
	a = a + 0;
	a = a + 1;
	b = b + 2;
	b = b + 1;
	EXPECT_EQ(a.IsMember(0), true);
	EXPECT_EQ(a.IsMember(1), true);
	EXPECT_EQ(b.IsMember(2), true);
	EXPECT_EQ(b.IsMember(1), true);
	a = a * b;
	EXPECT_EQ(a.IsMember(0), false);
	EXPECT_EQ(a.IsMember(1), true);
	EXPECT_EQ(a.IsMember(2), false);
	EXPECT_EQ(c.IsMember(1), false);
	c.InsElem(1);
	EXPECT_EQ(c.IsMember(1), true);
	a = a * c;
	EXPECT_EQ(a.IsMember(0), false);
	EXPECT_EQ(a.IsMember(1), true);
	EXPECT_EQ(a.IsMember(2), false);

}

TEST(TSet_operators_tests, method_invers_can) {
	ASSERT_NO_THROW(TSet(3));
}

TEST(TSet_operators_tests, method_invers_correctly) {
	TSet a = TSet(1);
	EXPECT_EQ(a.IsMember(0), false);
	a = ~a;
	EXPECT_EQ(a.IsMember(0), true);
}

TEST(TSet_operators_tests, method_functor_can) {
	ASSERT_NO_THROW(TSet(3).operator TBitField());
}

TEST(TSet_operators_tests, method_functor_correctly) {
	TSet a = TSet(3);
	a.InsElem(1);
	TBitField b = a.operator TBitField();
	EXPECT_EQ(b.getbit(0), false);
	EXPECT_EQ(b.getbit(1), true);
	EXPECT_EQ(b.getbit(2), false);
}

TEST(TSet_operators_tests, method_equals_can) {
	ASSERT_NO_THROW(TSet(3) = TSet(4));
}

TEST(TSet_operators_tests, method_equals_correctly) {
	TSet a = TSet(1);
	TSet b = TSet(3);
	EXPECT_EQ(a.GetMaxPower(), 1);
	EXPECT_EQ(b.GetMaxPower(), 3);
	a = b;
	EXPECT_EQ(a.GetMaxPower(), 3);
	EXPECT_EQ(b.GetMaxPower(), 3);
} 

#pragma endregion

#pragma region TEST_comparison

TEST(TSet_comparison_tests, method_equals_can) {
	ASSERT_NO_THROW(TSet(3) == TSet(5));
}

TEST(TSet_comparison_tests, method_equals_correctly) {
	TSet a = TSet(3);
	TSet b = TSet(3);
	a = a + 1;
	EXPECT_EQ(a == b, false);
	b = b + 1;
	EXPECT_EQ(a == b, true);
}

TEST(TSet_comparison_tests, method_not_equals_can) {
	ASSERT_NO_THROW(TSet(3) != TSet(5));
}

TEST(TSet_comparison_tests, method_not_equals_correctly) {
	TSet a = TSet(3);
	TSet b = TSet(3);
	a = a + 1;
	EXPECT_EQ(a != b, true);
	b = b + 1;
	EXPECT_EQ(a != b, false);
}

#pragma endregion
