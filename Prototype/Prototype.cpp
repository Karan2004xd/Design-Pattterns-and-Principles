#include <iostream>
#include <ostream>
#include <string>

struct Address {
   std::string street_name, city;
   int suite;
   Address(const std::string street_name, const std::string city, int suite) : street_name(street_name), city(city), suite(suite) {}
   Address(const Address &other) : street_name(other.street_name), city(other.city), suite(other.suite) {}

   friend std::ostream &operator<<(std::ostream &os, const Address &address) {
      os << "Street name: " << address.street_name << ", City name: " << address.city << ", Suite number: " << address.suite;
      return os;
   }
};

struct Contact {
   std::string name;
   Address *address;

   Contact(const std::string name, Address *address) : name(name), address(address) {}
   Contact(const Contact &other) : name(other.name), address(new Address { *other.address }) {}
   
   friend std::ostream &operator<<(std::ostream &os, const Contact &contact) {
      os << "Name: " << contact.name << "\nAddress: " << *contact.address << std::endl;
      return os;
   }

   ~Contact() {
      delete address;
   }
};

int main() {
   Contact john {"John Doe", new Address {"123 East Dr", "London", 123}};
   /* Contact jane {"Jane Smith", new Address {"123 East Dr", "London", 103}}; */
   Contact jane {john};
   jane.name = "Jane Smith";
   jane.address->suite = 103;
   std::cout << john << std::endl;
   std::cout << jane;
   return 0;
}
