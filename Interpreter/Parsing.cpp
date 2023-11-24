/*
 * It only supports the parsing and lexing for numeric expression with no:
 * Nested brackets
 * Special characters
 * It only supports '+' and '-' operations 
 * And spaces are also not allowed
 * */

#include <cctype>
#include <exception>
#include <iostream>
#include <memory>
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

struct Element
{
   virtual ~Element() = default;
   virtual int eval() const = 0;
};

struct Integer : Element
{
   int value;
   explicit Integer(const int value)
      : value(value)
   {
   }
   int eval() const override { return value; }
};

struct BinaryOperation : Element
{
   enum Type { addition, subtraction } type;
   std::shared_ptr<Element> lhs, rhs;

   int eval() const override
   {
      if (type == addition) 
         return lhs->eval() + rhs->eval();
      return lhs->eval() - rhs->eval();
   }
};

std::unique_ptr<Element> parse(const std::vector<Token>& tokens)
{
   auto result = std::make_unique<BinaryOperation>();
   bool have_lhs = false;
   for (size_t i = 0; i < tokens.size(); i++)
   {
      auto token = tokens[i];
      switch(token.type)
      {
         case Token::integer:
            {
               int value = std::stoi(token.text);
               auto integer = std::make_shared<Integer>(value);
               if (!have_lhs) {
                  result->lhs = integer;
                  have_lhs = true;
               }
               else result->rhs = integer;
            }
            break;
         case Token::plus: 
            result->type = BinaryOperation::addition;
            break;
         case Token::minus:
            result->type = BinaryOperation::subtraction;
            break;
         case Token::lparen: 
            {
               int j = i;
               for (; j < tokens.size(); ++j)
                  if (tokens[j].type == Token::rparen)
                     break; // found it!

               std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
               auto element = parse(subexpression);
               if (!have_lhs) 
               {
                  result->lhs = std::move(element);
                  have_lhs = true;
               }
               else result->rhs = std::move(element);
               i = j; // advance
            }
            break;
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

   try {
      auto parsed = parse(result);
      std::cout << input << " = " << parsed->eval() << std::endl;
   } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
   }
   return 0;
}
