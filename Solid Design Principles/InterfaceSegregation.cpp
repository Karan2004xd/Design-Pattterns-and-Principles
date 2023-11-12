#include <iostream>

struct Document {

};

struct IPrinter {
   virtual void print(Document &doc) = 0;
};

struct IScanner {
   virtual void scan(Document &doc) = 0;
};

struct Printer : IPrinter {
   void print(Document &doc) override {
      std::cout << "Printer print func" << std::endl;
   }
};

struct Scanner : IScanner {
   void scan(Document &doc) override {
      std::cout << "Scanner scan func" << std::endl;
   }
};

struct Machine : IPrinter, IScanner {
   void print(Document &doc) override {
      std::cout << "Machine print func" << std::endl;
   }

   void scan(Document &doc) override {
      std::cout << "Machine scan func" << std::endl;
   }
};

int main() {
   Document d;

   Printer p;
   p.print(d);

   std::cout << "\n";

   Scanner s;
   s.scan(d);

   std::cout << "\n";

   Machine m;
   m.print(d);
   m.scan(d);
   return 0;
}
