// make sure that you have the boost library installed in your system
// if you are using a command line for compiling this program than make sure to include the -lboost_serialization or else it might not compile

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <memory>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/access.hpp>

class Address {
public:
   std::string street_name, city_name;
   int suite_num;

   Address() {}
   friend class boost::serialization::access;

   template <class archive>
      void serialize(archive &ar, const unsigned version) {
         ar & street_name;
         ar & city_name;
         ar & suite_num;
      }

   Address(const std::string &street_name, const std::string &city_name, const int suite_num)
      : street_name(street_name), city_name(city_name), suite_num(suite_num) {}
   Address(const Address &other)
      : street_name(other.street_name), city_name(other.city_name), suite_num(other.suite_num) {}

   friend std::ostream &operator<<(std::ostream &os, const Address &address) {
      os << "Street Name: " << address.street_name << ", City Name: " << address.city_name << ", Suite number: " << address.suite_num;
      return os;
   }
};

class Contact {
public:
   std::string name;
   Address *address;

   ~Contact() { delete address; }

   Contact() {};
   friend class boost::serialization::access;

   template <class archive>
      void serialize(archive &ar, const unsigned version) {
         ar & name;
         ar & address;
      }
   Contact(const std::string &name, Address *address)
      : name(name), address(address) {}
   Contact(const Contact &other)
      : name(other.name), address( new Address { *other.address }) {}

   friend std::ostream &operator<<(std::ostream &os, const Contact &contact) {
      os << "Name: " << contact.name << "\nAddress: " << *contact.address << std::endl;
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
      static Contact p {"", new Address {"123 London Drive", "London", 0}};
      return new_employee(name, suite_num, p);
   }
};

int main() {
   auto clone = [](const Contact &c) {
      std::ostringstream oss;
      boost::archive::text_oarchive oa(oss);
      oa << c;
      std::string s {oss.str()};
      std::cout << s << std::endl;

      std::istringstream iss(s);
      boost::archive::text_iarchive ia(iss);
      Contact result;
      ia >> result;
      return result;
   };

   auto john = EmployeeFactory::new_main_office_employees("John Doe", 123);
   auto jane = clone(*john);
   jane.name = "Jane Smith";
   std::cout << "\n" << *john << "\n" << jane;
   return 0;
}
