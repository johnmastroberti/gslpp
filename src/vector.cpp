#include "vector.hpp"
#include <cassert>
#include <algorithm>

namespace gsl {

  // {{{  Special member functions
  Vector::Vector() : Vector( 0 ) {}
  Vector::Vector(std::size_t n) : m_vec{gsl_vector_calloc(n)} {}
  Vector::Vector(std::size_t n, double x) : m_vec{gsl_vector_calloc(n)} {
    if (x != 0.0)
      set_all(x);
  }

  Vector::Vector(std::initializer_list<double> init) : Vector( init.size() ) {
    std::copy(init.begin(), init.end(), this->begin());
  }

  Vector::Vector(const Vector& o) : Vector( o.size() ) {
    gsl_vector_memcpy(m_vec, o.m_vec);
  }
  Vector& Vector::operator=(const Vector& o) {
    assert(this->size() != o.size()); // TODO: upgrade this
    gsl_vector_memcpy(m_vec, o.m_vec);
    return *this;
  }

  Vector::Vector(Vector&& o) : m_vec{o.m_vec} {
    o.m_vec = nullptr;
  }
  Vector& Vector::operator=(Vector&& o) {
    assert(this->size() != o.size()); // TODO: upgrade this
    gsl_vector_free(m_vec);
    m_vec = o.m_vec;
    o.m_vec = nullptr;
    return *this;
  }

  Vector::~Vector() {
    gsl_vector_free(m_vec);
  }

  // }}}

  // {{{ Iterators

  VectorIterator      Vector::begin() {
    return {m_vec->data, m_vec->stride};
  }
  ConstVectorIterator Vector::begin() const {
    return {m_vec->data, m_vec->stride};
  }
  ConstVectorIterator Vector::cbegin() const {
    return {m_vec->data, m_vec->stride};
  }
  VectorIterator      Vector::end() {
    return {m_vec->data + m_vec->size * m_vec->stride, 1};
  }
  ConstVectorIterator Vector::end() const {
    return {m_vec->data + m_vec->size * m_vec->stride, 1};
  }
  ConstVectorIterator Vector::cend() const {
    return {m_vec->data + m_vec->size * m_vec->stride, 1};
  }

  // }}}


  // {{{ Utilities
  void Vector::set_all(double x) {
    gsl_vector_set_all(m_vec, x);
  }

  void Vector::set_zero() {
    gsl_vector_set_zero(m_vec);
  }

  void Vector::set_basis(std::size_t i) {
    gsl_vector_set_basis(m_vec, i);
  }

  std::size_t Vector::size() const {
    return m_vec->size;
  }

  double& Vector::operator[](std::size_t i) {
    return *gsl_vector_ptr(m_vec, i);
  }

  const double& Vector::operator[](std::size_t i) const {
    return *gsl_vector_const_ptr(m_vec, i);
  }

  int Vector::swap_elements(std::size_t i, std::size_t j) {
    return gsl_vector_swap_elements(m_vec, i, j);
  }

  int Vector::reverse() {
    return gsl_vector_reverse(m_vec);
  }

  double Vector::max() const {
    return gsl_vector_max(m_vec);
  }

  double Vector::min() const {
    return gsl_vector_min(m_vec);
  }

  std::pair<double, double> Vector::minmax() const {
    std::pair<double, double> ans;
    gsl_vector_minmax(m_vec, &ans.first, &ans.second);
    return ans;
  }

  std::size_t Vector::max_index() const {
    return gsl_vector_max_index(m_vec);
  }

  std::size_t Vector::min_index() const {
    return gsl_vector_min_index(m_vec);
  }

  std::pair<std::size_t, std::size_t> Vector::minmax_index() const {
    std::pair<std::size_t, std::size_t> ans;
    gsl_vector_minmax_index(m_vec, &ans.first, &ans.second);
    return ans;
  }

  bool Vector::isnull() const {
    return gsl_vector_isnull(m_vec);
  }
  bool Vector::ispos() const {
    return gsl_vector_ispos(m_vec);
  }
  bool Vector::isneg() const {
    return gsl_vector_isneg(m_vec);
  }
  bool Vector::isnonneg() const {
    return gsl_vector_isnonneg(m_vec);
  }
  // }}}

  // {{{ Arithmetic

  bool Vector::operator==(const Vector& o) const {
    return gsl_vector_equal(m_vec, o.m_vec);
  }

  // Vector+Vector operations
  Vector& Vector::operator+=(const Vector& o) {
    gsl_vector_add(m_vec, o.m_vec);
    return *this;
  }
  Vector& Vector::operator-=(const Vector& o) {
    gsl_vector_sub(m_vec, o.m_vec);
    return *this;
  }
  Vector& Vector::operator*=(const Vector& o) {
    gsl_vector_mul(m_vec, o.m_vec);
    return *this;
  }
  Vector& Vector::operator/=(const Vector& o) {
    gsl_vector_div(m_vec, o.m_vec);
    return *this;
  }

  // Vector+scaler operations
  Vector& Vector::operator+=(double x) {
    gsl_vector_add_constant(m_vec, x);
    return *this;
  }
  Vector& Vector::operator*=(double x) {
    gsl_vector_scale(m_vec, x);
    return *this;
  }

  Vector& Vector::axpby(const Vector& x, double a, double b) {
    gsl_vector_axpby(a, x.m_vec, b, m_vec);
    return *this;
  }

  // Binary operations
  Vector Vector::operator+(const Vector& o) const {
    Vector ans{*this};
    ans += o;
    return ans;
  }
  Vector Vector::operator-(const Vector& o) const {
    Vector ans{*this};
    ans -= o;
    return ans;
  }
  Vector Vector::operator*(const Vector& o) const {
    Vector ans{*this};
    ans *= o;
    return ans;
  }
  Vector Vector::operator/(const Vector& o) const {
    Vector ans{*this};
    ans /= o;
    return ans;
  }

  Vector Vector::operator+(double x) const {
    Vector ans{*this};
    ans += x;
    return ans;
  }
  Vector Vector::operator*(double x) const {
    Vector ans{*this};
    ans *= x;
    return ans;
  }

  // }}}

}
