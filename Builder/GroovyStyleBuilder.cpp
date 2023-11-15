#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

struct Tag {
protected:
   std::string name, text;
   std::vector<std::pair<std::string, std::string>> attributes;
   std::vector<Tag> childrens;

   friend std::ostream &operator<<(std::ostream &os, const Tag &tag) {
      os << "<" << tag.name;
      for (const auto& att : tag.attributes) {
         os << " " << att.first << "=\"" << att.second << "\"";  
      }
      
      if (tag.childrens.size() == 0 && tag.text.size() == 0) {
         os << "/>" << std::endl;
      } else {
         os << ">" << std::endl;
         if (tag.text.length()) {
            os << tag.text << std::endl;
         }

         for (const auto &child : tag.childrens) {
            os << child;
         }
         os << "</" << tag.name << ">" << std::endl;
      }
      return os;
   }
public:
   Tag(const std::string &name, const std::string &text) : name(name), text(text) {}
   Tag(const std::string &name, const std::vector<Tag> childrens) : name(name), childrens(childrens) {}
};

struct P : Tag {
   P(const std::string &text) : Tag{"p", text} {}
   P(std::initializer_list<Tag> childrens) : Tag("p", childrens) {}
};

struct IMG : Tag {
   explicit IMG(const std::string &url)
      : Tag("img", "") 
   {
      attributes.emplace_back(std::make_pair("src", url));
   }
};

int main() {
   std::cout << 
      P {
         IMG {"http://pokemon.com/pikachu.png"},
         IMG {"http://pokemon.com/psyduck.png"}
      };
   return 0;
}
