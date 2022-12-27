// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_QUEUE_ON_LIST_H_
#define INCLUDE_QUEUE_ON_LIST_H_

#include <iostream>
#include <ostream>
#include "../../LIBS/lib_list/List.h"

template <class T> class Stack;

template <class T>
class TQueue_on_list {
private:
	int size;
	CList<T> data;
public:
	TQueue_on_list() { data = CList<T>(); }
	TQueue_on_list(int _size) {
		data = CList<T>();
		_size < 1 ? throw std::string("Negative value") : NULL;
		size = _size;
	}
	void push(T value) {
		if (isFull()) { throw std::string("Queue is full"); }
		data.push_back(value);
	}
	int get_size() { return size; }
	int get_real_size() { return data.size(); }
	void pop() { if (!isEmpty()) { data.pop_front(); } }
	CNode<T> operator [] (int index) { return *data[index]; }
	T front() { return data.front()->get_data(); }
	T back() { return data.back()->get_data(); }
	bool isFull() { return data.size() >= size; }
	bool isEmpty() { return data.size() == 0; }
};

#endif  // INCLUDE_STACK_ON_LIST_H_
