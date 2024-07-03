// yehonatan768@gmail.com
#include "Catan.hpp"
#include <iostream>
using namespace std;
using namespace catan;
/**
 * @class catan:
 * This class represents the game operator and contains the game components -
 * players, and the game board.
 */
//cons
Catan::Catan() : _players(), b(nullptr) {}
//dest
Catan::~Catan() { delete b; }
//set the players of this game
void Catan::setPlayers(Player *p1, Player *p2, Player *p3) {
  if (p1 && p2 && p3) {
    this->_players.push_back(p1);
    this->_players.push_back(p2);
    this->_players.push_back(p3);
  } else {
    cout << "Error: One or more player pointers are null." << endl;
  }
}
// this function return the *board of the game
Board *Catan::getBoard() { return this->b; }
// this function starting the game- player #1 always started
void Catan::StartTheGame() {
  cout << "                                                   " << endl;
  cout << "               **********   LET'S START PLAY CATAN !!! **********"
       << endl;
  cout << "               ********  JUNCTIONS: 54 _____ ROADS: 72  ********** "
       << endl;
  cout << "               **PLAYER#1: " << this->_players[0]->getName()
       << ", PLAYER#2: " << this->_players[1]->getName()
       << ", PLAYER#3: " << this->_players[2]->getName() << "**" << endl;
  cout << "               ***************************************************"
       << endl;
  cout << "                                                   " << endl;
  this->_players[0]->setNextPlayer(_players[1]);
  this->_players[1]->setNextPlayer(_players[2]);
  this->_players[2]->setNextPlayer(_players[0]);
  // define the other players in this game
  this->_players[0]->setOtherPlayer(_players[1]);
  this->_players[0]->setOtherPlayer(_players[2]);
  this->_players[1]->setOtherPlayer(_players[2]);
  this->_players[1]->setOtherPlayer(_players[0]);
  this->_players[2]->setOtherPlayer(_players[0]);
  this->_players[2]->setOtherPlayer(_players[1]);

  this->_players[0]->setTurn(true);
}
// this function will print the winner if some of the player got 10 points.
int Catan::printWinner() {
  for (Player *p : this->_players) {
    if (p->getVictoryPoints() == 10) {
      cout << "******* GAME OVER **********" << endl;
      cout << "     THE WINNER IS-- " << p->getName() << "      " << endl;
      return 1;
    }
  }
  cout << "******* GAME not OVER **********" << endl;
  cout << "***No player with 10 points yet***" << endl;
  cout << "*******Continue the Game...********" << endl;
  return 0;

}
//getter for players of this game
vector<Player *> catan::Catan::getPlayers() {
    return this->_players;
}
