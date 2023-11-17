#include <iostream>
#include <string>
#include <memory>
#include <ostream>

class Address {
   friend class Contact;
   friend class EmployeeFactory;
   std::string street_name, city_name;
   int suite_num;

   Address(const std::string street_name, const std::string city_name, int suite_num) : street_name(street_name), city_name(city_name), suite_num(suite_num) {}
   Address(const Address &other) : street_name(other.street_name), city_name(other.city_name), suite_num(other.suite_num) {}

public:
   friend std::ostream &operator<<(std::ostream &os, const Address &address) {
      os << "Street name: " << address.street_name << ", City name: " << address.city_name << ", Suite number: " << address.suite_num << std::endl;
      return os;
   }
};

class Contact {
public:
   Address *address;
   std::string name;
   Contact(const Contact &other) : name(other.name), address(new Address { *other.address }) {}
   Contact(const std::string name, Address *address) : name(name), address(address) {}
   
   ~Contact() { delete address; }

   friend std::ostream &operator<<(std::ostream &os, const Contact &contact) {
      os << "Name: " << contact.name << "\nAddress: " << *contact.address;
      return os;
   }
};

class EmployeeFactory {
   static std::unique_ptr<Contact> new_employee(const std::string &name, const int suite_num, const Contact &prototype) {
      auto result = std::make_unique<Contact>(prototype);
      result->name = name;
      result->address->suite_num = suite_num;
      return result;
   }

public:
   static std::unique_ptr<Contact> new_main_office_employees(const std::string &name, const int suite_num) {
      static Contact p {"", new Address {"123 East Drive", "London", 0}};
      return new_employee(name, suite_num, p);
   }
};

int main() {
   auto john = EmployeeFactory::new_main_office_employees("John Doe", 123);
   auto jane = EmployeeFactory::new_main_office_employees("Jane Smith", 103);
   std::cout << *john;
   std::cout << "\n" << *jane;
   return 0;
}
