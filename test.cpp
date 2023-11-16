#include <string>
using namespace std;

struct Person
{
   int id {-1};
   string name;
   Person(std::string name) {
      this->name = name;
      this->id++;
   }
};

class PersonFactory
{
public:
   Person create_person(const string& name) {
      return {name};
   }
};
