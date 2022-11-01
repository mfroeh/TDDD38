#include <iostream>
using namespace std;

union IntDouble {
    int someInt;
    double someDouble;
};

enum class Status : char {
    NONE,
    ERROR,
};

enum Experiment {
    OK = 1234,
};

int func(int (*arr_ptr)[3]) {
    return *arr_ptr[3];
}

int otherFunc(double, int) {
    return 0;
}

class MeClass {
    public:
        int x;
        MeClass(int y) {
            x = y;
        }
};

int main()
{
    // Array pointers
    // Type in array (*name)[size]{arr}
    int arr[3] {1, 2, 33};
    int (*arr_ptr)[3]{&arr};

    // arr_ptr + 2 <=> arr_ptr[2]
    // These are both addresses!
    cout << arr_ptr[2] << endl;
    cout << arr_ptr + 2 << endl;
    cout << arr[2] << endl;
    
    // Function pointers are similar
    // Return type (*name)(parameter types){func};
    int (*func_ptr)(int (*)[3]){func};
    int x {func_ptr(arr_ptr)};

    // lvalues are expressions that will refer to the same object every time we use it
    // Examples are functions, variables, dereferenced pointers or array's at a certain index
    // lvalues have identity (the expression refers to a specific object)

    // rvalues are those values, that aren't lvalues
    // They are temporary values, and therefore have no identity (expression refers to value instead of object)
    // Examples are x + 12 and literals such as "mystring"

    // An expression is either a gvalue or a rvalue
    // glvalues denotes an object with identiy
    // lvalues are all glvalues that are not xvalues
    // xvalues are expiring values (denote an object bound to an rvalue reference)
    // prvalues are value literals or expressions that can be evaluated to a temporary value.
    // They can be used to initialize glvalues
    return 0;
}
