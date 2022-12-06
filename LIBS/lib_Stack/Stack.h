// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <iostream>
#include <ostream>
#include "../lib_Menu/Color.h"

template <class T> class Stack;

template <class T>
class Stack {
	int size;
	T* data;
	int top;
 public:
	Stack() {
		data = new T[1];
		size = 1;
		top = -1;
	}

	Stack(int _size) {
		_size < 1 ? throw std::string("Negative value") : NULL;
		data = new T[_size];
		size = _size;
		top = -1;
	}

	// Копирование
	Stack(const Stack& other) : data(other.data), size(other.size), top(other.top) {}

	// Перемещение
	Stack(Stack&& other) noexcept {
		delete[] data;
		data = nullptr;
		size = 0;
		top = -1;
		swap(*this, other);
	}

	// Присваивавние
	void operator=(Stack& other) noexcept {
		this->data = new T[other.size];
		this->size = other.size;
		this->top = 0;
		while (this->top <= other.top) {
			this->push(other.data[this->top]);
		}
	}

	// Обмен
	void swap(Stack& first, Stack& second) {
		std::swap(first.data, second.data);
		std::swap(first.size, second.size);
		std::swap(first.top, second.top);
	}

	void push(T value) {
		isFull() ? throw std::string("Stack is full") : NULL;
		top++;
		data[top] = value;
	}

	T check() {
		isEmpty() ? throw std::string("Stack is empty") : NULL;
		return data[top];
	}

	T pop() {
		isEmpty() ? throw std::string("Stack is empty") : NULL;
		T tmp = data[top];
		data[top] = 0;
		top--;
		return tmp;
	}

	bool isFull() {
		return top == size - 1;
	}

	bool isEmpty() {
		return top == -1;
	}

	bool solve_brackets(bool error_graphic) {
		std::string tmp;
		int ss = 0;
		for (int i = 0; i < size; i++, ss++) {
			char t = data[i];
			if (t == '(' || t == '{' || t == '[' || t == ')' || t == '}' || t == ']') {
				continue;
			}
			else {
				break;
			}
		}
		ss < 1 ? throw std::logic_error("Error: brackets size < 1") : NULL;
		(ss & 1) != 1 ? NULL : throw std::logic_error("Error: size is not a multiple of two");
		char t = data[0];
		if (t == ')' || t == '}' || t == ']') {
			throw std::logic_error("Error: no open cerrectly bracket in start");
		}
		for (int i = 0; i < size; i++) {
			if (!tmp.empty()) {
				char t = tmp[tmp.length() - 1];
				if (t == '(' && data[i] == ')' || t == '{' && data[i] == '}' || t == '[' && data[i] == ']') {
					tmp.pop_back();
					continue;
				}
				else if (data[i] == ')' || data[i] == '}' || data[i] == ']') {
					error_graphic ? draw_error_graphic(i, false) : void();
					throw std::logic_error("Error: no open cerrectly bracket");
				}
			}
			tmp.push_back(data[i]);
		}
		return true;
	}

	void print() {
		int ss = 0;
		for (int i = 0; i < size; i++, ss++) {
			char t = data[i];
			if (t == '(' || t == '{' || t == '[' || t == ')' || t == '}' || t == ']') {
				continue;
			}
			else {
				break;
			}
		}
		std::cout << "\n" << color(azure);
		for (int i = 0; i < ss; i++) {
			std::cout << data[i];
		}
		std::cout << color();
	}
 private:
	 void draw_error_graphic(int pos, bool flag) {
		 flag ? print() : void();
		 std::cout << "\n" << (pos == 1 ? " " : "");
		 for (int i = 0; i < pos - 1; i++) {
			 std::cout << " ";
		 }
		 std::cout << color(red) << "^" << color(gray_dark) << " (no open cerrectly bracket)\n";
	}
};

#endif  // INCLUDE_STACK_H_
