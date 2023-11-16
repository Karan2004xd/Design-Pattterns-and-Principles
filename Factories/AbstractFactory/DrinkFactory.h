#ifndef DRINK_FACTORY_H_
#define DRINK_FACTORY_H_

#include "HotDrinks.h"
#include "HotDrinksFactory.h"
#include <map>

class DrinkFactory {
public:
   enum class HotDrinkType { tea, coffee };
private:
   std::map<HotDrinkType, std::unique_ptr<HotDrinksFactory>> hot_drink_factories;
public:
   DrinkFactory() {
      hot_drink_factories[HotDrinkType::tea] = std::make_unique<TeaFactory>();
      hot_drink_factories[HotDrinkType::coffee] = std::make_unique<CoffeeFactory>();
   }

   std::unique_ptr<HotDrink> make_drink(const HotDrinkType type, int volume) {
      auto drink = hot_drink_factories[type]->make();
      drink->prepare(volume);
      return drink;
   }
};
#endif // DRINK_FACTORY_H_
