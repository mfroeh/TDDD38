#include <utility>

struct A {
  A(int i) : ptr{new int{i}} {}
  ~A() { delete ptr; }
  int *ptr{};
};

int main() {
  A one{123};
  A two{std::move(one)};
}
