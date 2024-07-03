// yehonatan768@gmail.com
#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <string>
using namespace std;

namespace catan {

enum cardType {LUMBER, WOOL, GRAIN, ORE, BRICK, DESERT, KNIGHT, BUILD_2_ROAD, VICTORY_POINT, MONOPOL, YEAR_OF_PLENTY};

class Card {
private:
  cardType type;

public:
  // Default constructor
  Card();

  Card(cardType r_type);

  // Copy constructor
  Card(const Card &c);

  // Virtual destructor
  ~Card();

  // Virtual function to get the type of the card
  cardType getType() const;
};

class DevelopmentCard {
private:
  cardType type;
public:
  DevelopmentCard(cardType devType);
  ~DevelopmentCard();
  int getQuantity() const;
  DevelopmentCard *clone() const;
  cardType getType() const;
};

} 
#endif
