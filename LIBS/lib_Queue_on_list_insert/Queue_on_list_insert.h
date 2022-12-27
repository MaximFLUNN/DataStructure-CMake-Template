// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_QUEUE_ON_LIST_INSERT_H_
#define INCLUDE_QUEUE_ON_LIST_INSERT_H_

#include <iostream>
#include <ostream>
#include "../../LIBS/lib_Queue_on_list/Queue_on_list.h"

template <class T> class TQueue_on_list;

template <class T>
class TQueue_insert : public TQueue_on_list<std::pair<T, int>> {
private:
	int size;
	CList<std::pair<T, int>> data;
public:
	TQueue_insert() { data = CList<std::pair<T, int>>(); }
	TQueue_insert(int _size) {
		data = CList<std::pair<T, int>>();
		_size < 1 ? throw std::string("Negative value") : NULL;
		size = _size;
	}
	void push(std::pair<T, int> value) {
		if (isFull()) { throw std::string("Queue is full"); }
		int size = data.size();
		if (size == 0) {
			data.push_back(value);
			return;
		}
		CNode<std::pair<T, int>>* tmp = data.front();
		int index = 0;
		for (; tmp != NULL && tmp != nullptr; tmp = tmp->get_next_node()) {
			if (value.first >= tmp->get_data().first) {
				data.insert(value, index);
				return;
			}
			++index;
		}
		data.push_back(value);	
	}
	int get_size() { return size; }
	int get_real_size() { return data.size(); }
	void pop() { if (!isEmpty()) { data.pop_front(); } }
	CNode<std::pair<T, int>> operator [] (int index) { return *data[index]; }
	std::pair<T, int> front() { return data.front()->get_data(); }
	std::pair<T,int> back() { return data.back()->get_data(); }
	bool isFull() { return data.size() >= size; }
	bool isEmpty() { return data.size() == 0; }
};

#endif  // INCLUDE_STACK_ON_LIST_INESRT_H_
