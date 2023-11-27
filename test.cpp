#include <vector>
#include <iostream>

struct Participant;

struct Mediator {
   std::vector<Participant*> participants;
};

struct Participant 
{
   int value{0};
   Mediator& mediator;

   Participant(Mediator &mediator) : mediator(mediator)
   {
      mediator.participants.push_back(this);
   }

   void say(int value)
   {
      for (auto &i : mediator.participants) {
         if (i != this) {
            i->value += value;
         }
      }
   }
};

int main() {
   Mediator m;
   Participant john {m};
   Participant jane {m};

   john.say(3);
   std::cout << "John value: " << john.value << ", Jane value: " << jane.value << std::endl;

   jane.say(2);
   std::cout << "John value: " << john.value << ", Jane value: " << jane.value << std::endl;
   return 0;
}

