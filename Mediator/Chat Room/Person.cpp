#include "Person.h"

Person::Person(const std::string &name) : name(name) {}

void Person::say(const std::string &message) const {

}

bool Person::operator==(const Person &rhs) const {
   return rhs.name == name;
}

bool Person::operator!=(const Person &rhs) const {
   return rhs.name != name;
}
