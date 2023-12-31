#include <iostream>
#include <string>
#include <vector>

struct GraphicObject {
   virtual void draw() = 0;
};

struct Circle : GraphicObject {
   void draw() override {
      std::cout << "Circle" << std::endl;
   }
};

struct Group : GraphicObject {
   std::string name;
   std::vector<GraphicObject *> objects;

   Group(const std::string &name) : name(name) {}
   void draw() override {
      std::cout << "Group: " << name.c_str() << " contains ";
      for (auto &i : objects) {
         i->draw();
      }
   }
};

int main() {
   Group root {"root"};
   Circle c1, c2;
   root.objects.push_back(&c1);

   Group sub_group {"sub"};
   sub_group.objects.push_back(&c2);

   root.objects.push_back(&sub_group);
   root.draw();
   return 0;
}
