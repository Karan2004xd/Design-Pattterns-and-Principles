#include <iostream>
#include <string>

struct Image {
   virtual void draw() = 0;
};

struct Bitmap : Image {
   Bitmap(const std::string &filename) {
      std::cout << "Loading bitmap from " << filename << std::endl;
   }
   
   void draw() override {
      std::cout << "Drawing bitmap" << std::endl;
   }
};

struct BitmapProxy : Image {
   BitmapProxy(const std::string &filename) : filename(filename) {}

   void draw() override {
      if (!bmp) {
         bmp = new Bitmap(filename);
      }
      bmp->draw();
   }
private:
   Bitmap *bmp {nullptr};
   std::string filename;
};

int main() {
   BitmapProxy bp {"pokemon.png"};
   bp.draw();
   return 0;
}
