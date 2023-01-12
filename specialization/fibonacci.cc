#include <cassert>
#include <iostream>
#include <type_traits>

template <int N> class Fibonacci {
public:
  static unsigned long long const value{Fibonacci<N - 2>::value +
                                        Fibonacci<N - 1>::value};
};

template <> class Fibonacci<1> {
public:
  static unsigned long long const value{1};
};

template <> class Fibonacci<0> {
public:
  static unsigned long long const value{0};
};

int main() {
  assert(Fibonacci<0>::value == 0);
  assert(Fibonacci<1>::value == 1);
  assert(Fibonacci<5>::value == 5);
  assert(Fibonacci<10>::value == 55);
  assert(Fibonacci<12>::value == 144);
  std::cout << Fibonacci<20>::value;
}
