// Copyright 2022 Filatov Maxim
#ifndef INCLUDE_SET_H_
#define INCLUDE_SET_H_

#include <iostream>
#include "../lib_bitfield/bitfield.h"

class TSet {
private:
	size_t maxPower;                       // максимальная мощность множества
	TBitField bitField;                    // битовое поле для хранения характеристического вектора

	bool ChechCorrectlyIndex(int index);

public:
	TSet(int mp);
	TSet(const TSet& s);                   // конструктор копирования
	operator TBitField();                  // преобразование типа к битовому полю

	size_t GetMaxPower(void) const noexcept;

	void InsElem(int Elem);            // включить элемент в множество
	void DelElem(int Elem);            // удалить элемент из множества
	bool IsMember(int Elem) const;     // проверить наличие элемента в множестве

	TSet operator+ (const int Elem);       // объединение с элементом
	TSet operator- (const int Elem);       // разность с элементом
	TSet operator+ (const TSet& s);        // объединение
	TSet operator* (const TSet& s);        // пересечение
	TSet operator~ (void);                 // дополнение

	int operator== (const TSet& s) const;
	int operator!= (const TSet& s) const;
	TSet& operator=(const TSet& s);

	friend std::istream& operator>>(std::istream& in, TSet& bf) {
		std::string inpt;
		int n = bf.GetMaxPower();
		for (int i = 0; i < n; i++)
		{
			std::cout << i << " The element is included in the set?" << std::endl;
			in >> inpt;
			if (inpt == "+") {
				bf.InsElem(i);
			}
			else if (inpt == "-") {
				bf.DelElem(i);
			}
			else {
				throw ("You can only answer: '+' or  '-'");
			}
			std::cout << std::endl;
		}
	}
	friend std::ostream& operator<<(std::ostream& out, const TSet& bf) {
		size_t size = bf.GetMaxPower();
		std::string ch = "{ ";
		for (size_t i = 0; i < size; i++) {
			if (bf.IsMember(i)) {
				out << ch << i;
				ch = ", ";
			}
		}
		out << " }";
		return out;
	}
};

#endif  // INCLUDE_SET_H_