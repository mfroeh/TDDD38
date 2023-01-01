#include <type_traits>

template <typename T>
struct remove_reference
{
  using type = T;
};

template <typename T>
struct remove_reference<T&> {
  using type = T;
};

template <typename T>
struct remove_reference<T&&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
struct remove_pointers {
  using type = T;
};

template <typename T>
struct remove_pointers<T*> {
  using type = typename remove_pointers<T>::type;
};

template <typename T>
struct remove_pointers<T* const> {
  using type = typename remove_pointers<T>::type;
};

template <typename T>
using remove_pointers_t = typename remove_pointers<T>::type;

int main()
{
  static_assert(std::is_same<
                remove_reference<int&&>::type, int
                >::value, "remove_reference failed for 'int&&'");
  static_assert(std::is_same<
                remove_reference<int&>::type, int
                >::value, "remove_reference failed for 'int&'");
  static_assert(std::is_same<
                remove_reference<int>::type, int
                >::value, "remove_reference failed for 'int'");
  static_assert(std::is_same<
                remove_reference<int const&>::type, int const
                >::value, "remove_reference failed for 'int const&'");

  static_assert(std::is_same<
                remove_pointers<int>::type, int
                >::value, "remove_pointers failed for 'int'");
  static_assert(std::is_same<
                remove_pointers<int*>::type, int
                >::value, "remove_pointers failed for 'int*'");
  static_assert(std::is_same<
                remove_pointers<int* const>::type, int
                >::value, "remove_pointers failed for 'int* const'");
  static_assert(std::is_same<
                remove_pointers<int* const*>::type, int
                >::value, "remove_pointers failed for 'int* const*'");
  static_assert(std::is_same<
                remove_pointers<int***>::type, int
                >::value, "remove_pointers failed for 'int***'");

  // Using alias templates
  static_assert(std::is_same_v<
                remove_reference_t<int&&>, int
                >, "remove_reference failed for 'int&&'");
  static_assert(std::is_same_v<
                remove_reference_t<int&>, int
                >, "remove_reference failed for 'int&'");
  static_assert(std::is_same_v<
                remove_reference_t<int>, int
                >, "remove_reference failed for 'int'");
  static_assert(std::is_same_v<
                remove_reference_t<int const&>, int const
                >, "remove_reference failed for 'int const&'");

  static_assert(std::is_same_v<
                remove_pointers_t<int>, int
                >, "remove_pointers failed for 'int'");
  static_assert(std::is_same_v<
                remove_pointers_t<int*>, int
                >, "remove_pointers failed for 'int*'");
  static_assert(std::is_same_v<
                remove_pointers_t<int* const>, int
                >, "remove_pointers failed for 'int* const'");
  static_assert(std::is_same_v<
                remove_pointers_t<int* const*>, int
                >, "remove_pointers failed for 'int* const*'");
  static_assert(std::is_same_v<
                remove_pointers_t<int***>, int
                >, "remove_pointers failed for 'int***'");
}
