// Copyright 2022 Filatov Maxim

#include <gtest/gtest.h>
#include "../../LIBS/lib_Stack_on_list/Stack_on_list.h"

TEST(Stack_on_list_tests, can_create) {
	ASSERT_NO_THROW(Stack_on_list<int> s);
}

TEST(Stack_on_list_tests, can_create_with_size) {
	ASSERT_NO_THROW(Stack_on_list<int> s(5));
}

TEST(Stack_on_list_tests, correctyly_create_with_size) {
	Stack_on_list<int> s(5);
	EXPECT_EQ(s.get_size(), 5);
}

TEST(Stack_on_list_tests, can_real_size) {
	Stack_on_list<int> s(5);
	ASSERT_NO_THROW(s.get_real_size());
}

TEST(Stack_on_list_tests, correctyly_real_size) {
	Stack_on_list<int> s(5);
	EXPECT_EQ(s.get_real_size(), 0);
}

TEST(Stack_on_list_tests, can_top) {
	Stack_on_list<int> s(5);
	s.push(1);
	ASSERT_NO_THROW(s.top());
}

TEST(Stack_on_list_tests, correctyly_top) {
	Stack_on_list<int> s(5);
	s.push(1);
	EXPECT_EQ(s.top(), 1);
}

TEST(Stack_on_list_tests, can_push) {
	Stack_on_list<int> s(5);
	ASSERT_NO_THROW(s.push(1));
}

TEST(Stack_on_list_tests, correctyly_push) {
	Stack_on_list<int> s(5);
	s.push(1);
	EXPECT_EQ(s.top(), 1);
}


TEST(Stack_on_list_tests, can_full) {
	Stack_on_list<int> s(1);
	s.push(1);
	ASSERT_NO_THROW(s.isFull());
}

TEST(Stack_on_list_tests, correctyly_full) {
	Stack_on_list<int> s(1);
	s.push(1);
	EXPECT_EQ(s.isFull(), true);
}

TEST(Stack_on_list_tests, can_empty) {
	Stack_on_list<int> s(1);
	ASSERT_NO_THROW(s.isEmpty());
}

TEST(Stack_on_list_tests, correctyly_empty) {
	Stack_on_list<int> s(1);
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(Stack_on_list_tests, can_brackets) {
	Stack_on_list<int> s(5);
	s.push(1);
	s.push(2);
	s.push(1);
	ASSERT_NO_THROW(s[0]);
}

TEST(Stack_on_list_tests, correctyly_brackets) {
	Stack_on_list<int> s(5);
	s.push(1);
	s.push(2);
	s.push(1);
	EXPECT_EQ(s[1], 2);
}
