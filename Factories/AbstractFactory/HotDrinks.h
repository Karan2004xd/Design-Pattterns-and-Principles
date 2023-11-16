#ifndef HOT_DRINKS_H_
#define HOT_DRINKS_H_

#include <iostream>
#include <memory>

struct HotDrink {
   virtual ~HotDrink() = default;
   virtual void prepare(int) = 0;
};

struct Tea : HotDrink {
   void prepare(int volume) override {
      std::cout << "Take tea bag, boil water, pour " << volume
                << "ml, add some lemon" << std::endl;
   }
};

struct Coffee : HotDrink {
   void prepare(int volume) override {
      std::cout << "Grind some beans, boil water, pour " << volume
                << "ml, add cream, and enjoy" << std::endl;
   }
};
#endif // HOT_DRINKS_H_
