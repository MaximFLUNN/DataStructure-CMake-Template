// Copyright 2022 Filatov Maxim

#include "../../LIBS/lib_Queue_on_list_insert/Queue_on_list_insert.h"

void printer(TQueue_insert<int> l) {
	int size = l.get_real_size();
	for (int i = 0; i < size; i++) {
		std::cout << "(" << l[i].get_data().first << ")";
		if (i + 1 < size) {
			std::cout << "<-";
		}
	}
}

void test() {
	TQueue_insert<int> t(10);
	t.push({ 1, 1 });
	t.push({ 2, 1 }); 
	t.push({ 3, 1 });
	t.push({ 4, 2 });
	t.push({ 5, 3 });
	//t.pop();
	t.push({ 2, 1 });
	t.push({ 9, 9 });
	t.push({ 9, 8 });
	t.push({ 6, 2 });
	printer(t);
	std::cout << " | fisrt\n";
	TQueue_insert<int> a(10);
	a.push({ 2, 2 });
	a.push({ 1, 1 });
	a.push({ 9, 9 });
	a.push({ 7, 7 });
	a.push({ 3, 3 });
	a.push({ 5, 5 });
	a.push({ 6, 6 });
	a.push({ 8, 8 });
	a.push({ 4, 4 });
	printer(a);
	std::cout << " | second";
}
