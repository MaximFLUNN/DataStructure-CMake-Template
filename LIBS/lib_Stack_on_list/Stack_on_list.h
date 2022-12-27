// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_STACK_ON_LIST_H_
#define INCLUDE_STACK_ON_LIST_H_

#include <iostream>
#include <ostream>
#include <vector>
#include "../../LIBS/lib_list/List.h"

template <class T> class Stack_on_list;

template <class T>
class Stack_on_list {
	int size;
	CList<T> data;
public:
	Stack_on_list() { data = CList<T>(); }

	Stack_on_list(int _size) {
		_size < 1 ? throw std::string("Negative value") : NULL;
		data = CList<T>();
		size = _size;
	}

	Stack_on_list(const Stack_on_list<T>& other) : data(other.data), size(other.size) {}

	int get_size() { return size; }

	int get_real_size() { return data.size(); }

	void push(T value) {
		isFull() ? throw std::string("Stack is full") : NULL;
		data.push_back(value);
	}

	void push(std::vector<T> arr) {
		for (auto& elem : arr) {
			this->push(elem);
		}
	}

	T top() {
		isEmpty() ? throw std::string("Stack is empty") : NULL;
		return data.back()->get_data();
	}

	void pop() {
		return isEmpty() ? throw std::string("Stack is empty") : data.pop_back();
	}

	bool isFull() {
		return data.size() >= size;
	}

	bool isEmpty() {
		return data.size() == 0;
	}

	T operator [] (int index) {
		return (*data[index]).get_data();
	}
};

#endif  // INCLUDE_STACK_ON_LIST_H_
