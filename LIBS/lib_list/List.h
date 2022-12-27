// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

#include <iostream>
#include <ostream>
template <class T> class CNode;
template <class T> class CList;



template <class T>
class CList {
	friend class CNode<T>;
private:
	CNode<T>* head;
	CNode<T>* tail;
public:
	CList() : head(nullptr), tail(nullptr) {}

	~CList() {}

	size_t size() {
		if (head == nullptr) {
			return 0;
		}
		int size = 0;
		CNode<T>* tmp = head;
		for (; tmp != NULL && tmp != nullptr; tmp = tmp->get_next_node()) { ++size; }
		return size;
	}

	void push_back(T value) {
		CNode<T>* new_node = new CNode<T>(value);
		if (!isEmpty()) {
			tail->next = new_node;
			tail = new_node;
		}
		else {
			head = new_node;
			tail = new_node;
		}
	}

	void push_front(T value) {
		CNode<T>* new_node = new CNode<T>(value);
		CNode<T>* tmp = head;
		if (!isEmpty()) {
			head = new_node;
			head->next = tmp;
		}
		else {
			head = new_node;
			tail = new_node;
		}
	}

	void pop_back() {
		if (head == tail) { throw std::logic_error("Head = tail"); }
		else if (isEmpty()) { throw std::logic_error("List is empty"); }
		CNode<T>* tmp = (*this)[size() - 2];
		tmp->del_next();
		tail = tmp;
	}

	void clearHeadAndTail() {
		delete head;
		delete tail;
		head = nullptr;
		tail = nullptr;
	}

	void pop_front() {
		if (head != tail) {
			CNode<T>* tmp = head;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
		else {
			clearHeadAndTail();
		}
	}

	CNode<T>* front() {
		return head;
	}

	CNode<T>* back() {
		return tail;
	}

	void insert(T _data, int index) {
		if (index < 0) {
			throw std::out_of_range("out of range");
		}
		if (index == 0) { 
			push_front(_data); 
			return;
		}
		if (index == size() - 1) { 
			push_back(_data);
			return;
		}
		if (index >= size() - 1) {
			throw std::out_of_range("out of range");
		}
		CNode<T>* tmp = new CNode<T>(_data);
		CNode<T>* post = (*this)[index];
		CNode<T>* pre = (*this)[index - 1];
		pre->set_next(tmp);
		tmp->set_next(post);
	}

	void erase(int index) {
		if (index < 0) {
			throw std::out_of_range("out of range");
		}
		if (index == 0) { 
			pop_back();
			return;
		}
		if (index == size() - 1) { 
			pop_back();
			return;
		}
		if (index >= size() - 1) {
			throw std::out_of_range("out of range");
		}
		CNode<T>* del_elem = (*this)[index];
		CNode<T>* pre = (*this)[index - 1];
		CNode<T>* post = (*this)[index + 1];
		pre->set_next(post);
		delete del_elem;
		del_elem = nullptr;
	}

	CNode<T>* operator[] (int index) {
		CNode<T>* tmp = head;
		int tmp_index = 0;
		for (; tmp_index < index; tmp = tmp->get_next_node()) { 
			++tmp_index;
		}
		return tmp;
	}

	bool isEmpty() {
		return head == nullptr;
	}
};

template <class T>
class CNode {
	friend class CList<T>;
private:
	T data;
	CNode<T>* next;
public:
	CNode(T value) {
		data = value;
		next = nullptr;
	}

	~CNode() {}

	void set_next(CNode<T>* next_node) {
		next = next_node;
	}

	CNode<T>* get_next_node() {
		return next;
	}

	void set_data(T _data) {
		data = _data;
	}

	T get_data() {
		return data;
	}

	void print() {
		std::cout << data;
	}

	void del_next() {
		delete next;
		next = nullptr;
	}

	void operator = (CNode<T>* node) {
		data = node->get_data();
		next = node->get_next_node();
	}

};

#endif  // INCLUDE_LIST_H_
