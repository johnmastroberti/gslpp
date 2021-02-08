#pragma once
#include <gsl/gsl_vector.h>
#include <utility>

namespace gsl {

  class Vector {
    private:
      gsl_vector* m_vec;

    public:
      // Special member functions
      Vector();
      Vector(std::size_t len);
      Vector(std::size_t len, double x);
      Vector(const Vector&);
      Vector& operator=(const Vector&);
      Vector(Vector&&);
      Vector& operator=(Vector&&);
      ~Vector();

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
