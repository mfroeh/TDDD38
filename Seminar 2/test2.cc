#include <iostream>
#include <string>
using namespace std;

int get_copy() {
    return 432;
}

int& get_lvalue_ref() {
    int x{2};
    cout << &x << endl;
    return x;
}

int&& get_rvalue_ref() {
    return 42;
}

// int main(int argc, char const* argv[])
// {
//     int x = get_copy();
//     int const& lvalue_ref = get_lvalue_ref();
//     int&& rvalue_ref = get_rvalue_ref();
//     lvalue_ref = x;
//     cout << &lvalue_ref << endl;
//     cout << lvalue_ref << endl;
//     cout << &x << endl;
// }


int task_2_3() {
    char _c{'a'};
    int i{1};
    char* a{&_c};
    int b[10]{0, 234};
    string (*c)[3];
    char** d{&a};
    int const e{1};
    int const* f{&i};
    int* const g{&i};
}

int task_4() {
    int a(int i); // Declares a function a that returns an integer and takes an integer as argument
    int a(int); // Declares a function a that returns an integer and takes an integer as argument
    int a(int (i)); // Legal: The parentheses around i are redundant
    int a(int (*i)()); // Legal: a takes as an argument a pointer to a function returning an int and taking no arguments
    int a(int* const); // Legal: a takes as it's argument a constant ptr to an int
    int a(int const* (*)()); // Legal: a takes a as argument a pointer to a function returning a pointer to a constant integer and taking no arguments.
    int a(int (*)(int)); // Legal: a takes a pointer to a function returning an integer and taking an integer.
}

int ok(int a, int b) {
    return 1 * a * b;
}

int task_5() {
    using x = int(&)(int, int);

    x l{ok};
    std::string test{"Hello World!"};
    cout << test.length() << " " << test.size() << endl;
}

int main(int argc, char *argv[]) {
    task_5();
    int i4 = {};
    std::string str4(3, 'a');
    cout << str4 << endl;
    unsigned i{};
    cout << i << endl;
    double x{234.0f}; // Non narrowing conversions are fine.
    cout << x << endl;

    return 0;
}

/*
1. 
a) lvalue
b) rvalue
c) rvalue
d) rvalue
e) lvalue
f) lvalue
g) lvalue
h) lvalue
*/
