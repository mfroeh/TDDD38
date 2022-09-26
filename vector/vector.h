#pragma once
#include <istream>
#include <ostream>
#include <string>

class Vector {
public:
  // ctor
  Vector(double x = 0, double y = 0);

  // addition, subtraction, multiplication and division with return result for
  // chaining
  Vector &operator+=(Vector const &other);
  Vector &operator-=(Vector const &other);
  Vector &operator*=(double k);
  Vector &operator/=(double k);

  // read and write from stream
  friend std::istream &operator>>(std::istream &istream, Vector &v);
  friend std::ostream &operator<<(std::ostream &ostream, Vector const &v);

  // equality
  bool operator==(Vector const &other) const;
  bool operator!=(Vector const &other) const;

  // dot product
  double operator*(Vector const &other) const;

  // euclidean length
  double length() const;

  // string repr
  std::string to_string() const;

private:
  double x{};
  double y{};
};

// negation
Vector operator-(Vector const &v);

// plus and minus
Vector operator+(Vector const &left, Vector const &right);
Vector operator-(Vector const &left, Vector const &right);

// multplication with constant
Vector operator*(Vector const &left, double k);
Vector operator*(double k, Vector const &left);

// division by constant
Vector operator/(Vector const &left, double k);
