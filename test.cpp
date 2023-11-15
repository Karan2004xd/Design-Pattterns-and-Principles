#include <iostream>
#include <string>
#include <ostream>
#include <utility>
#include <vector>
using namespace std;

class CodeBuilder
{
   string type, class_name;
   vector<pair<string, string>> names;
   public:
   CodeBuilder(const string& class_name) : class_name(class_name) {}

   CodeBuilder& add_field(const string& name, const string& type)
   {
      names.emplace_back(make_pair(name, type));
      return *this;
   }

   friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
   {
      os << "class " << obj.class_name << "\n"
         << "{\n";
      for (auto &name : obj.names) {
         os << string(2, ' ') << name.second << " " << name.first << ";\n";
      }
      os << "};\n";
      return os;
   }
};

int main() {
   auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
   cout << cb;
   return 0;
}
