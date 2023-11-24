#include <cctype>
#include <map>
#include <sstream>
#include <string>
#include <iostream>

struct ExpressionProcessor
{
   std::map<char,int> variables;
   int result {0};
   bool add_num {true};

   void evaluate(int number) {
      if (add_num) {
         result += number;
      } else {
         result -= number;
      }
   }

   int calculate(const std::string& expression)
   {
      result = 0;
      for (int i = 0; i < expression.size(); i++) {
         if (isdigit(expression[i])) {
            std::ostringstream oss;
            oss << expression[i];
            int j = i + 1;
            for (; j < expression.size(); j++) {
               if (!isdigit(expression[j])) break;
               else {
                  oss << expression[j];
               }
            }
            i = j - 1;
            evaluate(std::stoi(oss.str()));
         } else if (expression[i] == '-') {
            add_num = false;
         } else if (expression[i] == '+') {
            add_num = true;
         } else {
            std::map<char, int>::iterator it {variables.begin()};
            bool is_found {false};
            while (it != variables.end()) {
               if (it->first == expression[i]) {
                  evaluate(it->second);
                  is_found = true;
               }
               it++;
            }
            if (!is_found) {
               result = 0;
               break;
            }
         }
      }
      return result;
   }
};

int main() {
   ExpressionProcessor ep;
   ep.variables['x'] = 5;
   std::cout << ep.calculate("1") << std::endl;;
   std::cout << ep.calculate("1+2") << std::endl;;
   std::cout << ep.calculate("1+x") << std::endl;;
   std::cout << ep.calculate("1+xy") << std::endl;;
   return 0;
}
