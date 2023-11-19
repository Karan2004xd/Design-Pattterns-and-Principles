#include "Person.h"

class Person::PersonImlp {
public:
   void greet(const Person *p) const;
};

Person::Person(const std::string &name) : pimpl(new PersonImlp), name(name) {}
Person::~Person() { delete pimpl; }

void Person::PersonImlp::greet(const Person *p) const {
   std::cout << "Hello my name is " << p->name << std::endl;
}

void Person::greet() const {
   pimpl->greet(this);
}
