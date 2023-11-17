#include <iostream>
#include <string>
#include <memory>
#include <ostream>

class Address {
   friend class Contact;
   std::string street_name, city_name;
   int suite_num;

   Address(const Address &other) : street_name(other.street_name), city_name(other.city_name), suite_num(other.suite_num) {}

public:
   friend std::ostream &operator<<(std::ostream &os, const Address &address) {
      os << "Street name: " << address.street_name << ", City name: " << address.city_name << ", Suite number: " << address.suite_num << std::endl;
      return os;
   }
};

class Contact {
   friend class EmployeeFactory;
   Address *address;
   std::string name;
   Contact(const Contact &other) : name(other.name), address(new Address { *other.address }) {}
   
   ~Contact() { delete address; }
public:
   friend std::ostream &operator<<(std::ostream &os, const Contact &contact) {
      os << "Name: " << contact.name << "\nAddress: " << contact.address << std::endl;
      return os;
   }
};

class EmployeeFactory {
};
