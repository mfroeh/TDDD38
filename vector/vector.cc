#include "vector.h"
#include <cmath>
#include <ios>
#include <sstream>

using namespace std;

Vector::Vector(double x, double y) : x{x}, y{y} {}

Vector Vector::operator-() { return Vector{-x, -y}; }

Vector Vector::operator+(Vector const &other) const {
  return Vector{x + other.x, y + other.y};
}

Vector Vector::operator-(Vector const &other) const {
  return Vector{x - other.x, y - other.y};
}
Vector Vector::operator*(double k) const { return Vector{x * k, y * k}; }

Vector &Vector::operator*=(double k) {
  x *= k;
  y *= k;
  return *this;
}

Vector operator*(double k, Vector const &v) { return Vector{v.x * k, v.y * k}; }

Vector Vector::operator/(double k) const { return Vector{x / k, y / k}; }

Vector &Vector::operator/=(double k) {
  x /= k;
  y /= y;
  return *this;
}

std::ostream &operator<<(std::ostream &ostream, Vector const &v) {
  ostream << v.to_string();
  return ostream;
}

std::istream &operator>>(std::istream &istream, Vector &v) {
  double x{}, y{};
  istream.ignore(INT_MAX, '(');
  if (istream.fail()) {
    istream.setstate(ios::failbit);
    return istream;
  }
  istream >> x;
  if (istream.fail()) {
    istream.setstate(ios::failbit);
    return istream;
  }
  istream.ignore(INT_MAX, ',');
  if (istream.fail()) {
    istream.setstate(ios::failbit);
    return istream;
  }
  istream >> y;
  if (istream.fail()) {
    istream.setstate(ios::failbit);
    return istream;
  }
  istream.ignore(INT_MAX, ')');
  if (istream.fail()) {
    istream.setstate(ios::failbit);
    return istream;
  }
  v.x = x;
  v.y = y;
  return istream;
}

double Vector::operator*(Vector const &other) const {
  return x * other.x + y * other.y;
}

bool Vector::operator==(Vector const &other) const {
  return x == other.x && y == other.y;
}

bool Vector::operator!=(Vector const &other) const { return !(*this == other); }

double Vector::length() const { return sqrt(pow(x, 2) + pow(y, 2)); }

string Vector::to_string() const {
  ostringstream oss{};
  oss << "(" << x << ", " << y << ")";
  return oss.str();
}
