// Copyright 2022 Filatov Maxim

#include "../../LIBS/lib_Queue_on_list/Queue_on_list.h"

void printer(TQueue_on_list<int> l) {
	int size = l.get_real_size();
	for (int i = 0; i < size; i++) {
		std::cout << "(" << l[i].get_data() << ")";
		if (i + 1 < size) {
			std::cout << "<-";
		}
	}
}

void test() {
	TQueue_on_list<int> t(5);
	t.push(1);
	t.push(2);
	t.push(3);
	t.push(4);
	t.push(5);
	t.pop();
	t.push(2);
	printer(t);
}