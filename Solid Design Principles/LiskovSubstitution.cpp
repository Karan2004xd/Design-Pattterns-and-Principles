#include <iostream>
   
struct Rectangle {
protected:
   double width, height;
public:
   Rectangle(double width, double height) : width(width), height(height) {}

   virtual void set_width(double width) { this->width = width; }
   virtual void set_height(double height) { this->height = height; }

   double get_width() { return width; }
   double get_height() { return height; }

   int area() { return height * width; }
};

struct Square : public Rectangle {
   Square(double size) : Rectangle(size, size) {}
   
   void set_width(double width) override {
      if (width != this->height) {
         this->width = width;
      } else {
         this->width = this->height = width;
      }
   }

   void set_height(double height) override {
      if (height != this->width) {
         this->height = height;
      } else {
         this->height = this->width = height;
      }
   }
};

void process(Rectangle &obj) {
   int width = obj.get_width();
   obj.set_height(10);

   std::cout << "expected area = " << width * 10 << ", got = " << obj.area() << std::endl;
}

int main() {
   Rectangle r{3, 4};
   process(r); // Output should be: expected area = 30, got = 30

   Square s {5};
   process(s); // Output should be: expected area = 50, got = 50
   return 0;
}
