#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct HtmlElement {
   std::string name, text;
   std::vector<HtmlElement> elements;
   int indent_size = 2;

   HtmlElement() {}
   HtmlElement(std::string name, std::string text) : name(name), text(text) {}

   
};

struct HtmlBuilder {

};

int main() {
   return 0;
}
