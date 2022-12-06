// Copyright 2022 Filatov Maxim

#pragma region Инклуды

#include "bitfield.h"

#pragma endregion

#pragma region Служебные методы

size_t TBitField::GetMemIndex(size_t pos) const noexcept {        // индекс в pМем для бита pos
    return pos >> shiftSize;
}

elem_type TBitField::GetMemMask(size_t pos) const noexcept {      // битовая маска для бита pos
    return 1 << (pos & (bitsInElem - 1));
}

bool TBitField::CheckCorrectlyBitPosition(int bitPos) const noexcept {
    return ((bitPos > -1) && (bitPos < bitLen));
}

#pragma endregion

#pragma region Конструкторы

/// <summary>
/// Конструктор по умолчанию
/// </summary>
TBitField::TBitField() {
    bitLen = 1;
    memLen = ceil(static_cast<float>(1) / static_cast<float>(bitsInElem));
    pMem = new elem_type[memLen];
    memset(pMem, 0, memLen * sizeof(elem_type)); // заполняем нулями
}

/// <summary>
/// Конструктор копирования
/// </summary>
/// <param name="Размер"></param>
TBitField::TBitField(int _BitLen) { // изначально передавался size_t изменил на int чтобы была возможность отловить исключение иначе не предсказуемое поведение
    if (_BitLen < 1) {
        throw std::length_error("Bit length <= 0");
    }
    bitLen = _BitLen;
    memLen = ceil(static_cast<float>(_BitLen) / static_cast<float>(bitsInElem));
    pMem = new elem_type[memLen];
    memset(pMem, 0, memLen * sizeof(elem_type));
} 

/// <summary>
/// Конструктор копирования
/// </summary>
/// <param name="Битовое поле"></param>
TBitField::TBitField(const TBitField& bf) {
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new elem_type[bf.memLen];
    memcpy(pMem, bf.pMem, bf.memLen * sizeof(elem_type));
}

/// <summary>
/// Move конструктор
/// </summary>
/// <param name="Битовое поле"></param>
TBitField::TBitField(TBitField&& bf) noexcept
    : pMem(nullptr), bitLen(0), memLen(0) {
    swap(*this, bf);
}

/// <summary>
/// Деструктор
/// </summary>
TBitField::~TBitField() {
    delete[] pMem;
}

#pragma endregion

#pragma region Присвоение

/// <summary>
/// Операция приравнивания
/// </summary>
/// <param name="Битовое поле"></param>
/// <returns>Битовое поле со значениями переданного</returns>
TBitField& TBitField::operator=(const TBitField& bf) {
    if (this != &bf) {
        TBitField tmp(bf);
        swap(*this, tmp);
    }
    return *this;
}

/// <summary>
/// Операция приравнивания (move)
/// </summary>
/// <param name="Битовое поле"></param>
/// <returns>Битовое поле со значениями переданного</returns>
TBitField& TBitField::operator=(TBitField&& bf) noexcept {
    if (this != &bf) {
        swap(*this, bf);
    }
    return *this;
}

#pragma endregion

#pragma region Сравнение

/// <summary>
/// Операция равно
/// </summary>
/// <param name="Битовое поле"></param>
/// <returns>Результат сравнения (true/false)</returns>
bool TBitField::operator==(const TBitField& bf) const noexcept {
    if (bitLen != bf.bitLen) {
        return false;
    }
    else {
        for (size_t i = 0; i < memLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return false;
            }
        }
    }
}

/// <summary>
/// Операция не равно
/// </summary>
/// <param name="Битовое поле"></param>
/// <returns>Результат сравнения (true/false)</returns>
bool TBitField::operator!=(const TBitField& bf) const noexcept {
    return !(*this == bf);
}
#pragma endregion

#pragma region Методы взаимодействия с битами

/// <summary>
/// Получение значения бита
/// </summary>
/// <param name="Позиция бита"></param>
/// <returns>Значение бита (true/false)</returns>
/// <exception cref="Ошибка размера">description</exception>
bool TBitField::getbit(int i) const { // size_t заменён на int так как при передаче отрицательного числа ожидается неопределённое поведение 
    return CheckCorrectlyBitPosition(i) ? pMem[GetMemIndex(i)] & GetMemMask(i) : throw std::out_of_range("Invalid bit position!");
}

/// <summary>
/// Установка биту значения 1
/// </summary>
/// <param name="Позиция бита"></param>
/// <exception cref="Ошибка размера">description</exception>
void TBitField::setbit(int i) { // size_t заменён на int так как при передаче отрицательного числа ожидается неопределённое поведение
    CheckCorrectlyBitPosition(i) ? pMem[GetMemIndex(i)] |= GetMemMask(i) : throw std::out_of_range("Invalid bit position!");
}

/// <summary>
/// Установка биту значения 0
/// </summary>
/// <param name="Позиция бита"></param>
/// <exception cref="Ошибка размера">description</exception>
void TBitField::resetbit(int i) { // size_t заменён на int так как при передаче отрицательного числа ожидается неопределённое поведение
    CheckCorrectlyBitPosition(i) ? pMem[GetMemIndex(i)] &= ~GetMemMask(i) : throw std::out_of_range("Invalid bit position!");
}

/// <summary>
/// Применение размера
/// </summary>
/// <returns>Размер size_t()</returns>
size_t TBitField::size() const noexcept { // получить длину (к-во битов)
    return bitLen;
}

#pragma endregion

#pragma region Битовые операции

/// <summary>
/// Применение битового ИЛИ к битовым полям
/// </summary>
/// <param name="Битовое поле"></param>
/// <returns>Битовое поле с результатом применения битового ИЛИ</returns>
TBitField  TBitField::operator|(const TBitField& bf) {
    TBitField tmp(*this);
    int sizeMemLen = memLen < bf.memLen ? memLen : bf.memLen;
    for (size_t i = 0; i < sizeMemLen; i++) {
        tmp.pMem[i] |= bf.pMem[i]; // битовая операция ИЛИ с присвоением левому числу (a |= b) => (a = a | b)
    }
    return tmp;
}

/// <summary>
/// Применение битового И к битовым полям
/// </summary>
/// <param name="Битовое поле"></param>
/// <returns>Битовое поле с результатом применения битового И</returns>
TBitField  TBitField::operator&(const TBitField& bf) {
    TBitField tmp(*this);
    int sizeMemLen = memLen < bf.memLen ? memLen : bf.memLen;
    for (int i = 0; i < sizeMemLen; i++) {
        tmp.pMem[i] &= bf.pMem[i]; // битовая операция И с присвоением левому числу (a &= b) => (a = a & b)
    }
    return tmp;
}

/// <summary>
/// Отрицание битового поля
/// </summary>
/// <returns>Инверсию битового поля</returns>
TBitField  TBitField::operator~(void) {
    TBitField tmp(bitLen);
    for (int i = 0; i < bitLen; i++) {
        if (getbit(i) == 0) {
            tmp.setbit(i);
        }
        else {
            tmp.resetbit(i);
        }
    }
    return tmp;
}

#pragma endregion

#pragma region Создание поля функцией для использования move
/// <summary>
/// Создание поля (move)
/// </summary>
/// <returns>TBitFiled (move)</returns>
TBitField CreateTBitField(const TBitField buff) noexcept {
    TBitField retbuff(buff);
    return retbuff;
}

#pragma endregion
