// Copyright 2022 Filatov Maxim

#include "../../LIBS/lib_Stack_on_list/Stack_on_list.h"

void printer(Stack_on_list<int> l) {
	int size = l.get_real_size();
	for (int i = 0; i < size; i++) {
		std::cout << "(" << l[i] << ")";
		if (i + 1 < size) {
			std::cout << "\n---\n";
		}
	}
}

void test() {
	Stack_on_list<int> l;
	l.push(1);
	l.push(2);
	l.push(3);
	l.push(10);
	l.pop();
	l.push(6);
	printer(l);
}