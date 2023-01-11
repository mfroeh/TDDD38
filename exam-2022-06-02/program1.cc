#include <cassert>
#include <string>
#include <utility>
#include <cstddef>

struct Sentinel { };

Sentinel make_list() {
    return { };
}

template <typename T, typename ...Args>
auto make_list(T&& first, Args&&... rest) {
    return std::make_pair(std::forward<T>(first), make_list(std::forward<Args>(rest)...));
}

template <size_t N, typename T>
struct Get_Index {
    static auto& value(T& list) {
        return Get_Index<N-1, typename T::second_type>::value(list.second);
    }
};

template <typename T>
struct Get_Index<0, T> {
    static auto& value(T& list) {
        return list.first;
    }
};

template <size_t N, typename T>
auto& get_index(T& list) {
    return Get_Index<N, T>::value(list);
}


int main()
{
    std::string last { "54" };
    auto list1 = make_list(1, 2.3, '4', last);
    assert(get_index<0>(list1) == 1);
    assert(get_index<1>(list1) == 2.3);
    assert(get_index<2>(list1) == '4');
    assert(get_index<3>(list1) == "54");

    // Check that the values can be modified
    get_index<0>(list1) = 10;
    assert(get_index<0>(list1) == 10);
}
