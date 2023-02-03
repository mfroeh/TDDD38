#include <cstdint>
#include <iostream>

struct Dark {
  int64_t one;
  int64_t two;
  int64_t three;
  int64_t four;

  int64_t operator[](int i) {
    std::cout << this + i * sizeof(int64_t) << std::endl;
    return *(reinterpret_cast<int64_t *>(this) + i);
  }
};

struct VirtualDark {
  int64_t one;
  int64_t two;
  int64_t three;
  int64_t four;

  VirtualDark(int64_t a, int64_t b,int64_t c,int64_t d) : one{a}, two{b}, three{c}, four{d} {}
  virtual void blub() {}

  int64_t operator[](int i) {
    std::cout << this + i * sizeof(int64_t) << std::endl;
    return *(reinterpret_cast<int64_t *>(this) + i+1);
  }
};

int main(int argc, char *argv[]) {
  Dark *d{new Dark{1, 2, 3, 4}};
  VirtualDark *vd{new VirtualDark{1, 2, 3, 4}};
  for (size_t i{}; i < 4; ++i) {
    // std::cout << (*d)[i] << std::endl;
    std::cout << (*vd)[i] << std::endl;
  }

  std::cout << vd << std::endl;
  std::cout << &vd->one << std::endl;
  std::cout << &vd->two << std::endl;
  std::cout << &vd->three << std::endl;
  std::cout << &vd->four << std::endl;
}
