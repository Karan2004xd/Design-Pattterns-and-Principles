#include <iostream>

struct State {
   virtual void handle() = 0;
};

struct ConcreteStateA : State {
   void handle() override{
      std::cout << "Handling state A..." << std::endl;
   }
};

struct ConcreteStateB : State {
   void handle() override {
      std::cout << "Handling state B..." << std::endl;
   }
};

class Context {
   State *current_state;
public:
   Context() : current_state {nullptr} {}

   void set_state(State *new_state) {
      current_state = new_state;
   }

   void request() {
      if (current_state) {
         current_state->handle();
      } else {
         std::cout << "No state is set" << std::endl;
      }
   }
};

int main() {
   Context context;
   ConcreteStateA stateA;
   ConcreteStateB stateB;

   context.request();

   context.set_state(&stateA);
   context.request();

   context.set_state(&stateA);
   context.request();
   return 0;
}
