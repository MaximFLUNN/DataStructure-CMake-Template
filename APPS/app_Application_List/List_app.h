// Copyright 2022 Filatov Maxim

#include "../../LIBS/lib_list/List.h"

void printer(CList<int> l) {
	int size = l.size();
	for (int i = 0; i < size; i++) {
		std::cout << "(" << l[i]->get_data() << ")";
		if (i + 1 < size) {
			std::cout << "->";
		}
	}
}

void test() {
	CList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	l.reverse();
	/*l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.insert(4, 1);
	l.push_front(10);
	l.insert(7, 4);*/
	printer(l);
}