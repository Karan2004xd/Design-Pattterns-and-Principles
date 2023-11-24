#include <iostream>
#include <ostream>
#include <vector>

class BankAccount {
   double balance {0};
   double over_draft {-500};
public:
   void deposit(double amount) {
      balance += amount;
      std::cout << amount << " deposited in the account and the new balance is " << balance << std::endl;
   }

   bool withdraw(double amount) {
      if (balance - amount >= over_draft) {
         balance -= amount;
         std::cout << amount << " withdrawn from the account and the new balance is " << balance << std::endl;
         return true;
      } else {
         std::cout << "Insufficient funds" << std::endl;
         return false;
      }
   }

   friend std::ostream &operator<<(std::ostream &os, const BankAccount &obj) {
      os << "Balance: " << obj.balance << std::endl;
      return os;
   }
};

struct Command {
   bool success;
   virtual void call() = 0;
   virtual void undo() = 0;
};

class BankAccountCommand : Command {
   BankAccount &bank_account;
   double amount;
public:
   enum Action { deposit, withdraw } action;
   BankAccountCommand(BankAccount &bank_account, Action action, double amount)
      : bank_account(bank_account), action(action), amount(amount) 
   {
      success = false;
   }

   void call() override {
      if (action == deposit) {
         bank_account.deposit(amount);
         success = true;
      } else if (action == withdraw) {
         success = bank_account.withdraw(amount);
      }
   }

   void undo() override {
      if (!success) 
         return ;

      if (action == deposit) {
         bank_account.withdraw(amount);
      } else if (action == withdraw) {
         bank_account.deposit(amount);
      }
   }
};

int main() {
   BankAccount ba;
   
   std::cout << ba;

   std::vector<BankAccountCommand> commands {
      BankAccountCommand {ba, BankAccountCommand::deposit, 100},
      BankAccountCommand {ba, BankAccountCommand::withdraw, 200}
   };

   for (auto &i : commands) {
      i.call();
   }

   std::cout << ba;

   for (auto it = commands.rbegin(); it != commands.rend(); it++) {
      it->undo();
   }

   std::cout << ba;
   return 0;
}

