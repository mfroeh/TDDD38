#include <iostream>

template <typename... Ts> class Pack {};

template <typename T> template <typename... Ts> bool contains(Pack<Ts> pack) {
  return true;
}

int main() {
  Pack<int, double, float, void> p{};
    std::cout << contains<int>(p
};
}