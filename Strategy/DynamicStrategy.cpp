#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

enum class OutputFormat {
   markdown, html
};

struct ListStrategy {
   virtual void start(std::ostringstream &oss) {}
   virtual void add_list_item(std::ostringstream &oss, const std::string &item) = 0;
   virtual void end(std::ostringstream &oss) {}
};

struct HtmlListStrategy : ListStrategy {
   void start(std::ostringstream &oss) override {
      oss << "<ul>" << std::endl;
   }

   void add_list_item(std::ostringstream &oss, const std::string &item) override {
      oss << "   <li> " << item << " </li>" << std::endl;
   }

   void end(std::ostringstream &oss) override {
      oss << "</ul>\n";
   }
};

struct MarkdownListStrategy : ListStrategy {
   void add_list_item(std::ostringstream &oss, const std::string &item) override {
      oss << "* " << item << std::endl;
   }
};

class TextProcessor {
   std::ostringstream oss;
   std::unique_ptr<ListStrategy> list_strategy;
public:
   void clear() {
      oss.str("");
      oss.clear();
   }
   
   void append_list(const std::vector<std::string> &items) {
      list_strategy->start(oss);
      for (auto &item : items) {
         list_strategy->add_list_item(oss, item);
      }
      list_strategy->end(oss);
   }

   void set_output_fromat(const OutputFormat &format) {
      switch (format) {
         case OutputFormat::html:
            list_strategy = std::make_unique<HtmlListStrategy>();
            break;
         case OutputFormat::markdown:
            list_strategy = std::make_unique<MarkdownListStrategy>();
            break;
      }
   }

   std::string str() const { return oss.str(); }
};

int main() {
   std::vector<std::string> items {"foo", "bar", "baz"};
   
   TextProcessor tp;
   tp.set_output_fromat(OutputFormat::markdown);
   tp.append_list(items);
   std::cout << tp.str();

   tp.clear();
   std::cout << "\n";

   tp.set_output_fromat(OutputFormat::html);
   tp.append_list(items);
   std::cout << tp.str();
   return 0;
}
