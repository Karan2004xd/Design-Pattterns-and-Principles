#include <cctype>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class FormattingText {
public:
   struct TextRange {
      int start, end;
      bool capatilize;

      bool covers(int position) const {
         return position >= start && position <= end;
      }

      TextRange(int start, int end) : start(start), end(end) {}
   };

   TextRange &get_range(int start, int end) {
      range.emplace_back(TextRange{start, end});
      return *range.rbegin();
   }

   FormattingText(const std::string &plain_text) : plain_text(plain_text) {}

   friend std::ostream &operator<<(std::ostream &os, const FormattingText &obj) {
      std::string result;
      for (int i = 0; i < obj.plain_text.size(); i++) {
         auto c = obj.plain_text[i];
         for (const auto &rng : obj.range) {
            if (rng.covers(i) && rng.capatilize) {
               c = toupper(c);
            }
            result += c;
         }
      }
      return os << result;
   }
private:
   std::string plain_text;
   std::vector<TextRange> range;
};

int main() {
   FormattingText ft {"This is a brave new world"};
   ft.get_range(10, 15).capatilize = true;
   std::cout << ft << std::endl; // Output : This is a BRAVE new world
   return 0;
}
