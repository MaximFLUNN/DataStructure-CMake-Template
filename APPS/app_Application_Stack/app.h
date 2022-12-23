// Copyright 2022 Filatov Maxim

#include "../../LIBS/lib_Stack/Stack.h"

bool solve(Stack<char> a, bool print_solution) {
	if (print_solution) {
		a.print();
	}
	bool solved = false;
	try {
		solved = a.solve_brackets(true);
		if (print_solution) {
			std::cout << color(gray_dark) << "\nSolved: " << color(green) << (solved ? "true" : "false") << color() << "\n" << std::endl;
		}
	}
	catch (const std::exception& e) {
		if (print_solution) {
			std::cout << color(gray_dark) << "\nSolved: " << color(red) << "false \n" << color(yellow) << e.what() << std::endl;
		}
	}
	return solved;
}

void test() {
	Stack a = Stack<char>(5);
	Stack b = Stack<char>(7);
	Stack c = Stack<char>(9);
	Stack d = Stack<char>(10);
	Stack e = Stack<char>(4);
	Stack f = Stack<char>(2);
	Stack g = Stack<char>(2);

	a.push('(');
	a.push('{');
	a.push('(');
	a.push(')');
	a.push('}');

	b.push('(');
	b.push('{');
	b.push('(');
	b.push(')');
	b.push('}');
	b.push(')');

	c.push('(');
	c.push('{');
	c.push('[');
	c.push(']');
	c.push('}');
	c.push(')');
	c.push('(');
	c.push(')');

	d.push('(');
	d.push('{');
	d.push('[');
	d.push(']');
	d.push('}');
	d.push(')');
	d.push('(');
	d.push(')');
	d.push(')');
	d.push(')');

	e.push('[');
	e.push(']');
	e.push(']');
	e.push(')');

	f.push('}');
	f.push(')');
	
	g.push('[');
	g.push(')');

	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(blue).print("Test stack 'a': ");
	solve(a, true);
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(blue).print("Test stack 'b': ");
	solve(b, true);
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(blue).print("Test stack 'c': ");
	solve(c, true);
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(blue).print("Test stack 'd': ");
	solve(d, true);
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(blue).print("Test stack 'e': ");
	solve(e, true);
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(blue).print("Test stack 'f': ");
	solve(f, true);
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
	std::cout << color(white).print("-------------------------\n");
	std::cout << color(blue).print("Test stack 'g': ");
	solve(g, true);
	std::cout << color(blue_dark).print("-------------------------\n");
	std::cout << color(gray_dark).print("=========================\n");
}

