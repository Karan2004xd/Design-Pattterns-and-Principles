#include <iostream>
#include <sstream>

struct Expression {
   virtual ~Expression() = default;
   virtual void print(std::ostringstream &oss) = 0;
};

struct DoubleExpression : Expression {
   double value;
   DoubleExpression(double value) : value(value) {}

   void print(std::ostringstream &oss) override {
      oss << value;
   }
};

struct AdditionExpression : Expression {
   Expression *left, *right;
   AdditionExpression(Expression *left, Expression *right) : left(left), right(right) {}

   void print(std::ostringstream &oss) override {
      oss << "(";
      left->print(oss);
      oss << "+";
      right->print(oss);
      oss << ")";
   }

   ~AdditionExpression() {
      delete left;
      delete right;
   }
};

int main() {
   auto e = new AdditionExpression(
         new DoubleExpression {1},
         new AdditionExpression 
         {
            new DoubleExpression {2},
            new DoubleExpression {5}
         }
      );

   std::ostringstream oss;
   e->print(oss);
   std::cout << oss.str() << std::endl;

   delete e;

   return 0;
}
