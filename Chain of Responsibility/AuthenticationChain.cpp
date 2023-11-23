#include <iostream>
#include <string>

struct Authentication {
   Authentication *next {nullptr};
   virtual bool authenticate() = 0;
   void next_authentication(Authentication *auth) { next = auth; }
};

struct Username : Authentication {
   std::string name;
   Username(std::string name) : name(name) {}

   bool is_valid_user_name() { return name == "user"; }

   bool authenticate() override {
      if (!is_valid_user_name()) {
         std::cout << "Invalid user name" << std::endl;
         return false;
      } else if (next) {
         return next->authenticate();
      }
      return true;
   }
};

struct Password : Authentication {
   std::string password;
   Password(std::string password) : password(password) {}

   bool is_valid_password() { return password == "hello"; }

   bool authenticate() override {
      if (!is_valid_password()) {
         std::cout << "Invalid password" << std::endl;
         return false;
      } else if (next) {
         return next->authenticate();
      } 
      std::cout << "Login successfull" << std::endl;
      return true;
   }
};

int main() {
   Authentication *login { new Username("user") };
   login->next_authentication(new Password("hello"));
   login->authenticate();
   return 0;
}
