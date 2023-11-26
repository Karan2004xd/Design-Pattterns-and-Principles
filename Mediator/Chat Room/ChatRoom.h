#ifndef CHAT_ROOM_H_
#define CHAT_ROOM_H_

#include "Person.h"

struct ChatRoom {
   std::vector<Person*> people;
   void broadcast(const std::string &origin, const std::string &message);
   void join(Person *p);
   void message(const std::string &origin, const std::string &who, const std::string &message);
};
#endif // CHAT_ROOM_H_
