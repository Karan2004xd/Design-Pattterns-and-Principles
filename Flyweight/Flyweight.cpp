#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <boost/bimap.hpp>

typedef uint32_t key;

struct User {
   User(const std::string &first_name, const std::string &last_name)
      : first_name {add(first_name)}, last_name {add(last_name)} {}

   const std::string &get_first_name() { return names.left.find(first_name)->second; }
   const std::string &get_last_name() { return names.left.find(last_name)->second; }
   
   key first_name, last_name;
protected:
   static boost::bimap<key, std::string> names;
   static key seed;

   static key add(const std::string &name) {
      auto it = names.right.find(name);
      if (it == names.right.end()) {
         key id = ++seed;
         names.insert({seed, name});
         return id;
      }
      return it->second;
   }
};

std::ostream &operator<<(std::ostream &os, User &user) {
   os << "first name: " << user.get_first_name() << " (" << user.first_name << "), last name: " << user.get_last_name() << " (" << user.last_name << ")";
   return os;
}

key User::seed{0};
boost::bimap<key, std::string> User::names {};

int main() {
   User user1 {"John", "Smith"};
   User user2 {"Jane", "Smith"};
   std::cout << user1 << std::endl << user2 << std::endl;
   return 0;
}
