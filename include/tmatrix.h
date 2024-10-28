// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw ("Vector size should be less than MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      pMem = new T[v.sz];
      if (pMem == nullptr)
          throw ("Error");
      else
      {
          sz = v.sz;
          for (int i = 0; i < sz; i++)
              pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) {
          return *this;
      }
      TDynamicVector res(v);
      swap(*this, res);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      delete[] pMem;
      pMem = nullptr;
      swap(*this, v);
      return (*this);
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz)
          throw ("Error");
      else
          return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
          throw ("Error");
      else
          return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz == v.sz)
      {
          for (size_t i = 0; i < sz; i++)
              if (pMem[i] != v.pMem[i])
                  return 0;
          return 1;
      }
      else return 0;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !((*this) == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + val;
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - val;
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector<T> res(*this);
          for (size_t i = 0; i < sz; i++)
          {
              res.pMem[i] += v.pMem[i];
          }
          return res;
      }
      else
      {
          throw ("Error");
      }
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector<T> res(*this);
          for (size_t i = 0; i < sz; i++)
          {
              res.pMem[i] -= v.pMem[i];
          }
          return res;
      }
      else
      {
          throw ("Error");
      }
  }
  T operator*(const TDynamicVector& v) 
  {
      if (sz == v.sz)
      {
          T res{};
          for (size_t i = 0; i < v.sz; i++)
          {
              res = res + (pMem[i] * v.pMem[i]);
          }
          return res;
      }
      else
      {
          throw ("Error");
      }
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw("Error");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz == m.sz)
      {
          for (size_t i = 0; i < sz; i++)
              if (pMem[i] != m.pMem[i])
                  return 0;
          return 1;
      }
      else return 0;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (pMem[0].size() == v.size())
      {
          TDynamicVector<T>  res(sz);
          for (size_t i = 0; i < sz; i++)
          {
              res[i] = pMem[i] * v;
          }
          return res;
      }
      else
          throw ("Error");
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.sz == sz)
      {
          TDynamicMatrix res(sz);
          for (size_t i = 0; i < sz; i++)
          {
              res.pMem[i] = pMem[i] + m.pMem[i];
          }
          return res;
      }
      else
          throw ("Error");
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.sz == sz)
      {
          TDynamicMatrix res(sz);
          for (size_t i = 0; i < sz; i++)
          {
              res.pMem[i] = pMem[i] - m.pMem[i];
          }
          return res;
      }
      else
          throw ("Error");
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (m.sz == sz)
      {
          TDynamicMatrix res(sz);
          size_t pMemsz0 = pMem[0].size();
          TDynamicVector<T> tmp(pMemsz0);
          for (size_t i = 0; i < sz; i++)
          {
              for (size_t j = 0; j < pMemsz0; j++)
              {
                  for (size_t k = 0; k < pMemsz0; k++)
                  {
                      tmp[k] = m.pMem[k][j];
                  }
                  res[i][j] += pMem[i] * tmp;
              }
          }
          return res;
      }
      else
          throw("Error");

  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      ostr << endl;
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << "\n";
      return ostr;
  }
};

#endif
