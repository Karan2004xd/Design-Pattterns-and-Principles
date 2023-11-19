#include <iostream>
#include <string>

struct Renderer {
   virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer {
   void render_circle(float x, float y, float radius) override {
      std::cout << "Drawing a vector circle of radius of radius " << radius << std::endl;
   }
};

struct RastorRender : Renderer {
   void render_circle(float x, float y, float radius) override {
      std::cout << "Rasterizing a circle of radius " << radius << std::endl;
   }
};

struct Shape {
protected:
   Renderer &render;
   Shape(Renderer &render) : render(render) {}

   virtual void draw() = 0;
   virtual void resize(float factor) = 0;
};

struct Circle : Shape {
private:
   float x, y, radius;
public:
   Circle(Renderer &render, float x, float y, float radius) : Shape(render) ,x(x), y(y), radius(radius) {}

   void draw() override {
      render.render_circle(x, y, radius);
   }

   void resize(float factor) override {
      radius *= 2;
   }
};

int main() {
   RastorRender rr;
   Circle raster_circle {rr, 5, 6, 10};
   raster_circle.draw();
   raster_circle.resize(2);
   raster_circle.draw();
   return 0;
}
