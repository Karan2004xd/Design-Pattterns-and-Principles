#include <ostream>
#include <iostream>
#include <cmath>

struct Point {
   float x, y;
   Point(float x, float y) : x(x), y(y) {}

   friend std::ostream &operator<<(std::ostream &os, const Point &point) {
      return os << "Point 1: " << point.x << ", Point 2: " << point.y << std::endl;
   }
};

struct PointFactory {
   static Point new_cartesian(float x, float y) {
      return {x, y};
   }

   static Point new_polar(float x, float y) {
      return { x * std::cos(y), y * std::sin(y) };
   }
};

int main() {
   std::cout << PointFactory::new_polar(4, 3);
   return 0;
}
