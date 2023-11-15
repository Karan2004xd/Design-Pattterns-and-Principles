#ifndef PERSON_BUILDER_H_
#define PERSON_BUILDER_H_

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
protected:
   Person &person;
public:
   PersonBuilderBase(Person &person);
   PersonAddressBuilder lives() const;
   PersonJobBuilder works() const;

   operator Person() const {
      return std::move(person);
   }
};

class PersonBuilder : public PersonBuilderBase {
   Person person;
public:
   PersonBuilder();
};
#endif // PERSON_BUILDER_H_
