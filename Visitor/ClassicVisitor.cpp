#include <iostream>
#include <sstream>
#include <string>

struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpression;

struct ExpressionVisitor {
   virtual void visit(DoubleExpression *de) = 0;
   virtual void visit(AdditionExpression *ae) = 0;
   virtual void visit(SubtractionExpression *ae) = 0;
};

struct ExpressionPrinter : ExpressionVisitor {
   std::ostringstream oss;
   std::string str() { return oss.str(); }

   void visit(DoubleExpression *de) override;
   void visit(AdditionExpression *ae) override;
   void visit(SubtractionExpression *ae) override;
};

struct ExpressionEvaluator : ExpressionVisitor {
   double result;
   void visit(DoubleExpression *de) override;
   void visit(AdditionExpression *ae) override;
   void visit(SubtractionExpression *ae) override;
};

struct Expression {
   virtual void accept(ExpressionVisitor *visitor) = 0;
   virtual ~Expression() = default;
};

struct DoubleExpression : Expression {
   double value;
   DoubleExpression(double value) : value(value) {}

   void accept(ExpressionVisitor *visitor) override {
      visitor->visit(this);
   }
};

struct AdditionExpression : Expression {
   Expression *left, *right;
   AdditionExpression(Expression *left, Expression *right) : left(left), right(right) {}

   void accept(ExpressionVisitor *visitor) override {
      visitor->visit(this);
   }

   ~AdditionExpression() {
      delete left;
      delete right;
   }
};

struct SubtractionExpression : Expression {
   Expression *left, *right;
   SubtractionExpression(Expression *left, Expression *right) : left(left), right(right) {}

   void accept(ExpressionVisitor *visitor) override {
      visitor->visit(this);
   }

   ~SubtractionExpression() {
      delete left;
      delete right;
   }
};

void ExpressionPrinter::visit(DoubleExpression *de) {
   oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression *ae) {
   bool need_braces = dynamic_cast<SubtractionExpression *>(ae->right);
   ae->left->accept(this);
   oss << "+";
   if (need_braces) oss << "(";
   ae->right->accept(this);
   if (need_braces) oss << ")";
}

void ExpressionPrinter::visit(SubtractionExpression *se) {
   bool need_braces = dynamic_cast<SubtractionExpression *>(se->right);
   if (need_braces) oss << "(";
   se->left->accept(this);
   oss << "-";
   se->right->accept(this);
   if (need_braces) oss << ")";
}

void ExpressionEvaluator::visit(DoubleExpression *de) {
   result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression *ae) {
   ae->left->accept(this);
   auto temp = result;
   ae->right->accept(this);
   result += temp;
}

void ExpressionEvaluator::visit(SubtractionExpression *se) {
   se->left->accept(this);
   auto temp = result;
   se->right->accept(this);
   result = temp - result;
}

int main() {
   auto e = new AdditionExpression {
      new DoubleExpression {1},
      new SubtractionExpression {
         new DoubleExpression {2},
         new DoubleExpression {3}
      }
   };

   ExpressionPrinter ep;
   ep.visit(e);

   ExpressionEvaluator ev;
   ev.visit(e);
   std::cout << ep.str() << " = " << ev.result << std::endl;

   delete e;
   return 0;
}
