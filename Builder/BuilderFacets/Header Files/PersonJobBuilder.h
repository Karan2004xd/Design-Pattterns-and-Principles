#ifndef PERSON_JOB_BUILDER_H_
#define PERSON_JOB_BUILDER_H_

#include "PersonBuilder.h"
class PersonJobBuilder : public PersonBuilderBase {
public:
   PersonJobBuilder(Person &person) : PersonBuilderBase(person) {}

   PersonJobBuilder &at(std::string company_name) { 
      person.company_name = company_name;
      return *this;
   }

   PersonJobBuilder &as_a(std::string position) {
      person.position = position;
      return *this;
   }

   PersonJobBuilder &earning(double annual_income) {
      person.annual_income = annual_income;
      return *this;
   }
};
#endif // PERSON_JOB_BUILDER_H_
