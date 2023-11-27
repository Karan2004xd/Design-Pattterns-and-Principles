#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

class Momento {
   double balance;
   std::vector<std::shared_ptr<Momento>> changes;
   int current;
public:
   Momento(double balance) : balance(balance) {
      changes.emplace_back(std::make_shared<Momento>(balance));
      current = 0;
   }
   friend class BankAccount;
};

class BankAccount {
   double balance;
public:
   BankAccount(double balance) : balance(balance) {}
   Momento deposit(double amount) {
      balance += amount;
      return {balance};
   }

   void restore(Momento &momento) {
      balance = momento.balance;
   }


   friend std::ostream &operator<<(std::ostream &os, const BankAccount &obj) {
      return os << "Balance: " << obj.balance;
   }
};

int main() {
   return 0;
}
