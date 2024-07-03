// yehonatan768@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace catan {

/**
 * @class Player
 * 
 * Represents a player in the game of Catan.
 */
class Player {
protected:
  string _name;                                 ///< The player's name
  map<cardType, int> _cards;                    ///< A map of the player's resource cards
  int victoryPoints = 0;                        ///< The player's victory points
  bool turn = false;                            ///< Flag indicating if it is the player's turn
  Player *nextPlayer;                           ///< Pointer to the next player in turn
  Board *b;                                     ///< Pointer to the game board
  vector<Player *> _otherPlayers;               ///< List of other players in the game
  map<DevelopmentCard *, int> _developmentCards; ///< A map of the player's development cards

public:
  /**
   * @brief Default constructor for Player.
   */
  Player();

  /**
   * @brief Destructor for Player.
   */
  ~Player();

  /**
   * @brief Constructor for Player with a specified name.
   * @param name The name of the player.
   */
  Player(string name);

  /**
   * @brief Get the player's name.
   * @return The player's name.
   */
  string getName();

  /**
   * @brief Get the player's victory points.
   * @return The number of victory points the player has.
   */
  int getVictoryPoints();

  /**
   * @brief Allow the player to buy a development card.
   */
  void BuyDevelopCard();

  /**
   * @brief Allow the player to use a development card.
   * @param d Pointer to the development card to be used.
   */
  void useDevelpCard(DevelopmentCard *d);

  /**
   * @brief Implement the effect of a development card.
   * @param d Pointer to the development card to be implemented.
   */
  void implementDevelopCard(DevelopmentCard *d);

  /**
   * @brief Add a resource card to the player's collection.
   * @param c Pointer to the resource card to be added.
   */
  void addCard(Card *c);

  /**
   * @brief Add two resource cards to the player's collection.
   * @param c Pointer to the resource card to be added.
   */
  void add2Card(Card *c);

  /**
   * @brief Print the player's development cards.
   */
  void printDevelopCard();

  /**
   * @brief Print the player's resource cards.
   */
  void printCard();

  /**
   * @brief Roll dice to determine the outcome of the player's turn.
   * @return The result of rolling the dice.
   */
  int rollDices();

  /**
   * @brief Place a road on the game board.
   * @param wayNumber The number indicating the road position on the board.
   */
  void placeRoad(int wayNumber);

  /**
   * @brief Place a settlement on the game board.
   * @param juncNum The number indicating the settlement position on the board.
   */
  void placeSettlement(int juncNum);

  /**
   * @brief Place a town on the game board.
   * @param JunctionNumber The number indicating the town position on the board.
   */
  void placeTown(int JunctionNumber);

  /**
   * @brief Place the first settlement for the player.
   * @param JunctionNumber The number indicating the settlement position on the board.
   */
  void placeFirstSettlement(int JunctionNumber);

  /**
   * @brief Place the first road for the player.
   * @param WayNum The number indicating the road position on the board.
   */
  void placeFirstRoad(int WayNum);

  /**
   * @brief Set the game board for the player.
   * @param b Pointer to the game board to be set.
   */
  void setBoard(Board *b);

  /**
   * @brief Set the next player in turn.
   * @param p Pointer to the next player.
   */
  void setNextPlayer(Player *p);

  /**
   * @brief Add another player to the list of other players.
   * @param p Pointer to the player to be added.
   */
  void setOtherPlayer(Player *p);

  /**
   * @brief Get a development card from the player's collection.
   * @return Pointer to the development card.
   */
  DevelopmentCard *getDevCard();

  /**
   * @brief Trade resources with another player.
   * @param p Pointer to the player to trade with.
   * @param give Type of resource to give.
   * @param get Type of resource to get in return.
   * @param amountGive Number of resources to give.
   * @param amountGet Number of resources to get in return.
   */
  void trade(Player *p, cardType give, cardType get, int amountGive, int amountGet);

  /**
   * @brief Set whether it is the player's turn.
   * @param b Boolean value indicating if it is the player's turn.
   */
  void setTurn(bool b);

  /**
   * @brief Get the number of a specific type of card in the player's collection.
   * @param type Type of card to count.
   * @return The number of cards of the specified type.
   */
  int getNumOfCard(cardType type);

  /**
   * @brief Give cards to the player after placing a settlement.
   * @param Junctionnumber The number indicating the settlement position on the board.
   */
  void giveCardsAfterPlacing(int Junctionnumber);

  /**
   * @brief Reduce the player's resource cards based on a provided map of resources.
   * @param cards Map containing the resources to be reduced from the player's collection.
   */
  void reduceCards(map<cardType, int> &cards);

  /**
   * @brief Throw cards when required (e.g., after rolling a seven).
   */
  void throwCards();

  /**
   * @brief Check if it is the player's turn.
   * @return True if it is the player's turn, false otherwise.
   */
  bool getTurn();
};

} // namespace catan

#endif // PLAYER_HPP
