// Copyright 2022 Filatov Maxim

#include <gtest/gtest.h>
#include "../../LIBS/lib_Queue_on_list_insert/Queue_on_list_insert.h"

TEST(Queue_on_list_tests, can_create) {
	ASSERT_NO_THROW(TQueue_insert<int> t);
}

TEST(Queue_on_list_tests, can_create_with_size) {
	ASSERT_NO_THROW(TQueue_insert<int> t(5));
}

TEST(Queue_on_list_tests, correctly_create_with_size) {
	TQueue_insert<int> t(5);
	EXPECT_EQ(t.get_size(), 5);
}

TEST(Queue_on_list_tests, can_real_size) {
	TQueue_insert<int> t(5);
	ASSERT_NO_THROW(t.get_real_size());
}

TEST(Queue_on_list_tests, correctly_real_size) {
	TQueue_insert<int> t(5);
	EXPECT_EQ(t.get_real_size(), 0);
}

TEST(Queue_on_list_tests, can_full) {
	TQueue_insert<int> t(5);
	ASSERT_NO_THROW(t.isFull());
}

TEST(Queue_on_list_tests, correctly_full) {
	TQueue_insert<int> t(1);
	t.push({ 1,1 });
	EXPECT_EQ(t.isFull(), true);
}

TEST(Queue_on_list_tests, can_push) {
	TQueue_insert<int> t(5);
	ASSERT_NO_THROW(t.push({1, 1}));
}

TEST(Queue_on_list_tests, correctly_push) {
	TQueue_insert<int> t(5);
	t.push({ 1,1 });
	t.push({ 7,7 });
	t.push({ 5,5 });
	EXPECT_EQ(t.front().first, 7);
}
