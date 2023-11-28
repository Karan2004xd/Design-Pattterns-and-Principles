#include <iostream>

class LightSwitch;

struct State {
   virtual void on(LightSwitch *ls);
   virtual void off(LightSwitch *ls);
};

struct OffState : State {
   OffState() {
      std::cout << "Light is turned off" << std::endl;
   }
   void off(LightSwitch *ls) override;
};

struct OnState : State {
   OnState() {
      std::cout << "Light is turned on" << std::endl;
   }
   void on(LightSwitch *ls) override;
};

class LightSwitch {
   State *state;
public:
   LightSwitch() {
      state = new OffState();
   }

   void set_state(State *state) {
      this->state = state;
   }

   void on() {
      state->on(this);
   }

   void off() {
      state->off(this);
   }
};

void OffState::off(LightSwitch *ls) {
   std::cout << "Switching light off..." << std::endl;
   ls->set_state(new OffState());
   delete this;
}

void OnState::on(LightSwitch *ls) {
   std::cout << "Switching light on..." << std::endl;
   ls->set_state(new OnState());
   delete this;
}

int main() {
   LightSwitch ls;
   ls.on();
   ls.off();
   ls.off();
   return 0;
}
