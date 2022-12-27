// Copyright 2022 Filatov Maxim

#include "../../LIBS/lib_Stack/Stack.h"

bool solve(Stack<char> a, bool error) {
	if (error) {
		a.print();
	}
	bool solved = false;
	try {
		solved = a.force_solve(error);
		if (error) {
			std::cout << color(gray_dark) << "\nSolved: " << color(green) << (solved ? "true" : "false") << color() << "\n" << std::endl;
		}
	}
	catch (const std::exception& e) {
		if (error) {
			std::cout << color(gray_dark) << "\nSolved: " << color(red) << "false \n" << color(yellow) << e.what() << std::endl;
		}
	}
	return solved;
}

void color_print(Stack<char> a, int index) {
	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(blue_dark).print("-------------------------\n");
	std::cout << color(blue) << "Test stack '" << index << "': ";
	solve(a, true);
}

void test() {
	Stack<Stack<char>> main(7);
	Stack a = Stack<char>(50);
	Stack b = Stack<char>(7);
	Stack c = Stack<char>(9);
	Stack d = Stack<char>(10);
	Stack e = Stack<char>(4);
	Stack f = Stack<char>(2);
	Stack g = Stack<char>(2);

	a.push({ '(', '{', '(', ')', '}' });
	b.push({ '(', '{', '(', ')', '}', ')' });
	c.push({ '(', '{', '[', ']', '}', ')', '(', ')' });
	d.push({ '(', '{', '[', ']', '}', ')', '(', ')', ')', ')' });
	e.push({ '[', ']', ']', ')' });
	f.push({ '}', ')' });
	g.push({ '[', ')' });

	main.push({g, f, e, d, c, b, a});

	int index = 1;
	while (!main.isEmpty()) { color_print(main.pop(), index++); }
	std::cout << color(blue_dark).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
}
