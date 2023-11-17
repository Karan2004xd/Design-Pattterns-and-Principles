#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>

class SingletonDatabase {
   std::map<std::string, int> cities;
   
   SingletonDatabase() {
      std::ifstream ifs("./cites.txt");
      
      std::string line1, line2;
      while (std::getline(ifs, line1)) {
         std::getline(ifs, line2);
         int population = boost::lexical_cast<int>(line2);
         cities[line1] = population;
      }
      ifs.close();
   }
public:
   SingletonDatabase(SingletonDatabase const &) = delete;
   void operator=(SingletonDatabase const &) = delete;

   static SingletonDatabase &get() {
      static SingletonDatabase db;
      return db;
   }

   int get_population(const std::string &city_name) {
      return cities[city_name];
   }

   void set_population(const std::string &city_name, const int population) {
      if (cities[city_name]) {
         cities[city_name] = population;
      } else {
         std::cout << "The name was not found" << std::endl;
      }
   }
};
int main() {
   std::string city_name {"New York City"};
   std::cout << city_name << " has a total population of " << SingletonDatabase::get().get_population(city_name) << std::endl;
   SingletonDatabase::get().set_population(city_name, 10000);
   std::cout << city_name << " has a total population of " << SingletonDatabase::get().get_population(city_name) << std::endl;
   return 0;
}

