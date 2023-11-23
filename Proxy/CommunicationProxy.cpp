#include <iostream>
#include <string>

struct Image {
   virtual void draw() = 0;
};

struct Bitmap : Image {
   void draw() override {
      std::cout << "Drawing bitmap" << std::endl;
   }
};

struct Proxy : Image {
   Proxy() : bmp(new Bitmap()) {}
   
   void draw() override {
      if (this->check_access()) {
         bmp->draw();
         this->Log();
      }
   }

   ~Proxy() { delete bmp; }
private:
   Bitmap *bmp {nullptr};

   bool check_access() const {
      std::cout << "Proxy: Checking access..." << std::endl;;
      return true;
   }

   void Log() const {
      std::cout << "Proxy: Logging the time of access" << std::endl;
   }
};

int main() {
   Proxy bitmap_proxy;
   bitmap_proxy.draw();
}
