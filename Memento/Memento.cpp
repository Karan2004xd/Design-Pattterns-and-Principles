#include <iostream>
#include <ostream>

class Memento {
   double balance;
public:
   Memento(double balance) : balance(balance) {}
   friend class BankAccount;
};

class BankAccount {
   double balance;
public:
   BankAccount(double balance) : balance(balance) {}
   Memento deposit(double amount) {
      balance += amount;
      return {balance};
   }

   void restore(Memento &memento) {
      balance = memento.balance;
   }

   friend std::ostream &operator<<(std::ostream &os, const BankAccount &obj) {
      return os << "Balance: " << obj.balance;
   }
};

int main() {
   BankAccount ba {100};
   std::cout << ba << std::endl;

   auto m1 = ba.deposit(30);
   auto m2 = ba.deposit(20);

   ba.deposit(50);
   std::cout << ba << std::endl;

   ba.restore(m1);
   std::cout << ba << std::endl;

   ba.restore(m2);
   std::cout << ba << std::endl;
   return 0;
}
