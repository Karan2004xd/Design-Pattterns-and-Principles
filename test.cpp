#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

struct Sentence
{
   struct WordToken
   {
      bool capitalize;
      int start, end;

      bool covers(int position) const {
         return position >= start && position <= end;
      }

      WordToken(int start, int end) : start(start), end(end) {}
   };

   Sentence(const std::string& text) : text(text) {}

   WordToken& operator[](size_t index)
   {
      int temp_start {-1}, temp_end;
      for (int i = 0; i < text.size(); i++) {
         if (index == 0 && text[i] != ' ') {
            if (temp_start == -1) {
               temp_start = i;
               temp_end = i;
            } 
            temp_end++;
         } 
         if (text[i] == ' ') {
            index--;
         }
      }
      words.emplace_back(WordToken {temp_start, temp_end});
      return *words.rbegin();
   }

   std::string str() const
   {
      std::string result_str;
      for (int i = 0; i < text.size(); i++) {
         auto c = text[i];
         for (auto &word : words) {
            if (word.covers(i) && word.capitalize) {
               c = toupper(c);
            }
         }
         result_str += c;
      }
      return result_str;
   }

private:
   std::vector<WordToken> words;
   std::string text;
};

int main() {
   Sentence sentence("alpha beta gamma");
   sentence[1].capitalize = true;
   std::cout << sentence.str() << std::endl;
   return 0;
};
