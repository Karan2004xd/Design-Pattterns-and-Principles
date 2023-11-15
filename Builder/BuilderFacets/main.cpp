#include <iostream>
#include "Header Files/PersonBuilder.h"
#include "Header Files/PersonJobBuilder.h"
#include "Header Files/PersonAddressBuilder.h"
#include "Header Files/Person.h"

int main() {
   Person p = Person::create()
      .lives().at("123 London Road")
              .with("380050")
              .in("Ahemdabad")
      .works().at("Pragma Soft")
              .as_a("Software Engineer")
              .earning(100000);

   std::cout << p << std::endl;
   return 0;
}
