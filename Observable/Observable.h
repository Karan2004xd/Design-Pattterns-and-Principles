#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <algorithm>
#include <string>
#include <vector>

template <typename> struct Observer;

template <typename T> struct Observable {
   std::vector<Observer<T>*> observers;
   void notify(T &source, const std::string &field_name) {
      for (auto observer : observers) {
         observer->field_changed(source, field_name);
      }
   }

   void subscribe(Observer<T> *observer) {
      observers.push_back(observer);
   }

   void unsubscribe(Observer<T> *observer) {
      observers.erase(std::find(observers.begin(), observers.end(), observer));
   }
};
#endif // OBSERVABLE_H_
