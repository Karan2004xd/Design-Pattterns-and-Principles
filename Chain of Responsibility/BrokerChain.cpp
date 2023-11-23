#include <boost/signals2/connection.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <boost/signals2.hpp>

using namespace boost::signals2;

struct Query {
   std::string creature_name;
   enum Arguments { attack, defense } arguments;
   int result;

   Query(std::string creature_name, Arguments arguments, int result)
      : creature_name(creature_name), result(result), arguments(arguments) {}
};

struct Game {
   signal<void(Query &)> queries;
};

struct Creature {
   Game &game;
   std::string name;
   int defense, attack;

   Creature(Game &game, const std::string &name, int defense, int attack)
      : game(game), attack(attack), name(name), defense(defense) {}

   int get_attack() const {
      Query q{name, Query::Arguments::attack, attack};
      game.queries(q);
      return q.result;
   }

   friend std::ostream &operator<<(std::ostream &os, const Creature &creature) {
      os << "attack: " << creature.get_attack() << ", name: " << creature.name << ", defense: " << creature.defense << std::endl;
      return os;
   }
};

class CreatureModifier {
   Game &game;
   Creature &creature;
public:
   CreatureModifier(Game &game, Creature &creature) : game(game), creature(creature) {}
   virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier {
   connection conn;
public:
   DoubleAttackModifier(Game &game, Creature &creature) : 
      CreatureModifier(game, creature)
   {
      conn = game.queries.connect([&](Query &q) {
         if (q.creature_name == creature.name && q.arguments == Query::Arguments::attack) {
            q.result *= 2;
         }
      });
   }
   ~DoubleAttackModifier() { conn.disconnect(); }
};

int main() {
   Game game;
   Creature goblin {game, "Strong goblin", 2, 2};
   
   std::cout << goblin;

   {
      DoubleAttackModifier dam {game, goblin};
      std::cout << goblin;
   }

   std::cout << goblin;
   return 0;
}
