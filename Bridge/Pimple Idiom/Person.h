#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <iostream>

class Person {
public:
   std::string name;
   class PersonImlp;
   PersonImlp *pimpl;

   Person(const std::string &);
   ~Person();
   void greet() const;
};
#endif // PERSON_H_
