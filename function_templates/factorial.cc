#include <iostream>

using namespace std;

template <int N>
unsigned long long factorial() {
    return factorial<N-1>() * N;
}

template <>
unsigned long long factorial<0>() {
    return 1;
}

int main()
{
    cout << factorial<0>() << endl;
    cout << factorial<1>() << endl;
    cout << factorial<5>() << endl;
    cout << factorial<20>() << endl;
}
