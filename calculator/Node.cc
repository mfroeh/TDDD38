#include "Node.h"
#include <iomanip>

using namespace std;

// #include <iostream>
// int main(int argc, char *argv[]) {
//   Number n1{1};
//   Number n2{2};
//   Number n3{3};
//   Number n4{4};

//   Addition a1{&n1, &n2};
//   Addition a2{&n3, &n4};
//   Multiplication m1{&a1, &a2};
//   Subtraction s1{&n3, &n4};

//   m1.print_tree(cout);
//   m1.print(cout);
// }

Number::Number(double value) : value{value} {}

double Number::evaluate() const { return value; }

void Number::print_tree(ostream &os, int depth) const {
  os << setw(3 * depth) << "" << value << endl;
}

Node *Number::clone() const { return new Number{value}; }

void Number::print(std::ostream &os) const { os << value; }

Operator::Operator(Node *left, Node *right) : left{left}, right{right} {}

void Operator::print_tree(std::ostream &os, int depth) const {
  int dk = 3 * depth;
  right->print_tree(os, depth + 1);
  os << setw(dk + 1) << ""
     << "/" << endl;
  os << setw(dk) << "" << op << endl;
  os << setw(dk + 1) << ""
     << "\\" << endl;
  left->print_tree(os, depth + 1);
}

void Operator::print(std::ostream &os) const {
  bool is_mul_div = typeid(*this) == typeid(Multiplication) ||
                    typeid(*this) == typeid(Division);

  if (is_mul_div && dynamic_cast<Addition *>(left) != nullptr) {
    os << "(";
    left->print(os);
    os << ")";
  } else {
    left->print(os);
  }

  os << op;

  if (is_mul_div && dynamic_cast<Addition *>(right) != nullptr) {
    os << "(";
    right->print(os);
    os << ")";
  } else {
    right->print(os);
  }
}

Addition::Addition(Node *left, Node *right) : Operator{left, right} {
  op = '+';
}

double Addition::evaluate() const {
  return left->evaluate() + right->evaluate();
}

Node *Addition::clone() const {
  return new Addition{left->clone(), right->clone()};
}

Multiplication::Multiplication(Node *left, Node *right)
    : Operator{left, right} {
  op = '*';
}

double Multiplication::evaluate() const {
  return left->evaluate() * right->evaluate();
}

Node *Multiplication::clone() const {
  return new Multiplication{left->clone(), right->clone()};
}

Subtraction::Subtraction(Node *left, Node *right) : Addition{left, right} {
  op = '-';
}

double Subtraction::evaluate() const {
  return left->evaluate() - right->evaluate();
}

Node *Subtraction::clone() const {
  return new Subtraction{left->clone(), right->clone()};
}

Division::Division(Node *left, Node *right) : Multiplication{left, right} {
  op = '/';
}

double Division::evaluate() const {
  return left->evaluate() / right->evaluate();
}

Node *Division::clone() const {
  return new Division{left->clone(), right->clone()};
}
