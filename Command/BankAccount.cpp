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

   void withdraw(double amount) {
      if (balance - amount >= over_draft) {
         balance -= amount;
         std::cout << amount << " withdrawn from the account and the new balance is " << balance << std::endl;
      } else {
         std::cout << "Insufficient funds" << std::endl;
      }
   }

   friend std::ostream &operator<<(std::ostream &os, const BankAccount &obj) {
      os << "Balance: " << obj.balance << std::endl;
      return os;
   }
};

struct Command {
   virtual void call() = 0;
};

class BankAccountCommand : Command {
   BankAccount &bank_account;
   double amount;
public:
   enum Action { deposit, withdraw } action;
   BankAccountCommand(BankAccount &bank_account, Action action, double amount)
      : bank_account(bank_account), action(action), amount(amount) {}

   void call() override {
      if (action == deposit) {
         bank_account.deposit(amount);
      } else if (action == withdraw) {
         bank_account.withdraw(amount);
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
   return 0;
}
