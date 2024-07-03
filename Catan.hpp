// yehonatan768@gmail.com
#ifndef CATAN_HPP
#define CATAN_HPP
#include "Player.hpp"

namespace catan {
/**
 * @class Catan
 * This class represents the game operator and contains the game components -
 * players, and the game board.
 */
class Catan {
private:
  vector<Player *> _players; ///< Vector of pointers to the players in the game
  Board *b;             ///< The game board

public:
  Catan();             // Default constructor for Catan.
  ~Catan();            // Destructor
  void setPlayers(Player *p1, Player *p2, Player *p3);
  Board *getBoard();   // Get the game board.
  void StartTheGame(); // Start the game.
  int printWinner();  // Print the winner of the game.
  vector<Player*> getPlayers();
};
} 
#endif
