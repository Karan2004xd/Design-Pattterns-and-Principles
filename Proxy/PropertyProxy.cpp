#include <iostream>

template<typename T> struct Property {
   T value;

   Property(T value) {
      *this = value;
   }

   operator T() {
      return value;
   }

   T operator=(T new_value) {
      std::cout << "Assignment!" << std::endl;
      return value = new_value;
   }
};

struct Creature {
   Property<int> strength {10};
   Property<int> agility {5};
};

int main() {
   Creature c;
   c.strength = 15;
   int x = c.agility;
   return 0;
}
