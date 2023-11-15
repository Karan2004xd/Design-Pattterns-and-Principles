#ifndef PERSON_ADDRESS_BUILDER_H_
#define PERSON_ADDRESS_BUILDER_H_

#include "PersonBuilder.h"
#include <string>
class PersonAddressBuilder : public PersonBuilderBase {
public:
   PersonAddressBuilder(Person &person) : PersonBuilderBase(person) {}

   PersonAddressBuilder &at(std::string street_name) {
      person.street_name = street_name;
      return *this;
   }

   PersonAddressBuilder &with(std::string postal_code) {
      person.postal_code = postal_code;
      return *this;
   }

   PersonAddressBuilder &in(std::string city) {
      person.city = city;
      return *this;
   }
};
#endif // PERSON_ADDRESS_BUILDER_H_
