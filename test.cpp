#include <sstream>
#include <iostream>
#include <string>
using namespace std;

struct Flower
{
   virtual string str() = 0;
};

struct Rose : Flower
{
   Rose() {}

   string str() override {
      std::ostringstream oss;
      oss << "A rose";
      return oss.str();
   }
};

struct RedFlower : Flower
{
   Flower &flower;
   RedFlower(Flower &flower) : flower(flower) {}
   string str() override {
      std::ostringstream oss;
      oss << flower.str();
      if (flower.str().find("blue") == std::string::npos) {
         oss << " that is red";
      } else if (flower.str().find("red") == std::string::npos) {
         oss << " and red";
      }
      return oss.str();
   }
};

struct BlueFlower : Flower
{
   Flower &flower;
   BlueFlower(Flower &flower) : flower(flower) {}

   string str() override {
      std::ostringstream oss;
      oss << flower.str();
      if (flower.str().find("red") == std::string::npos) {
         oss << " that is blue";
      } else if (flower.str().find("blue") == std::string::npos) {
         oss << " and blue";
      }
      return oss.str();
   }
};

int main() {
   Rose rose;
   RedFlower red_rose{rose};
   RedFlower red_red_rose{red_rose};
   BlueFlower blue_red_rose{red_rose};
   cout << rose.str() << endl;          // "A rose"
   cout << red_rose.str() << endl;      // "A rose that is red"
   cout << red_red_rose.str() << endl;  // "A rose that is red"
   cout << blue_red_rose.str() << endl; // "A rose that is red and blue"
   return 0;
}
