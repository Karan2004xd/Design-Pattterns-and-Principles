struct Command
{
   enum Action { deposit, withdraw } action;
   int amount{0};
   bool success{false};
};

struct Account
{
   int balance{0};

   void process(Command& cmd)
   {
      if (cmd.action == Command::Action::deposit) {
         balance += cmd.amount;
         cmd.success = true;
      } else if (cmd.action == Command::Action::withdraw) {
         if (cmd.amount <= balance) {
            balance -= cmd.amount;
            cmd.success = true;
         } else {
            cmd.success = false;
         }
      }
   }
};
