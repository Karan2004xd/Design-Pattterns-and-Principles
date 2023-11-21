#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

struct Shape {
   virtual std::string str() const = 0;
};

struct Circle : Shape {
   float radius;
   Circle() {}
   Circle(float radius) : radius(radius) {}

   void resize() { radius *= 2; }

   std::string str() const override {
      std::ostringstream oss;
      oss << "A circle with radius " << radius;
      return oss.str();
   }
};

struct Square : Shape {
   float side;
   Square() {}
   Square(float side) : side(side) {}

   std::string str() const override {
      std::ostringstream oss;
      oss << "A square with side " << side;
      return oss.str();
   }
};

template <typename T> struct ColoredShape : T {
   std::string color;
   ColoredShape() {}

   template <typename...Args>
   ColoredShape(const std::string &color, Args ...args)
      : T(std::forward<Args>(args)...), color(color) {}

   std::string str() const override {
      std::ostringstream oss;
      oss << T::str() << " has the color " << color;
      return oss.str();
   }
};

template <typename T> struct TransparentShape : T {
   uint8_t transparency;

   template <typename...Args>
   TransparentShape(uint8_t transparency, Args ...args)
      : T(std::forward<Args>(args)...), transparency(transparency) {}

   std::string str() const override {
      std::ostringstream oss;
      oss << T::str() << " has "
          << static_cast<float>(transparency) / 255.f * 100.f
          << "% transparency";
      return oss.str();
   }
};

int main() {
   ColoredShape<Circle> green_color { "green", 5 };
   green_color.resize();
   std::cout << green_color.str() << std::endl;

   TransparentShape<ColoredShape<Square>> bis { 0, "blue", 10 };
   bis.side = 20;
   std::cout << bis.str() << std::endl;
   return 0;
}
