#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

class Memento {
   double balance;
   int current;
public:
   Memento(double balance) : balance(balance) {}
   friend class BankAccount;
};

class BankAccount {
   double balance;
   std::vector<std::shared_ptr<Memento>> changes;
   int current;
public:
   BankAccount(double balance) : balance(balance) {
      changes.emplace_back(std::make_shared<Memento>(balance));
      current = 0;
   }

   std::shared_ptr<Memento> deposit(double amount) {
      balance += amount;
      auto mement = std::make_shared<Memento>(balance);
      changes.emplace_back(mement);
      current++;
      return mement;
   }

   void restore(const std::shared_ptr<Memento> &mement) {
      if (mement) {
         balance = mement->balance;
         changes.push_back(mement);
         current = changes.size() - 1;
      }
   }

   std::shared_ptr<Memento> undo() {
      if (current > 0) {
         current--;
         auto mement = changes[current];
         balance = mement->balance;
         return mement;
      }
      return {};
   }

   std::shared_ptr<Memento> redo() {
      if (current + 1 < changes.size()) {
         current++;
         auto mement = changes[current];
         balance = mement->balance;
         return mement;
      }
      return {};
   }

   friend std::ostream &operator<<(std::ostream &os, const BankAccount &obj) {
      return os << "Balance: " << obj.balance;
   }
};

int main() {
   BankAccount ba {100};
   ba.deposit(50);
   ba.deposit(25);
   std::cout << ba << std::endl;

   auto m1 = ba.deposit(60);
   std::cout << ba << std::endl;

   ba.undo();
   std::cout << "Undo 1: " << ba << std::endl;
   ba.undo();
   std::cout << "Undo 2: " << ba << std::endl;
   ba.redo();
   std::cout << "Redo: " << ba << std::endl;

   ba.restore(m1);
   std::cout << ba << std::endl;

   return 0;
}
