#include "Node.h"
#include <iomanip>
#include <iostream>

using namespace std;

Number::Number(double value) : value{value} {}

double Number::evaluate() const { return value; }

void Number::print_tree(ostream &os, int depth) const {
  os << setw(3 * depth) << "" << value << endl;
}

Node *Number::clone() const { return new Number{value}; }

void Number::print(std::ostream &os) const { os << value; }

Operator::Operator(Node *left, Node *right) : left{left}, right{right} {}

Operator::~Operator() {
  delete left;
  delete right;
}

void Operator::print_tree(std::ostream &os, int depth) const {
  int dk = 3 * depth;
  right->print_tree(os, depth + 1);
  os << setw(dk + 1) << ""
     << "/" << endl;
  os << setw(dk) << "" << get_glyph() << endl;
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

  os << get_glyph();

  if (is_mul_div && dynamic_cast<Addition *>(right) != nullptr) {
    os << "(";
    right->print(os);
    os << ")";
  } else {
    right->print(os);
  }
}

double Addition::evaluate() const {
  return left->evaluate() + right->evaluate();
}

Node *Addition::clone() const {
  return new Addition{left->clone(), right->clone()};
}

char Addition::get_glyph() const { return '+'; }

double Multiplication::evaluate() const {
  return left->evaluate() * right->evaluate();
}

Node *Multiplication::clone() const {
  return new Multiplication{left->clone(), right->clone()};
}

char Multiplication::get_glyph() const { return '*'; }

double Subtraction::evaluate() const {
  return left->evaluate() - right->evaluate();
}

Node *Subtraction::clone() const {
  return new Subtraction{left->clone(), right->clone()};
}

char Subtraction::get_glyph() const { return '-'; }

double Division::evaluate() const {
  return left->evaluate() / right->evaluate();
}

Node *Division::clone() const {
  return new Division{left->clone(), right->clone()};
}

char Division::get_glyph() const { return '/'; }
