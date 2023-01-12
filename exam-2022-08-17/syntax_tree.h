#pragma once
#include <algorithm>
#include <initializer_list>
#include <string>
#include <vector>

class Expression;

void pretty_print(std::ostream &os, Expression *expression);

class Expression {
public:
  virtual ~Expression() = default;
  virtual bool evaluate() = 0;
  virtual void print(std::ostream &os) = 0;
};

class Literal : public Expression {
public:
  Literal(bool value) : value{value} {}

  bool evaluate() override { return value; }

  void print(std::ostream &os) override { os << (value ? "true" : "false"); }

private:
  bool value;
};

class Negation : public Expression {
public:
  Negation(Expression *expression) : expression{expression} {}

  ~Negation() { delete expression; }

  bool evaluate() override { return !expression->evaluate(); }

  void print(std::ostream &os) override {
    os << "!";
    pretty_print(os, expression);
  }

private:
  Expression *expression;
};

class Compound : public Expression {
public:
  Compound(std::initializer_list<Expression *> expr) : expressions{expr} {}

  ~Compound() {
    for (auto &&e : expressions) {
      delete e;
    }
  }

  virtual std::string glyph() = 0;

  void print(std::ostream &os) override {
    pretty_print(os, expressions[0]);

    for (size_t i{1}; i < expressions.size(); ++i) {
      os << " " << glyph() << " ";
      pretty_print(os, expressions[i]);
    }
  }

protected:
  std::vector<Expression *> expressions;
};

class And : public Compound {
public:
  using Compound::Compound;

  std::string glyph() override { return std::string{"&&"}; }

  bool evaluate() override {
    return std::all_of(begin(expressions), end(expressions),
                       [](Expression *e) { return e->evaluate(); });
  }
};

class Or : public Compound {
public:
  using Compound::Compound;

  std::string glyph() override { return std::string{"||"}; }

  bool evaluate() override {
    return std::any_of(begin(expressions), end(expressions),
                       [](Expression *e) { return e->evaluate(); });
  }
};

void pretty_print(std::ostream &os, Expression *expression) {
  if (dynamic_cast<Compound *>(expression)) {
    os << "(";
    expression->print(os);
    os << ")";
  } else {
    expression->print(os);
  }
}
