#include <cctype>
#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <vector>

struct Token {
   std::string text;
   enum Type { integer, plus, minus, lparen, rparen } type;
   Token(Type type, const std::string &text) : type(type), text(text) {}

   friend std::ostream &operator<<(std::ostream &os, const Token &token) {
      os << "`" << token.text << "`";
      return os;
   }
};

std::vector<Token> lex(std::string &input) {
   std::vector<Token> result;
   for (int i = 0; i < input.size(); i++) {
      switch (input[i]) {
         case '+':
            result.push_back(Token {Token::Type::plus, "+"});
            break;
         case '-':
            result.push_back(Token {Token::Type::minus, "-"});
            break;
         case '(':
            result.push_back(Token {Token::Type::lparen, "("});
            break;
         case ')':
            result.push_back(Token {Token::Type::rparen, ")"});
            break;
         default:
            std::ostringstream oss;
            oss << input[i];
            for (int j = i + 1; j < input.size(); j++) {
               if (isdigit(input[j])) {
                  oss << input[j];
                  i++;
               } else {
                  result.push_back(Token {Token::Type::integer, oss.str()});
                  break;
               }
            }
      }
   }
   return result;
}

int main() {
   std::string input {"(13-4)-(12+1)"};
   auto result = lex(input);
   for (auto &t : result) {
      std::cout << t << " ";
   }
   std::cout << "\n";
   return 0;
}
