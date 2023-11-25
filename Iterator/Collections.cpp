#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

template <typename T> struct Iterator;
template <typename T> class ConcreteIterator;

template <typename T> struct Collections {
   virtual Iterator<T> *new_iterator() = 0;
};

template <typename T> class ConcreteCollections : public Collections<T> {
   std::vector<T> collections;
   int iteration_steps;

public:
   ConcreteCollections(std::initializer_list<T> list, int iteration_steps = 1) 
      : collections(list), iteration_steps(iteration_steps) 
   {
      if (iteration_steps <= 0) {
         this->iteration_steps = 1;
      }
   }
   
   Iterator<T> *new_iterator() override {
      return new ConcreteIterator<T>(this, iteration_steps);
   }

   T get_item(int index) const { 
      return collections[index]; 
   }

   int get_count() const {
      return collections.size();
   }
};

template <typename T> struct Iterator {
   virtual void next() = 0;
   virtual bool end() = 0;
   virtual T current_item() const = 0;
   virtual ~Iterator() = default;
};

template <typename T> class ConcreteIterator : public Iterator<T> {
   ConcreteCollections<T> *collections_obj;
   int current;
   int iteration_steps;
public:
   ConcreteIterator(ConcreteCollections<T> *collections_obj, int iteration_steps) 
      : collections_obj(collections_obj), iteration_steps(iteration_steps) 
   {
      this->current = 0;
   }
   
   void next() override {
      current += iteration_steps;
   }

   bool end() override {
      return current >= collections_obj->get_count();
   }

   T current_item() const override {
      return collections_obj->get_item(current);
   }
};

int main() {
   /* ConcreteCollections<std::string> *collection = new ConcreteCollections<std::string> ({"hello", "world"}, -3); */
   /* Iterator<std::string> *it = collection->new_iterator(); */

   ConcreteCollections<int> *collection = new ConcreteCollections<int> ({1, 2, 3, 4, 5, 6, 7}, 2);
   Iterator<int> *it = collection->new_iterator();

   while (!it->end()) {
      std::cout << it->current_item() << " ";
      it->next();
   }
   std::cout << "\n";

   delete it;
   delete collection;
   return 0;
}
