#include <iostream>

using namespace std;

class Cls {
public:
  int num;

public:
  void fun() &;
  void fun() &&;
};

void Cls::fun() & {
  num = 4;
  cout << num << endl;
}
void Cls::fun() && {
  num = 2;
  cout << "rvalue reference overload" << endl;
}

int main(int argc, char *argv[]) {
  Cls &&cls{234234};
  cls.fun();
  cout << cls.num << endl;

  Cls{234}.fun();

  Cls c2{12323};
  c2.fun();

  cout << c2.num << endl;

  int i{};
  cout << i << endl;

  Cls cc{};
  cout << cc.num << endl;
}
