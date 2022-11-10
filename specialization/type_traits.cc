class is_not {
    public:
        static bool const value{false};
};

class is {
    public:
        static bool const value{true};
};

// is_const
template <typename T>
class is_const : public is_not {};

template <typename T>
class is_const<T const> : public is {};

// is_pointer
template <typename T>
class is_pointer : public is_not {};

template <typename T>
class is_pointer<T*> : public is {};

template <typename T>
class is_pointer<T* const> : public is {};

// is_array
template <typename T>
class is_array : public is_not {};

template <typename T, unsigned int N>
class is_array<T[N]> : public is {};

// is_const_pointer
template <typename T>
class is_const_pointer {
    public:
        static bool const value{is_const<T>::value && is_pointer<T>::value};
};

int main()
{ 
  static_assert(is_const<int const>::value, "is_const failed for 'int const'");
  static_assert(is_const<int* const>::value, "is_const failed for 'int* const'");
  static_assert(!is_const<int>::value, "is_const failed for 'int'");
  static_assert(!is_const<int const*>::value, "is_const failed for 'int const*'");

  static_assert(is_pointer<int*>::value, "is_pointer failed for 'int*'");
  static_assert(is_pointer<int const*>::value, "is_pointer failed for 'int const*'");
  static_assert(is_pointer<int* const>::value, "is_pointer failed for 'int* const'");
  static_assert(!is_pointer<int>::value, "is_pointer failed for 'int'");

  static_assert(is_array<int[5]>::value, "is_array failed for 'int[5]'");
  static_assert(is_array<int const[7]>::value, "is_array failed for 'int const[7]'");
  static_assert(!is_array<int>::value, "is_array failed for 'int'");

  static_assert(is_const_pointer<int* const>::value, "is_const_pointer failed for 'int* const'");
  static_assert(!is_const_pointer<int*>::value, "is_const_pointer failed for 'int*'");
  static_assert(!is_const_pointer<int>::value, "is_const_pointer failed for 'int'");
  static_assert(!is_const_pointer<int const>::value, "is_const_pointer failed for 'int const'");
}
