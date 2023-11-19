#include <string>
using namespace std;

struct Render {
   virtual string str(string name) const = 0;
};

struct VectorSquare : Render 
{
   string str(string name) const override {
      return "Drawing " + name + " as lines";
   }
};

struct RasterSquare : Render 
{
   string str(string name) const override {
      return "Drawing " + name + " as pixels";
   }
};

struct Shape
{
   string name;
   Render &render;
   Shape(Render &render) : render(render) {}
   string str() {
      return render.str(name);
   }
};

struct Triangle : Shape
{
   Triangle(Render &render)
      : Shape(render)
   {
      name = "Triangle";
   }
};

struct Square : Shape
{
   Square(Render &render)
      : Shape(render)
   {
      name = "Square";
   }
};
