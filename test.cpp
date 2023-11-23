#include <vector>
#include <iostream>

struct Creature;
struct Game
{
   std::vector<Creature*> creatures;
};

struct StatQuery
{
   enum Statistic { attack, defense } statistic;
   int result;

   StatQuery(Statistic statistic, int result) : statistic(statistic), result(result) {}
};

struct Creature
{
   protected:
      Game& game;
      int base_attack, base_defense;

   public:
      Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
      base_defense(base_defense) {}
      virtual int get_attack() = 0;
      virtual int get_defense() = 0;
      virtual void query(void *source, StatQuery &sq) = 0; 
};

class Goblin : public Creature
{
   int get_statistics(StatQuery::Statistic stat) {
      StatQuery sq {stat, 0};
      for (auto &i : game.creatures) {
         i->query(this, sq);
      }
      return sq.result;
   }

   public:
      Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

      Goblin(Game &game) : Creature(game, 1, 1) {}

      int get_attack() override {
         return get_statistics(StatQuery::Statistic::attack);
      }

      int get_defense() override {
         return get_statistics(StatQuery::Statistic::defense);
      }

      void query(void *source, StatQuery &sq) override {
         if (this == source) {
            if (sq.statistic == StatQuery::Statistic::attack) {
               sq.result += base_attack;
            } else if (sq.statistic == StatQuery::Statistic::defense) {
               sq.result += base_defense;
            }
         } else {
            if (sq.statistic == StatQuery::Statistic::defense) {
               sq.result++;
            }
         }
      }
};

class GoblinKing : public Goblin
{
   public:
      GoblinKing(Game &game) : Goblin(game, 3, 3) {}
      void query(void *source, StatQuery &sq) override {
         if (sq.statistic == StatQuery::Statistic::attack && source != this) {
            sq.result++;
         } else {
            Goblin::query(source, sq);
         }
      }
};
