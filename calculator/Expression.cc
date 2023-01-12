#include "Expression.h"

#include <ostream>
#include <stdexcept>

void Expression::print(std::ostream &os) const { root->print(os); }

void Expression::print_tree(std::ostream &os) const { root->print_tree(os); }

Expression::Expression(Node *root) : root{root} {}
Expression::Expression(Expression const &other) { root = other.root->clone(); }
Expression::Expression(Expression &&other) {
  root = other.root;
  other.root = nullptr;
}

Expression::~Expression() { delete root; }

Expression &Expression::operator=(Expression const &rhs) {
  root = rhs.root->clone();
  return *this;
}

double Expression::evaluate() const { return root->evaluate(); }

Expression &Expression::operator=(Expression &&rhs) {
  root = rhs.root;
  rhs.root = nullptr;
  return *this;
}

/* For part C */
void Expression::expand() {
  throw std::invalid_argument{"--expand is unimplemented"};
}
