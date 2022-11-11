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
public:
  Number(double value);

  double evaluate() const override;
  void print_tree(std::ostream &os, int depth = 0) const override;
  Node *clone() const override;
  void print(std::ostream &os) const override;

private:
  double value;
};

class Operator : public Node {
public:
  Operator(Node *left, Node *right);
  ~Operator();

  void print_tree(std::ostream &os, int depth = 0) const override;
  void print(std::ostream &os) const override;
  
protected:
  Node *left;
  Node *right;

  virtual char get_glyph() const = 0;
};

class Addition : public Operator {
public:
  using Operator::Operator;
  virtual double evaluate() const override;
  virtual Node *clone() const override;

protected:
  char get_glyph() const override;
};

class Multiplication : public Operator {
public:
  using Operator::Operator;
  virtual double evaluate() const override;
  virtual Node *clone() const override;

protected:
  char get_glyph() const override;
};

class Subtraction : public Addition {
public:
  using Addition::Addition;
  double evaluate() const override;
  Node *clone() const override;

protected:
  char get_glyph() const override;
};

class Division : public Multiplication {
public:
  using Multiplication::Multiplication;
  double evaluate() const override;
  Node *clone() const override;

protected:
  char get_glyph() const override;
};
