#include <iostream>
#include "Observer.h"
#include "Observable.h"

class Person : public Observable<Person> { // observable
   int age;
public:
   Person(int age) : age(age) {}
   int get_age() const {
      return this->age;
   }

   void set_age(int age) {
      if (this->age == age) return ;
      this->age = age;
      notify(*this, "age");
   }
};

class ConsolePersonObserver : public Observer<Person> {
   void field_changed(Person &soruce, const std::string &field_name) override {
      std::cout << "Person's " << field_name << " has changed to ";
      if (field_name == "age") {
         std::cout << soruce.get_age();
      }
      std::cout << "\n";
   }
};

int main() {
   Person person {10};
   ConsolePersonObserver cpo;
   person.subscribe(&cpo);

   person.set_age(11);
   person.set_age(12);

   person.unsubscribe(&cpo);
   person.set_age(13);
   return 0;
}
