#include "ChatRoom.h"
#include <algorithm>
#include <iterator>

void ChatRoom::broadcast(const std::string &origin, const std::string &message) {
   for (auto &i : people) {
      if (i->name != origin) {
         i->receive(origin, message);
      }
   }
}

void ChatRoom::join(Person *p) {
   std::string joining_msg = p->name + " joins the chat room";
   broadcast("room", joining_msg);
   p->room = this;
   people.push_back(p);
}

void ChatRoom::message(const std::string &origin, const std::string &who, const std::string &message) {
   auto target = std::find_if(
         std::begin(people),
         std::end(people),
         [&](const Person *p) {
         return p->name == who;
         }
   );

   if (target != std::end(people)) {
      (*target)->receive(origin, message);
   }
}
