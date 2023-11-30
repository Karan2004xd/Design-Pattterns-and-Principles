#include <iostream>

struct Game {
   Game(int numbers_of_players) : numbers_of_players(numbers_of_players) {}
   void run() {
      start();
      while (!have_winner()) {
         take_turn();
      }
      std::cout << "Player " << get_winner() << " wins" << std::endl;
   }
protected:
   virtual void start() = 0;
   virtual bool have_winner() = 0;
   virtual int get_winner() = 0;
   virtual void take_turn() = 0;
   int current_player {0};
   int numbers_of_players;
};

struct ChessGame : public Game {  
   ChessGame() : Game(2) {}
protected:
   void start() override {
      std::cout << "Starting a game of chess with " << numbers_of_players << " players" << std::endl;
   }

   bool have_winner() override {
      return turn == max_turns;
   }

   int get_winner() override {
      return current_player;  
   }

   void take_turn() override {
      std::cout << "Turn " << turn << " taken by player " << current_player << std::endl;
      turn++;
      current_player = (current_player + 1) % numbers_of_players;
   }

private:
   int turn {0}, max_turns {10};
};

int main() {
   ChessGame chess;
   chess.run();
   return 0;
}
