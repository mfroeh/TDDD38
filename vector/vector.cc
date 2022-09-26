#include "vector.h"
#include <cmath>
#include <ios>
#include <sstream>

using namespace std;

// ctor
Vector::Vector(double x, double y) : x{x}, y{y} {}

// addition, subtraction, multiplication and division with return result for
// chaining
Vector &Vector::operator+=(Vector const &other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vector &Vector::operator-=(Vector const &other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector &Vector::operator*=(double k) {
  x *= k;
  y *= k;
  return *this;
}

Vector &Vector::operator/=(double k) {
  x /= k;
  y /= k;
  return *this;
}

// read and write from stream
std::istream &operator>>(std::istream &istream, Vector &v) {
  Vector temp{};
  istream >> ws;
  if (istream.peek() == '(') {
    istream.ignore(1) >> ws >> temp.x >> ws;
    if (istream.peek() == ',') {
      istream.ignore(1) >> ws >> temp.y >> ws;
      if (istream.peek() == ')') {
        istream.ignore(1);
        // Copy assignment
        v = temp;
        return istream;
      }
    }
  }
  istream.setstate(ios::failbit);
  return istream;
}

std::ostream &operator<<(std::ostream &ostream, Vector const &v) {
  ostream << v.to_string();
  return ostream;
}

// equality
bool Vector::operator==(Vector const &other) const {
  return x == other.x && y == other.y;
}

bool Vector::operator!=(Vector const &other) const { return !(*this == other); }

// dot product
double Vector::operator*(Vector const &other) const {
  return x * other.x + y + other.y;
}

// euclidean length
double Vector::length() const { return sqrt(pow(x, 2) + pow(y, 2)); }

// string repr
string Vector::to_string() const {
  ostringstream oss{};
  oss << "(" << x << ", " << y << ")";
  return oss.str();
}

// negation
Vector operator-(Vector const &v) { return Vector{v} *= -1; }

// plus and minus
Vector operator+(Vector const &left, Vector const &right) {
  // Copy initialization
  return Vector{left} += right;
}
Vector operator-(Vector const &left, Vector const &right) {
  // Copy initialization
  return Vector{left} -= right;
}

// multplication with constant
Vector operator*(Vector const &v, double k) { return Vector{v} *= k; }
Vector operator*(double k, Vector const &v) { return Vector{v} *= k; }

// division by constant
Vector operator/(Vector const &v, double k) { return Vector{v} /= k; }
