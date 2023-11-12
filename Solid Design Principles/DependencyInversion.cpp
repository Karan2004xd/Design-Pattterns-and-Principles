#include <iostream>
#include <string>
#include <tuple>
#include <vector>

enum class Relations { parent, child, sibling };

struct Person {
   std::string name;
};

struct Relationships { // low-level module
   std::vector<std::tuple<Person, Relations, Person>> relationships;
   
   void add_child_parent(const Person &parent, const Person &child) {
      relationships.push_back({parent, Relations::parent, child});
      relationships.push_back({child, Relations::child, parent});
   }
};

struct Research { // high-level module
   Research(const Relationships &obj) {
      auto &relations = obj.relationships;
      for (auto && [first, rel, second] : relations) {
      }
   }
};

int main() {
   return 0;
}
