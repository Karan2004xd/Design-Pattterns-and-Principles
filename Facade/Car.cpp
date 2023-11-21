#include <iostream>

struct Engine{
   void start() {
      std::cout << "Engine Started" << std::endl;
   }

   void stop() {
      std::cout << "Engine Stopped" << std::endl;
   }
};

struct Lights {
   void turn_on() {
      std::cout << "Lights on" << std::endl;
   }

   void turn_off() {
      std::cout << "Lights off" << std::endl;
   }
};

struct Car {
private:
   Engine engine;
   Lights lights;
public:
   void start_car() {
      engine.start();
      lights.turn_on();
      std::cout << "\tThe car is ready to drive" << std::endl;
   }

   void stop_car() {
      engine.stop();
      lights.turn_off();
      std::cout << "\tThe car has stopped" << std::endl;
   }
};

int main() {
   Car car;
   car.start_car();
   std::cout << "\n";
   car.stop_car();
   return 0;
}
