#include <cassert>
#include <type_traits>

using namespace std;

template <typename... Ts> class Pack {};

namespace recur {
template <typename T> bool contains() { return false; }

template <typename T, typename U, typename... Ts> bool contains() {
  return is_same<T, U>::value || contains<T, Ts...>();
}

template <typename T, typename... Ts> bool contains(Pack<Ts...>) {
  return contains<T, Ts...>();
};

template <typename T> int index_of(int) { return -1; }

template <typename T, typename U, typename... Ts> int index_of(int i) {
  return is_same<T, U>::value ? i : index_of<T, Ts...>(i + 1);
}

template <typename T, typename... Ts> int index_of(Pack<Ts...>) {
  return index_of<T, Ts...>(0);
}
} // namespace recur

namespace fold {
template <typename T, typename... Ts> bool contains(Pack<Ts...>) {
  return (std::is_same<T, Ts>::value || ...);
}

template <typename T, typename... Ts> int index_of(Pack<Ts...>) {
  int i{-1};
  return ((i++, std::is_same<T, Ts>::value) || ...) ? i : -1;
}
} // namespace fold

int main() {
  Pack<int, float, char> p;
  assert(recur::contains<int>(p));
  assert(!recur::contains<bool>(p));
  assert(recur::index_of<int>(p) == 0);
  assert(recur::index_of<char>(p) == 2);
  assert(recur::index_of<bool>(p) == -1);

  assert(fold::contains<int>(p));
  assert(!fold::contains<bool>(p));
  assert(fold::index_of<int>(p) == 0);
  assert(fold::index_of<char>(p) == 2);
  assert(fold::index_of<bool>(p) == -1);
}
