/*
  Implement the classes:
  - Node
  - Number
  - Operator
  - Addition
  - Subtraction
  - Multiplication
  - Division

  Node should have the following (pure virtual) members:
  - double evaluate()
    + Calculate the expression stored in 'this'
  - void print(std::ostream& os)
    + print the expression represented in 'this'
  - void print_tree(std::ostream& os, int depth)
    + print a textual representation of the expression tree
  - Node* clone()
    + return a a new instance of the expression stored in 'this'
 */
#include <memory>
#include <ostream>

class Node {
public:
  virtual ~Node() = default;
  virtual double evaluate() const = 0;
  virtual void print_tree(std::ostream &os, int depth = 0) const = 0;
  virtual Node *clone() const = 0;
  virtual void print(std::ostream &os) const = 0;
};

class Number : public Node {
private:
  double value;

public:
  Number(double value);
  double evaluate() const override;
  void print_tree(std::ostream &os, int depth = 0) const override;
  Node *clone() const override;
  void print(std::ostream &os) const override;
};

class Operator : public Node {
protected:
  Node *left;
  Node *right;
  char op;

public:
  Operator(Node *left, Node *right);
  void print_tree(std::ostream &os, int depth = 0) const override;
  void print(std::ostream &os) const override;
};

class Addition : public Operator {
public:
  Addition(Node *left, Node *right);
  double evaluate() const override;
  Node *clone() const override;
};

class Multiplication : public Operator {
public:
  Multiplication(Node *left, Node *right);
  double evaluate() const override;
  Node *clone() const override;
};

class Subtraction : public Addition {
public:
  Subtraction(Node *left, Node *right);
  double evaluate() const override;
  Node *clone() const override;
};

class Division : public Multiplication {
public:
  Division(Node *left, Node *right);
  double evaluate() const override;
  Node *clone() const override;
};
