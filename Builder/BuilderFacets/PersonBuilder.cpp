#include "./Header Files/PersonBuilder.h"
#include "Header Files/PersonAddressBuilder.h"
#include "Header Files/PersonJobBuilder.h"

PersonBuilder::PersonBuilder() : PersonBuilderBase(person) {}
PersonBuilderBase::PersonBuilderBase(Person &person) : person(person) {}

PersonAddressBuilder PersonBuilderBase::lives() const {
   return PersonAddressBuilder {person};
}

PersonJobBuilder PersonBuilderBase::works() const {
   return PersonJobBuilder {person};
}
