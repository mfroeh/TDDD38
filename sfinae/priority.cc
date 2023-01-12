#include <iostream>
#include <utility>

template <typename T>
auto get_priority(T &&t, int, int, int) -> decltype(t.first()) {
  return t.first();
}

template <typename T>
auto get_priority(T &&t, int, int, long) -> decltype(t.second()) {
  return t.second();
}

template <typename T>
auto get_priority(T &&t, int, long, long) -> decltype(t.third()) {
  return t.third();
}

template <typename T> int get_priority(T &&t, long, long, long) { return 4; }

template <typename T> int get_priority(T &&t) {
  return get_priority(std::forward<T>(t), 1, 1, 1);
}

struct X {
  int first() const { return 1; }
};

struct Y {
  int second() const { return 2; }
};

struct Z {
  int third() const { return 3; }
};

struct XY {
  int first() const { return 1; }
  int second() const { return 2; }
};

struct XZ {
  int first() const { return 1; }
  int third() const { return 3; }
};

struct YZ {
  int second() const { return 2; }
  int third() const { return 3; }
};

struct XYZ {
  int first() const { return 1; }
  int second() const { return 2; }
  int third() const { return 3; }
};

int main() {
  using std::cout;
  using std::endl;

  cout << get_priority(X{}) << endl
       << get_priority(Y{}) << endl
       << get_priority(Z{}) << endl
       << get_priority(XY{}) << endl
       << get_priority(XZ{}) << endl
       << get_priority(YZ{}) << endl
       << get_priority(XYZ{}) << endl
       << get_priority(5) << endl;
}
