#pragma once
#include <istream>
#include <ostream>
#include <string>

class Vector {
public:
  Vector(double x = 0, double y = 0);
  Vector operator-();
  Vector operator+(Vector const &other) const;
  Vector operator-(Vector const &other) const;
  Vector operator*(double k) const;
  Vector &operator*=(double k);
  friend Vector operator*(double k, Vector const &v);
  Vector operator/(double k) const;
  Vector &operator/=(double k);
  friend std::ostream &operator<<(std::ostream &ostream, Vector const &v);
  friend std::istream &operator>>(std::istream &istream, Vector &v);
  double operator*(Vector const &other) const;
  bool operator==(Vector const &other) const;
  bool operator!=(Vector const &other) const;
  double length() const;
  std::string to_string() const;

private:
  double x{};
  double y{};
};
