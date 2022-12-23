// Copyright 2022 Filatov Maxim

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#define MAX_VECTOR_SIZE 100000000
#define MAX_MATRIX_SIZE 10000

#include <iostream>
#include <algorithm>
#include <utility>

#pragma region TDynamicVector

template<typename T>
class TDynamicVector {
protected:
    size_t sz;
    T* pMem;

    void border_check() {
        sz <= 0 ? 
            throw std::out_of_range("Vector size should be greater than zero") : 
        sz > MAX_VECTOR_SIZE ? 
            throw std::out_of_range("Vector size must be less than 100000000") : NULL;
    }
public:
    explicit TDynamicVector(int size = 1) : sz(size) {
        border_check();
        /*if (sz <= 0) {
            throw std::out_of_range("Vector size should be greater than zero");
        }*/
        pMem = new T[sz]();
    }

    explicit TDynamicVector(T* arr, int s) : sz(s) {
        border_check();
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    explicit TDynamicVector(const TDynamicVector& v) {
    }

    explicit TDynamicVector(TDynamicVector&& v) noexcept {
    }

    ~TDynamicVector() {
    }

    TDynamicVector& operator=(const TDynamicVector& v) {
        if (this == &v) {
            return *this;
        }
        this->equating(v);
        return *this;
    }

    void allocate_new_memory(int size) {
        delete[] pMem;              // release resource in *this
        pMem = nullptr;
        sz = 0;                     // preserve invariants in case next line throws
        pMem = new T[size]; // allocate resource in *this
        sz = size;
    }

    void equating(const TDynamicVector& v, bool enable_auto_resize = true) {
        if (sz != v.sz && enable_auto_resize) {
            allocate_new_memory(v.sz);
        }
        int size = sz <= v.sz ? sz : v.sz;
        for (int i = 0; i < size; i++) {
            pMem[i] = v.pMem[i];
        }
    }

    void resize(int size) {
        if (size < 0) {
            throw std::logic_error("Size < 0");
        }
        TDynamicVector temp;
        temp.equating(*this);
        *this = TDynamicVector(size);
        this->equating(temp, false);
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept {
        delete[] pMem;
        pMem = nullptr;
        sz = 0;
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // indexing

    T& operator[](size_t ind) {
        return pMem[ind];
    }

    const T& operator[](size_t ind) const {
        return pMem[ind];
    }

    // indexing with control

    T& at(size_t ind) {
        if (ind >= sz) {
            throw std::out_of_range("Многа слишком атата");
        }
        return pMem[ind];
    }

    const T& at(size_t ind) const {
        if (ind >= sz) {
            throw std::out_of_range("Многа слишком атата");
        }
        return pMem[ind];
    }

    // comparisons

    bool operator==(const TDynamicVector& v) const noexcept {
        int size = v.sz;
        if (sz != v.sz) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept {
        return !(*this == v);
    }

    // scalar operations

    TDynamicVector operator+(T val) {
    }

    TDynamicVector operator-(double val) {
    }

    TDynamicVector operator*(double val) {
    }

    // vector operations

    TDynamicVector operator+(const TDynamicVector& v) {
    }

    TDynamicVector operator-(const TDynamicVector& v) {
    }

    T operator*(const TDynamicVector& v) noexcept(noexcept(T())) {
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // input / output


    friend std::istream& operator>>(std::istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};

#pragma endregion

#pragma region TDynamicMatrix

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
private:
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;

    void border_check();

public:
    explicit TDynamicMatrix(size_t s = 1);

    TDynamicMatrix(const TDynamicMatrix& other);

    TDynamicMatrix& operator=(const TDynamicMatrix<T>& m);

    void allocate_new_memory(int size);

    void equating(const TDynamicMatrix& v, bool enable_auto_resize = true);

    void resize(int size);

    /*TDynamicMatrix& operator=(TDynamicMatrix&& v) noexcept {
        delete[] pMem;
        pMem = nullptr;     
        sz = 0;
        swap(*this, v);
        return &*this;
    }*/
    using TDynamicVector<TDynamicVector<T>>::operator=;
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;

    // comparison

    bool operator==(const TDynamicMatrix& m) const noexcept;

    bool operator!=(const TDynamicMatrix& m) const noexcept {
        return !(*this == m);
    }

    size_t size() const noexcept;

    // matrix-scalar operations

    TDynamicVector<T> operator*(const T& val) {
        // TODO
    }

    // matrix-vector operations

    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        // TODO
    }

    // matrix-matrix operations

    TDynamicMatrix operator+(const TDynamicMatrix& m);

    TDynamicMatrix operator+=(const TDynamicMatrix& m) {
        *this = *this + m;
        return *this;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m) {
        if (sz != m.sz) {
            throw std::logic_error("Sizes not equal");
        }
        TDynamicMatrix tmp(sz);
        TDynamicMatrix t;
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                tmp[i][j] = (*this)[i][j] - m[i][j];
            }
        }
        return tmp;
    }

    TDynamicMatrix operator-=(const TDynamicMatrix& m) {
        *this = *this - m;
        return *this;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) {
        // TODO
    }

    // input / output

    friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v) {
        // TODO
    }

    /*friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v) {
    * // TODO
    }*/
};

#pragma endregion

#endif  // LIB_MATRIX_MATRIX_H_

template<typename T>
void TDynamicMatrix<T>::border_check() {
    sz <= 0 ?
        throw std::out_of_range("Matrix size should be greater than zero") :
        sz > MAX_MATRIX_SIZE ?
        throw std::out_of_range("Matrix size must be less than 10000") : NULL;
}

template<typename T>
TDynamicMatrix<T>::TDynamicMatrix(size_t s) : TDynamicVector<TDynamicVector<T>>(s) {
    border_check();
    for (size_t i = 0; i < sz; i++) {
        pMem[i] = TDynamicVector<T>(sz);
    }
}

template<typename T>
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicMatrix& other) {
    pMem = other.pMem;
    sz = other.sz;
}

template<typename T>
TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicMatrix<T>& m) {
    if (this == &m) {
        return *this;
    }
    this->equating(m);
    return *this;
}

template<typename T>
void TDynamicMatrix<T>::allocate_new_memory(int size) {
    delete[] pMem;              // release resource in *this
    pMem = nullptr;
    sz = 0;                     // preserve invariants in case next line throws
    pMem = new TDynamicVector<T>[size]; // allocate resource in *this
    sz = size;
}

template<typename T>
void TDynamicMatrix<T>::equating(const TDynamicMatrix<T>& v, bool enable_auto_resize) {
    if (sz != v.sz && enable_auto_resize) {
        allocate_new_memory(v.sz);
    }
    int size = sz <= v.sz ? sz : v.sz;
    for (int i = 0; i < size; i++) {
        pMem[i] = v.pMem[i];
    }
}

template<typename T>
void TDynamicMatrix<T>::resize(int size) {
    if (size < 0) {
        throw std::logic_error("Size < 0");
    }
    TDynamicMatrix temp;
    temp.equating(*this);
    *this = TDynamicMatrix(size);
    this->equating(temp, false);
    for (int i = 0; i < sz; i++) {
        pMem[i].resize(size);
    }
}

template<typename T>
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix& m) const noexcept {
    int size = sz;
    if (size != m.sz) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (pMem[i] != m.pMem[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
size_t TDynamicMatrix<T>::size() const noexcept {
    return sz; 
}

template<typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix& m) {
    if (sz != m.sz) {
        throw std::logic_error("Sizes not equal");
    }
    TDynamicMatrix tmp(sz);
    TDynamicMatrix t;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            tmp[i][j] = (*this)[i][j] + m[i][j];
        }
    }
    return tmp;
}