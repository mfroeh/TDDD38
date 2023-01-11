#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace details {
    template <typename T, typename V>
    auto prepend(T& t, V&& v, int, int) -> decltype(t.push_front(v), std::declval<void>()) {
        t.push_front(v);
    }

    template <typename T, typename V>
    auto prepend(T& t, V&& v, int, float) -> decltype(t = v + t, std::declval<void>()) {
        t = v + t;
    }

    template <typename T, typename V>
    auto prepend(T& t, V&& v, float, float) -> decltype(t.insert(begin(t), v), std::declval<void>()) {
        t.insert(begin(t), v);
    }
}

template <typename T, typename V>
auto prepend(T& t, V&& v) {
    return details::prepend(t, std::forward<V>(v), 0, 0);
}

int main()
{
    std::vector<int> v { 1, 2, 3 };

    assert(v.front() == 1);
    prepend(v, 0);
    assert(v.front() == 0);

    std::list<float> d { 1.2f, 3.45f, 67.8f, 9.0f };

    assert(d.front() == 1.2f);
    prepend(d, 0);
    assert(d.front() == 0.0f);

    std::string s { "ello world!" };

    assert(s.front() == 'e');
    prepend(s, 'H');
    assert(s.front() == 'H');
}
