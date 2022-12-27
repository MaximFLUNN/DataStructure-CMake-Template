// Copyright 2022 Filatov Maxim

#include "../../LIBS/lib_Queue_on_list_erase/Queue_on_list_erase.h"

void printer(TQueue_erase<int> l) {
	int size = l.get_real_size();
	for (int i = 0; i < size; i++) {
		std::cout << "(" << l[i].get_data().first << ")";
		if (i + 1 < size) {
			std::cout << "<-";
		}
	}
}

void test() {
	TQueue_erase<int> t(5);
	t.push({1, 1});
	t.push({2, 2});
	t.push({5, 5}); 
	t.push({4, 4});
	t.push({3, 3});
	printer(t);
	std::cout << " | push\n\n";
	t.pop();
	printer(t);
	std::cout << " | pop\n\n";
	t.pop();
	printer(t);
	std::cout << " | pop2\n\n";
}