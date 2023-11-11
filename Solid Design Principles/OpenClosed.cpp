#include <iostream>
#include <string>
#include <vector>

enum class Color { red, green, blue };
enum class Size { large, medium, small };

struct Product {
   std::string name;
   Color color;
   Size size;
};

template<typename T> struct Specification {
   virtual bool is_satisfied(T *item) = 0;
};

template<typename T> struct Filter {
   virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> *) = 0;
};

struct ProductFilter : Filter<Product> {
   std::vector<Product *> filter(std::vector<Product *> items, Specification<Product> *spec) override {
      std::vector<Product *> result;
      for (auto &i : items) {
         if (spec->is_satisfied(i)) {
            result.push_back(i);
         }
      }
      return result;
   }
};

struct ColorSpecification : Specification<Product> {
   Color color;

   ColorSpecification(Color color) : color(color) {}

   bool is_satisfied(Product *item) override {
      return color == item->color;
   }
};

struct SizeSpecification : Specification<Product> {
   Size size;

   SizeSpecification(Size size) : size(size) {}

   bool is_satisfied(Product *item) override {
      return size == item->size;
   }
};

template<typename T> struct MultipleSpecification : Specification<T> {
   std::vector<Specification<T> *> spec;
   MultipleSpecification(std::vector<Specification<T> *> spec) : spec(spec) {}

   bool is_satisfied(T *item) override {
      for (auto &i : spec) {
         if (!i->is_satisfied(item)) {
            return false;
         }
      }
      return true;
   }
};

int main() {
   Product p1 { "Apple", Color::red, Size::small };
   Product p2 { "Tree", Color::green, Size::large };
   Product p3 { "Strawberry", Color::red, Size::small };

   std::vector<Product *> items {&p1, &p2, &p3};
   ProductFilter pf;

   ColorSpecification red {Color::red};
   SizeSpecification small {Size::small};

   std::vector<Specification<Product> *> spec { &red, &small };
   MultipleSpecification<Product> red_and_small {spec};

   for (auto &i : pf.filter(items, &red_and_small)) {
      std::cout << "Name: " << i->name << ", who's color is red and size is small" << std::endl;
   }
   return 0;
}
