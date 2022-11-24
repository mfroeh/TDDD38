#include <iostream>

template <typename ...Ts>
void print(Ts... list) {
  // Unary left fold
  // expression op ...
  // The comma operator works as a semicolon
  ((std::cout << list << ' '), ...);
  std::endl(std::cout);
}
