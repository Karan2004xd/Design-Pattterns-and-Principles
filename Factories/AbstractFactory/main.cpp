#include "DrinkFactory.h"
#include <iostream>

int main() {
   DrinkFactory df;
   df.make_drink(DrinkFactory::HotDrinkType::coffee, 200);
   return 0;
}
