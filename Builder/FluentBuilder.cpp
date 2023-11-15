#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class HtmlBuilder;

class HtmlElement {
   friend class HtmlBuilder;
   std::string name, text;
   std::vector<HtmlElement> elements;
   int indent_size = 2;

   HtmlElement() {}
   HtmlElement(std::string name, std::string text) : name(name), text(text) {}
   
public: 
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

class HtmlBuilder {
   HtmlElement root;

public:
   HtmlBuilder(std::string root_name) {
      root.name = root_name;
   }

   HtmlBuilder &add_child(std::string child_name, std::string chlld_text) {
      root.elements.emplace_back(HtmlElement{child_name, chlld_text});
      return *this;
   }

   std::string str() const { return root.str(); }

   static HtmlBuilder create(std::string root_name) {
      return {root_name};
   }

   HtmlElement build() const { return root; }

   operator HtmlElement() const {
      return root;
   }
};

int main() {
   std::cout << HtmlBuilder::create("ul").add_child("li", "Hello World").add_child("li", "Hi everyone").build().str() << std::endl;
   return 0;
}
