#ifndef PERSON_H_
#define PERSON_H_

#include <ostream>
#include <string>

class PersonBuilder;

class Person {
   std::string street_name, postal_code, city;
   std::string company_name, position;
   double annual_income {0};
public:
   static PersonBuilder create();
   
   friend class PersonAddressBuilder;
   friend class PersonJobBuilder;
   friend class PersonBuilder;

   friend std::ostream &operator<<(std::ostream &os, Person &person) {
      return os
      << "Street name: " << person.street_name
      << "\nPostal Code: " << person.postal_code
      << "\nCity name: " << person.city << std::endl
      << "\nCompany name: " << person.company_name
      << "\nPosition at the company: " << person.position
      << "\nAnnual income: " << person.annual_income;
   }
};
#endif // PERSON_H_
