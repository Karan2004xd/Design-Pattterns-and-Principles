#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct HtmlElement {
   std::string name, text;
   std::vector<HtmlElement> elements;
   const int indent_size = 2;

   HtmlElement(std::string name, std::string text) : name(name), text(text) {}
   HtmlElement() {}
   
   std::string str(int indent = 0) const {
      std::ostringstream oss;
      std::string i(indent_size * indent, ' ');
      oss << i << "<" << name << ">" << std::endl;

      if (text.size() > 0) {
         oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;
      }

      for (const auto &e : elements) {
         oss << e.str(indent + 1);
      }

      oss << i << "</" << name << ">" << std::endl;
      return oss.str();
   }
};

struct HtmlBuilder {
   HtmlElement root;
   HtmlBuilder(std::string root_name) {
      root.name = root_name;
   }

   void add_child(std::string child_name, std::string child_text) {
      root.elements.emplace_back(HtmlElement{child_name, child_text});
   }

   std::string str() const { return root.str(); }
};

int main() {
   HtmlBuilder builder {"ul"};
   builder.add_child("li", "hello");
   builder.add_child("li", "world");
   std::cout << builder.str() << std::endl;
   return 0;
}
