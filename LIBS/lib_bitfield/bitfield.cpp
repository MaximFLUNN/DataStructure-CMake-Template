// Copyright 2022 Filatov Maxim

#pragma region �������

#include "bitfield.h"

#pragma endregion

#pragma region ��������� ������

size_t TBitField::GetMemIndex(size_t pos) const noexcept {        // ������ � p��� ��� ���� pos
    return pos >> shiftSize;
}

elem_type TBitField::GetMemMask(size_t pos) const noexcept {      // ������� ����� ��� ���� pos
    return 1 << (pos & (bitsInElem - 1));
}

bool TBitField::CheckCorrectlyBitPosition(int bitPos) const noexcept {
    return ((bitPos > -1) && (bitPos < bitLen));
}

#pragma endregion

#pragma region ������������

/// <summary>
/// ����������� �� ���������
/// </summary>
TBitField::TBitField() {
    bitLen = 1;
    memLen = ceil(static_cast<float>(1) / static_cast<float>(bitsInElem));
    pMem = new elem_type[memLen];
    memset(pMem, 0, memLen * sizeof(elem_type)); // ��������� ������
}

/// <summary>
/// ����������� �����������
/// </summary>
/// <param name="������"></param>
TBitField::TBitField(int _BitLen) { // ���������� ����������� size_t ������� �� int ����� ���� ����������� �������� ���������� ����� �� ������������� ���������
    if (_BitLen < 1) {
        throw std::length_error("Bit length <= 0");
    }
    bitLen = _BitLen;
    memLen = ceil(static_cast<float>(_BitLen) / static_cast<float>(bitsInElem));
    pMem = new elem_type[memLen];
    memset(pMem, 0, memLen * sizeof(elem_type));
} 

/// <summary>
/// ����������� �����������
/// </summary>
/// <param name="������� ����"></param>
TBitField::TBitField(const TBitField& bf) {
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new elem_type[bf.memLen];
    memcpy(pMem, bf.pMem, bf.memLen * sizeof(elem_type));
}

/// <summary>
/// Move �����������
/// </summary>
/// <param name="������� ����"></param>
TBitField::TBitField(TBitField&& bf) noexcept
    : pMem(nullptr), bitLen(0), memLen(0) {
    swap(*this, bf);
}

/// <summary>
/// ����������
/// </summary>
TBitField::~TBitField() {
    delete[] pMem;
}

#pragma endregion

#pragma region ����������

/// <summary>
/// �������� �������������
/// </summary>
/// <param name="������� ����"></param>
/// <returns>������� ���� �� ���������� �����������</returns>
TBitField& TBitField::operator=(const TBitField& bf) {
    if (this != &bf) {
        TBitField tmp(bf);
        swap(*this, tmp);
    }
    return *this;
}

/// <summary>
/// �������� ������������� (move)
/// </summary>
/// <param name="������� ����"></param>
/// <returns>������� ���� �� ���������� �����������</returns>
TBitField& TBitField::operator=(TBitField&& bf) noexcept {
    if (this != &bf) {
        swap(*this, bf);
    }
    return *this;
}

#pragma endregion

#pragma region ���������

/// <summary>
/// �������� �����
/// </summary>
/// <param name="������� ����"></param>
/// <returns>��������� ��������� (true/false)</returns>
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
/// �������� �� �����
/// </summary>
/// <param name="������� ����"></param>
/// <returns>��������� ��������� (true/false)</returns>
bool TBitField::operator!=(const TBitField& bf) const noexcept {
    return !(*this == bf);
}
#pragma endregion

#pragma region ������ �������������� � ������

/// <summary>
/// ��������� �������� ����
/// </summary>
/// <param name="������� ����"></param>
/// <returns>�������� ���� (true/false)</returns>
/// <exception cref="������ �������">description</exception>
bool TBitField::getbit(int i) const { // size_t ������ �� int ��� ��� ��� �������� �������������� ����� ��������� ������������� ��������� 
    return CheckCorrectlyBitPosition(i) ? pMem[GetMemIndex(i)] & GetMemMask(i) : throw std::out_of_range("Invalid bit position!");
}

/// <summary>
/// ��������� ���� �������� 1
/// </summary>
/// <param name="������� ����"></param>
/// <exception cref="������ �������">description</exception>
void TBitField::setbit(int i) { // size_t ������ �� int ��� ��� ��� �������� �������������� ����� ��������� ������������� ���������
    CheckCorrectlyBitPosition(i) ? pMem[GetMemIndex(i)] |= GetMemMask(i) : throw std::out_of_range("Invalid bit position!");
}

/// <summary>
/// ��������� ���� �������� 0
/// </summary>
/// <param name="������� ����"></param>
/// <exception cref="������ �������">description</exception>
void TBitField::resetbit(int i) { // size_t ������ �� int ��� ��� ��� �������� �������������� ����� ��������� ������������� ���������
    CheckCorrectlyBitPosition(i) ? pMem[GetMemIndex(i)] &= ~GetMemMask(i) : throw std::out_of_range("Invalid bit position!");
}

/// <summary>
/// ���������� �������
/// </summary>
/// <returns>������ size_t()</returns>
size_t TBitField::size() const noexcept { // �������� ����� (�-�� �����)
    return bitLen;
}

#pragma endregion

#pragma region ������� ��������

/// <summary>
/// ���������� �������� ��� � ������� �����
/// </summary>
/// <param name="������� ����"></param>
/// <returns>������� ���� � ����������� ���������� �������� ���</returns>
TBitField  TBitField::operator|(const TBitField& bf) {
    TBitField tmp(*this);
    int sizeMemLen = memLen < bf.memLen ? memLen : bf.memLen;
    for (size_t i = 0; i < sizeMemLen; i++) {
        tmp.pMem[i] |= bf.pMem[i]; // ������� �������� ��� � ����������� ������ ����� (a |= b) => (a = a | b)
    }
    return tmp;
}

/// <summary>
/// ���������� �������� � � ������� �����
/// </summary>
/// <param name="������� ����"></param>
/// <returns>������� ���� � ����������� ���������� �������� �</returns>
TBitField  TBitField::operator&(const TBitField& bf) {
    TBitField tmp(*this);
    int sizeMemLen = memLen < bf.memLen ? memLen : bf.memLen;
    for (int i = 0; i < sizeMemLen; i++) {
        tmp.pMem[i] &= bf.pMem[i]; // ������� �������� � � ����������� ������ ����� (a &= b) => (a = a & b)
    }
    return tmp;
}

/// <summary>
/// ��������� �������� ����
/// </summary>
/// <returns>�������� �������� ����</returns>
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

#pragma region �������� ���� �������� ��� ������������� move
/// <summary>
/// �������� ���� (move)
/// </summary>
/// <returns>TBitFiled (move)</returns>
TBitField CreateTBitField(const TBitField buff) noexcept {
    TBitField retbuff(buff);
    return retbuff;
}

#pragma endregion
