#include <iostream>
#include <string>
#include <tuple>
#include <vector>

enum class Relations { parent, child, sibling };

struct Person {
   std::string name;
};

struct RelationshipBrowser {
   virtual std::vector<Person> find_all_children_of(const std::string &name) = 0;
};

struct Relationships : RelationshipBrowser { // low-level module
   std::vector<std::tuple<Person, Relations, Person>> relationships;

   void add_child_parent(const Person &parent, const Person &child) {
      relationships.push_back({parent, Relations::parent, child});
      relationships.push_back({child, Relations::child, parent});
   }
   
   std::vector<Person> find_all_children_of(const std::string &name) override {
      std::vector<Person> result;
      for (auto && [first, rel, second] : relationships) {
         if (name == first.name && rel == Relations::parent) {
            result.push_back(second);
         }
      }
      return result;
   }
};

struct Research { // high-level module
   Research (RelationshipBrowser &browser, const std::string name) {
      for (auto &i : browser.find_all_children_of(name)) {
         std::cout << name << " has a child called " << i.name << std::endl;
      }
   }
};

int main() {
   Person john {"John"};
   Person child_1 {"James"}, child_2 {"Chris"};
   Relationships relationships;
   relationships.add_child_parent(john, child_1);
   relationships.add_child_parent(john, child_2);
   
   Research _(relationships, "John");
   return 0;
}
