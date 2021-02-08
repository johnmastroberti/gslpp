#pragma once
#include <gsl/gsl_vector.h>
#include <utility>

namespace gsl {

  // {{{ Iterators
  template<typename T>
  concept pointer_type = std::is_pointer_v<T>;

  template<typename T, typename U>
  concept comparable_pointers = pointer_type<T>
      && pointer_type<U>
      && std::is_same_v<std::remove_cv_t<T>, std::remove_cv_t<U>>;

  template<typename T>
  struct reference_type {};

  template<typename T>
  struct reference_type<T*> {
    typedef T& type;
  };

  template<typename T>
  struct reference_type<const T*> {
    typedef const T& type;
  };

  template<pointer_type T>
  class VectorIteratorImpl {
    private:
      T m_pos;
      std::size_t m_stride;

    public:
      VectorIteratorImpl() : VectorIteratorImpl{nullptr, 0} {}
      VectorIteratorImpl(T p, std::size_t stride=1)
        : m_pos{p}, m_stride{stride} {}

      // VectorIterator& operator++();
      // VectorIterator operator++(int);
      // VectorIterator& operator--();
      // VectorIterator operator--(int);
      // {{{ Increment/Decrement
      VectorIteratorImpl<T> operator++() {
        m_pos += m_stride;
        return *this;
      }
      VectorIteratorImpl<T> operator++(int) {
        auto tmp = *this;
        m_pos += m_stride;
        return tmp;
      }
      VectorIteratorImpl<T> operator--() {
        m_pos -= m_stride;
        return *this;
      }
      VectorIteratorImpl<T> operator--(int) {
        auto tmp = *this;
        m_pos -= m_stride;
        return tmp;
      }
      // }}}

      // {{{ Iterator + int, Iterator - Iterator
      VectorIteratorImpl<T> operator+(int diff) const {
        return VectorIteratorImpl<T>{m_pos + diff*m_stride, m_stride};
      }
      VectorIteratorImpl<T>& operator+=(int diff) {
        m_pos += diff*m_stride;
      }
      VectorIteratorImpl<T> operator-(int diff) const {
        return VectorIteratorImpl<T>{m_pos - diff*m_stride, m_stride};
      }
      VectorIteratorImpl<T>& operator-=(int diff) {
        m_pos -= diff*m_stride;
      }

      template<typename U> requires comparable_pointers<T, U>
      int operator-(const VectorIteratorImpl<U>& o) const {
        return m_pos - o.m_pos;
      }

      // }}}

      // {{{ Comparison and dereference

      template<typename U> requires comparable_pointers<T, U>
      bool operator==(const VectorIteratorImpl<U>& o) const {
        return m_pos == o.m_pos;
      }
      reference_type<T>::type operator*() {
        return *m_pos;
      }
      const reference_type<T>::type operator*() const {
        return *m_pos;
      }
      // }}}
  };

  // }}}

  using VectorIterator = VectorIteratorImpl<double*>;
  using ConstVectorIterator = VectorIteratorImpl<const double*>;

  class Vector {
    private:
      gsl_vector* m_vec;

    public:
      // Special member functions
      Vector();
      Vector(std::size_t len);
      Vector(std::size_t len, double x);
      Vector(std::initializer_list<double> init);

      Vector(const Vector&);
      Vector& operator=(const Vector&);
      Vector(Vector&&);
      Vector& operator=(Vector&&);
      ~Vector();

      // Iterators
      VectorIterator begin();
      ConstVectorIterator begin() const;
      ConstVectorIterator cbegin() const;
      VectorIterator end();
      ConstVectorIterator end() const;
      ConstVectorIterator cend() const;

      // Utilities
      void set_all(double x);
      void set_zero();
      void set_basis(std::size_t i);

      std::size_t size() const;
      double& operator[](std::size_t i);
      const double& operator[](std::size_t i) const;

      int swap_elements(std::size_t i, std::size_t j);
      int reverse();

      double max() const;
      double min() const;
      std::pair<double, double> minmax() const;
      std::size_t max_index() const;
      std::size_t min_index() const;
      std::pair<std::size_t, std::size_t> minmax_index() const;

      bool isnull() const;
      bool ispos() const;
      bool isneg() const;
      bool isnonneg() const;

      // Arithmetic
      bool operator==(const Vector& o) const;
      Vector& operator+=(const Vector& o);
      Vector& operator-=(const Vector& o);
      Vector& operator*=(const Vector& o);
      Vector& operator/=(const Vector& o);

      Vector& operator+=(double x);
      Vector& operator*=(double x);

      Vector& axpby(const Vector& x, double a, double b);

      Vector operator+(const Vector& o) const;
      Vector operator-(const Vector& o) const;
      Vector operator*(const Vector& o) const;
      Vector operator/(const Vector& o) const;

      Vector operator+(double x) const;
      Vector operator*(double x) const;
  };
}
