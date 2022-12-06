// Copyright 2022 Filatov Maxim

#pragma region »нклуды

#include "set.h"

#pragma endregion

#pragma region  онструкторы

TSet::TSet(int mp) : maxPower(mp), bitField(mp) {};

TSet::TSet(const TSet& s) : maxPower(s.maxPower), bitField(s.bitField) {};

#pragma endregion

#pragma region ћетоды

bool TSet::ChechCorrectlyIndex(int index) {
	return (index <= maxPower && index > -1);
}

size_t TSet::GetMaxPower(void) const noexcept { 
	return maxPower; 
}

void TSet::InsElem(int Elem) { // size_t заменено на int дл€ улавливани€ отрицательного значени€ и предотвращени€ неопределЄнного поведени€
	ChechCorrectlyIndex(Elem) ? bitField.setbit(Elem) : throw std::length_error("Invalid index");
}

void TSet::DelElem(int Elem) { // size_t заменено на int дл€ улавливани€ отрицательного значени€ и предотвращени€ неопределЄнного поведени€
	ChechCorrectlyIndex(Elem) ? bitField.resetbit(Elem) : throw std::length_error("Invalid index");
}

bool TSet::IsMember(int Elem) const { // size_t заменено на int дл€ улавливани€ отрицательного значени€ и предотвращени€ неопределЄнного поведени€
	return bitField.getbit(Elem);
}

#pragma endregion

#pragma region ќператоры множества

TSet TSet::operator+ (const int Elem) {
	InsElem(Elem);
	return *this;
}

TSet TSet::operator- (const int Elem) {
	DelElem(Elem);
	return *this;
}

TSet TSet::operator+ (const TSet& s) {
	if (maxPower >= s.maxPower) {
		bitField = bitField | s.bitField;
		return *this;
	}
	else {
		TSet tmp = TSet(s);
		tmp.bitField = bitField | s.bitField;
		return tmp;
	}
}

TSet TSet::operator* (const TSet& s) {
	if (maxPower >= s.maxPower) {
		bitField = bitField & s.bitField;
		return *this;
	}
	else {
		TSet tmp = TSet(s);
		tmp.bitField = bitField & s.bitField;
		return tmp;
	}
}

TSet TSet::operator~ (void) {
	bitField = ~bitField;
	return *this;
}

TSet::operator TBitField() { 
	return TBitField(bitField); 
}

TSet& TSet::operator=(const TSet& s) {
	if (this != &s) {
		maxPower = s.maxPower;
		bitField = s.bitField;
	}
	return *this;
}

int TSet::operator== (const TSet& s) const {
	return bitField == s.bitField;
}

int TSet::operator!= (const TSet& s) const {
	return !(*this == s);
}

#pragma endregion

