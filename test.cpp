#include <iostream>
#include <string>

struct Sentence
{
   struct WordToken
   {
      bool capitalize;
   };

   Sentence(const std::string& text)
      : text(text) {}

   WordToken& operator[](size_t index)
   {
      for (int i = 0; i < text.size(); i++) {
         if (index > 0 && text[i] == ' ') {
            index--;
         } else {
            if (index <= 0) {
            }
         }
      }
   }

   std::string str() const
   {
      // todo
   }

private:
   std::string text;
   int start, end;
};

int main() {
   std::string str {"hello world"};
   std::cout << str.find("world") << std::endl;
   return 0;
}
