#include <cassert>
#include <cstddef>
#include <iterator>
#include <list>
#include <vector>

#include <iostream>
using namespace std;

template <typename T>
concept Iter = requires(T t) {
    {std::begin(t)} -> std::input_iterator;
    {std::end(t)} -> std::input_iterator;
};

template <typename T> requires (!Iter<T>)
size_t count_bytes(T t) {
    return sizeof(t);
}

template <Iter T>
size_t count_bytes(T const& obj) {
    size_t sum{};
    for (auto&& e : obj) {
        sum += count_bytes(e);
    }
    return sum;
}

// Somehow the c-arrays don't qualify for Iter<T>
template <typename T, size_t N>
size_t count_bytes(T (&arr)[N]) {
    size_t sum{};
    for (auto&& e : arr) {
        sum += count_bytes(e);
    }
    return sum;
}

int main()
{
    /*
    int x { 9 };
    assert(count_bytes(x) == sizeof(int));

    std::vector<int> v { 1, 2, 3 };
    assert(count_bytes(v) == 3 * sizeof(int));

    std::list<std::vector<std::string>> l {
	{ "a", "bc" }, // 3 chars
	{ },           // 0 chars
	{ "defg" },    // 4 chars
    };

    // 3 + 0 + 4 = 7 chars
    assert(count_bytes(l) == 7 * sizeof(char));
    */
    std::vector<int> array[] = {
	{ 1, 2, 3, 4 }, // 4 ints
	{ 5, 6 },       // 2 ints
	{ },            // 0 ints
	{ 7, 8 },       // 2 ints
    };

    // 4 + 2 + 0 + 2 = 8 ints
    assert(count_bytes(array) == 8 * sizeof(int));
}
