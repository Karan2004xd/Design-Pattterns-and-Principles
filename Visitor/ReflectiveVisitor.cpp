#include <iostream>
#include <sstream>
#include <string>

struct Expression {
   virtual ~Expression() = default;
};

struct AdditionExpression : Expression {
   Expression *left, *right;
   AdditionExpression(Expression *left, Expression *right) : left(left), right(right) {}
};

struct DoubleExpression : Expression {
   double value;
   DoubleExpression(double value) : value(value) {}
};

struct ExpressionPrinter {
   std::ostringstream oss;
   void print(Expression *e) {
      if (auto de = dynamic_cast<DoubleExpression*>(e)) {
         oss << de->value;
      } else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {
         oss << "(";
         print(ae->left);
         oss << "+";
         print(ae->right);
         oss << ")";
      }
   }

   std::string str() const { return oss.str(); }
};

int main() {
   auto e = new AdditionExpression {
      new DoubleExpression {1},
      new AdditionExpression {
         new DoubleExpression {2},
         new DoubleExpression {3}
      }
   };

   ExpressionPrinter ep;
   ep.print(e);
   std::cout << ep.str() << std::endl;

   delete e;
   return 0;
}
