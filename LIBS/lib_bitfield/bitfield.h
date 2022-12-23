// Copyrught 2022 Filatov Maxim
#ifndef INCLUDE_BITFIELD_H_
#define INCLUDE_BITFIELD_H_

#include <iostream>

using elem_type = unsigned int;

class TBitField {
private:
//public: // временно для отладки
    size_t  bitLen;                      // длина битового поля (максимальное допустимое значение эл-та мн-ва, универс)
    size_t  memLen;                      // кол-во элементов, необходимое для хранения битового поля
    elem_type* pMem;                     // память для представления битового поля

    // служебные поля
    size_t bitsInElem = std::numeric_limits<elem_type>::digits;
    size_t shiftSize = std::bit_width(bitsInElem - 1);

    // служебные методы
    size_t GetMemIndex(size_t pos) const noexcept;

    elem_type GetMemMask(size_t pos) const noexcept;

    bool CheckCorrectlyBitPosition(int bitPos) const noexcept;

public:
    // обязательный классический функционал
    TBitField();
    TBitField(int _BitLen);                         // конструктор специального вида
    TBitField(const TBitField& bf);                      // конструктор копирования
    TBitField(TBitField&& bf) noexcept;                  // move-конструктор (перемещение содержимого bf в this)
    ~TBitField();                                        // деструктор
    TBitField& operator=(const TBitField& bf);
    TBitField& operator=(TBitField&& bf) noexcept;

    size_t size() const noexcept;      // получить длину (к-во битов)

    bool operator==(const TBitField& bf) const noexcept;
    bool operator!=(const TBitField& bf) const noexcept;

    bool getbit(int i) const;                           // получить значение бита i
    void setbit(int i);                                  // установить бит i
    void resetbit(int i);                                // очистить бит i

    TBitField  operator|(const TBitField& bf);           // или
    TBitField  operator&(const TBitField& bf);           // и
    TBitField  operator~(void);                          // отрицание


    
    friend void swap(TBitField& lhs, TBitField& rhs) noexcept {
        std::swap(lhs.bitLen, rhs.bitLen);
        std::swap(lhs.memLen, rhs.memLen);
        std::swap(lhs.pMem, rhs.pMem);
    }
    
    friend std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) { // вывод
        size_t len = bf.size();
        ostr << "{ ";
        for (size_t i = 0; i < len; i++) { 
            ostr << (i > 0 && i < len ? ", " : "") << (bf.getbit(i) ? 1 : 0);
        }
        ostr << " }";
        return ostr;
    }
};

TBitField CreateTBitField(const TBitField buff) noexcept;

#endif  // INCLUDE_BITFIELD_H_