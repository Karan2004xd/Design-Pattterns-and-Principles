#ifndef HOT_DRINKS_FACTORY_H_
#define HOT_DRINKS_FACTORY_H_

#include "HotDrinks.h"
struct HotDrinksFactory {
   virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinksFactory {
   std::unique_ptr<HotDrink> make() const override {
      return std::make_unique<Tea>();
   }
};

struct CoffeeFactory : HotDrinksFactory {
   std::unique_ptr<HotDrink> make() const override {
      return std::make_unique<Coffee>();
   }
};
#endif // HOT_DRINKS_FACTORY_H_
