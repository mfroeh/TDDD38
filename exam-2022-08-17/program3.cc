#include "syntax_tree.h"
#include <iostream>
#include <memory>

/* Expected output:

!true = false
!(true && false) = true
(true || false) && false && (false || !false) = false

 */

int main() {

  // Think carefully about the types here. You might have to modify
  // the testcases slightly to make it work.

  std::unique_ptr<Expression> expr1{new Negation{new Literal{true}}};

  expr1->print(std::cout);
  std::cout << " = " << expr1->evaluate() << std::endl;

  std::unique_ptr<Expression> expr2{
      new Negation{new And{new Literal{true}, new Literal{false}}}};

  expr2->print(std::cout);
  std::cout << " = " << expr2->evaluate() << std::endl;

  std::unique_ptr<Expression> expr3{
      new And{new Or{new Literal{true}, new Literal{false}}, new Literal{false},
              new Or{new Literal{false}, new Negation{new Literal{false}}}}};

  expr3->print(std::cout);
}
