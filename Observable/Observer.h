#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>
template <typename T> struct Observer {
   virtual void field_changed(T &soruce, const std::string &field_name) = 0;
};
#endif // OBSERVER_H_
