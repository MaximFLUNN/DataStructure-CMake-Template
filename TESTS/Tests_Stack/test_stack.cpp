// Copyright 2022 Filatov Maxim

#include <gtest/gtest.h>
#include "../../LIBS/lib_Stack/Stack.h"
#include "../../APPS/app_Application_Stack/app.h"


TEST(Stack_Tests, can_create_stack) {
	ASSERT_NO_THROW(Stack<int> s1(10));
}

TEST(Stack_Tests, cant_create_stack_then_size_negative) {
	ASSERT_ANY_THROW(Stack<int> s1(-20));
}

TEST(Stack_Tests, can_push_in_stack) {
	Stack<int> s1(5);
	ASSERT_NO_THROW(s1.push(7));
}

TEST(Stack_Tests, cant_push_in_stack_but_stack_is_full) {
	Stack<int> s(1);
	s.push(1);
	ASSERT_ANY_THROW(s.push(2));
}

TEST(Stack_Tests, can_correctly_push_in_stack) {
	Stack<int> s(5);
	s.push(8);
	EXPECT_EQ(s.check(), 8);
}

TEST(Stack_Tests, can_pop_in_stack) {
	Stack<int> s(5);
	s.push(1);
	ASSERT_NO_THROW(s.pop());
}

TEST(Stack_Tests, correctly_pop_in_stack) {
	Stack<int> s(5);
	s.push(1);
	int a = s.pop();
	EXPECT_EQ(a, 1);
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(Stack_Tests, differient_link_data_test) {
	Stack<int> s1(5);
	Stack<int> s2(5);
	s1.push(1);
	s2.push(2);
	s1 = s2;
	s2.pop();
	EXPECT_EQ(s1.check(), 2);
}

TEST(Stack_Brackets_tests, five_brackets_solve_correctly) {
	Stack a = Stack<char>(5);
	a.push('(');
	a.push('{');
	a.push('(');
	a.push(')');
	a.push('}');
	EXPECT_EQ(solve(a, false), false);
}

TEST(Stack_Brackets_tests, four_brackets_solve_correctly) {
	Stack a = Stack<char>(5);
	a.push('(');
	a.push('{');
	a.push('}');
	a.push(')');
	EXPECT_EQ(solve(a, false), true);
}

TEST(Stack_Brackets_tests, no_open_start_brackets_solve_correctly) {
	Stack a = Stack<char>(5);
	a.push(']');
	a.push('{');
	a.push('}');
	EXPECT_EQ(solve(a, false), false);
}