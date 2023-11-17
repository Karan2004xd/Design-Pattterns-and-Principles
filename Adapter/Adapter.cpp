#include <iostream>

class CelsiusTemperature {
   double temperature;
public:
   CelsiusTemperature(double temperature) : temperature(temperature) {}
   double get_celsius_temp() { return temperature; }
};

class FahrenheitTempearature {
public:
   virtual double get_fahrenhiet_temp() = 0;
};

class CelsiusToFahrenheitAdapter : public FahrenheitTempearature {
   CelsiusTemperature temp;
public:
   CelsiusToFahrenheitAdapter(const CelsiusTemperature &other) : temp(other) {}
   double get_fahrenhiet_temp() override {
      return (temp.get_celsius_temp() * 9 / 5) + 32;
   }
};

int main() {
   CelsiusTemperature celsius {25.0};
   CelsiusToFahrenheitAdapter adapter {celsius};
   std::cout << "temperature in fahrenheit: " << adapter.get_fahrenhiet_temp() << std::endl;
   return 0;
}
