#include <ostream>
#include <iostream>
#include <cmath>

class Point {
   float x, y;
   Point(float x, float y) : x(x), y(y) {}

public:
   static Point new_cartesian(float x, float y) {
      return {x, y};
   }

   static Point new_polar(float x, float y) {
      return { x * std::cos(y), y * std::sin(y) };
   }
   friend std::ostream &operator<<(std::ostream &os, const Point &point) {
      return os << "Point 1: " << point.x << ", Point 2: " << point.y << std::endl;
   }
};

int main() {
   std::cout << Point::new_polar(3, 4);
   return 0;
}
