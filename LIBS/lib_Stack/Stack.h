// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <iostream>
#include <ostream>
#include <vector>
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

	void set_data(int size) {
		this->data = new T[size];
	}

	void set_size(int value) {
		this->size = value;
	}

	void set_top(int value) {
		this->top = value;
	}

	int get_size() {
		return size;
	}

	// Копирование
	Stack(const Stack& other) : data(other.data), size(other.size), top(other.top) {}

	// Перемещение
	Stack(Stack&& other) noexcept {
		delete[] data;
		data = nullptr;
		set_size(0);
		set_top(-1);
		swap(*this, other);
	}

	// Присваивавние
	void operator=(Stack& other) {
		int s = other.get_size();
		this->set_data(s);
		this->set_size(s);
		this->set_top(-1);
		Stack<T> temp(s);
		while (!other.isEmpty()) {
			T element = other.pop();
			temp.push(element);
		}
		while (!temp.isEmpty()) {
			this->push(temp.check());
			other.push(temp.pop());
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

	void push(std::vector<T> arr) {
		for (auto &elem : arr) {
			this->push(elem);
		}
	}

	T check() {
		isEmpty() ? throw std::string("Stack is empty") : NULL;
		return data[top];
	}

	int get_top() {
		return top;
	}

	T pop() {
		return isEmpty() ? throw std::string("Stack is empty") : data[top--];
	}

	bool isFull() {
		return top == size - 1;
	}

	bool isEmpty() {
		return top == -1;
	}

	bool force_solve(bool error_graphic) {  
		Stack<T> temp(size);
		int index = 0;
		while (!this->isEmpty()) {
			T element = pop();
			if (element == '(' || element == '{' || element == '[') {
				if (!temp.isEmpty()) {
					T temp_element = temp.pop();
					if (element == '(' && temp_element == ')'
						|| element == '{' && temp_element == '}'
						|| element == '[' && temp_element == ']'
						) 
					{
						index++;
						continue;
					}
					else
					{
						error_graphic ? draw_error_graphic(index, true, "no closed cerrectly bracket") : void();
						throw std::logic_error("Error: no closed cerrectly bracket");
					}
				}
				else {
					error_graphic ? draw_error_graphic(index, true, "first bracket no close cerrectly") : void();
					throw std::logic_error("Error: first bracket no close cerrectly");
				}
			}
			else if (element == ')' || element == '}' || element == ']') {
				temp.push(element);
			}
			else {
				error_graphic ? draw_error_graphic(index, true, "finded unknown symbol") : void();
				throw std::logic_error("Error: finded unknown symbol");
			}
			index++;
		}
		if (!temp.isEmpty()) {
			throw std::logic_error("Error: left closed brackets");
		}
		return true;
	}

	 void print() {
		 Stack<T> temp(this->get_size());
		 while (!this->isEmpty()) { temp.push(this->pop()); }
		 std::cout << "\n" << color(azure);
		 while (!temp.isEmpty()) {
			 T element = temp.pop();
			 std::cout << element;
			 this->push(element);
		 }
		 std::cout << color();
	 }
 private:
	 void draw_error_graphic(int pos, bool flag, std::string error) {
		 std::cout << '\n';
		 int index = (this->get_top() - pos) - 1;
		 for (int i = 0; i < index; i++) { std::cout << " "; }
		 std::cout << color(red) << "^" << color(gray_dark) << " (" << error << ")\n";
	 }
};

#endif  // INCLUDE_STACK_H_
