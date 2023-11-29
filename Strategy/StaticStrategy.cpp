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

template<typename LS> class TextProcessor {
   std::ostringstream oss;
   LS list_strategy;
public:
   void clear() {
      oss.str("");
      oss.clear();
   }
   
   void append_list(const std::vector<std::string> &items) {
      list_strategy.start(oss);
      for (auto &item : items) {
         list_strategy.add_list_item(oss, item);
      }
      list_strategy.end(oss);
   }

   std::string str() const { return oss.str(); }
};

int main() {
   TextProcessor<MarkdownListStrategy> tpm;
   tpm.append_list({"foo", "bar", "baz"});
   std::cout << tpm.str();

   std::cout << "\n";

   TextProcessor<HtmlListStrategy> tph;
   tph.append_list({"foo", "bar", "baz"});
   std::cout << tph.str();
   return 0;
}
