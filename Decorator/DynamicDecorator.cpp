#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

struct Shape {
   virtual std::string str() const = 0;
};

struct Circle : Shape {
   float radius;
   Circle() {}
   Circle(float radius) : radius(radius) {}

   void resize() {
      radius *= 2;
   }

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
      oss << "A Square with side " << side;
      return oss.str();
   }
};

struct ColoredShape : Shape {
   Shape &shape;
   std::string color;
   ColoredShape(Shape &shape, const std::string &color) : color(color), shape(shape) {}

   std::string str() const override {
      std::ostringstream oss;
      oss << shape.str() << " has the color " << color;
      return oss.str();
   }
};

struct TransparentShape : Shape {
   Shape &shape;
   uint8_t transparency;

   TransparentShape(Shape &shape, uint8_t transparency) : shape(shape), transparency(transparency) {}

   std::string str() const override {
      std::ostringstream oss;
      oss << shape.str() << " has "
          << static_cast<float>(transparency) / 255.f * 100.f
          << "% transparency";
      return oss.str();
   }
};

int main() {
   Circle cirlce {10.2};
   ColoredShape colored_circle {cirlce, "red"};
   TransparentShape transparent_colored_cirlce {colored_circle, 51};
   std::cout << transparent_colored_cirlce.str() << std::endl;
}
