#include <initializer_list>
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
   virtual void call() = 0;
   virtual void undo() = 0;
   bool success;
};

struct BankAccountCommand : Command {
   BankAccount &bank_account;
   double amount;

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

struct CompositeBankAccount : std::vector<BankAccountCommand>, Command {
   CompositeBankAccount(const std::initializer_list<BankAccountCommand> &items) : vector(items) {}

   void call() override {
      for (auto &i : *this) {
         i.call();
      }
   }

   void undo() override {
      for (auto it = rbegin(); it != rend(); it++) {
         it->undo();
      }
   }
};

struct DependentCompositeCommand : CompositeBankAccount {
   DependentCompositeCommand(const std::initializer_list<BankAccountCommand> &items) : CompositeBankAccount(items) {}

   void call() override {
      bool ok = true;
      for (auto &i : *this) {
         if (ok) {
            i.call();
            ok = i.success;
         } else {
            i.success = false;
         }
      }
   }
};

struct MoneyTransferCommand : DependentCompositeCommand {
   MoneyTransferCommand(BankAccount &from, BankAccount &to, double amount)
      : DependentCompositeCommand(
         { BankAccountCommand {from, BankAccountCommand::withdraw, amount}, BankAccountCommand {to, BankAccountCommand::deposit, amount} }
      ) {}
};

int main() {
   BankAccount b1, b2;
   b1.deposit(100);

   std::cout << b1 << b2 << std::endl;;

   MoneyTransferCommand mtc {b1, b2, 50};
   mtc.call();

   std::cout << "\n" << b1 << b2 << std::endl;

   mtc.undo();

   std::cout << "\n" << b1 << b2;
   return 0;
}
