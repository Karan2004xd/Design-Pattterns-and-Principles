#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

enum class State {
   LOCKED,
   OPEN,
   ERROR
};

inline string get_state(State state) {
   string status;
   switch (state) {
      case State::LOCKED:
         status = "LOCKED";
         break;
      case State::OPEN:
         status = "OPEN";
         break;
      case State::ERROR:
         status = "ERROR";
         break;
   }
   return status;
}

class CombinationLock
{
   vector<int> combination;
   int nums;
   public:
   string status;
   ostringstream oss;

   CombinationLock(const vector<int> &combination) : combination(combination) {
      status = get_state(State::LOCKED);
      nums = 0;
   }

   void enter_digit(int digit)
   {
      if (digit == combination[nums] && nums < combination.size() - 1) {
         oss << digit;
         status = oss.str();
      } else if (digit != combination[nums]) {
         status = get_state(State::ERROR);
      } else {
         status = get_state(State::OPEN);
      }
      nums++;
   }
};

int main() {
   CombinationLock cl ({1, 2, 3});
   cout << cl.status << endl;

   cl.enter_digit(1);
   cout << cl.status << endl;

   cl.enter_digit(1);
   cout << cl.status << endl;

   cl.enter_digit(3);
   cout << cl.status << endl;
   return 0;
}
