// yehonatan768@gmail.com
#include "Card.hpp"

using namespace catan;

// Default constructor sets a default type
Card::Card() : type(DESERT) {}

// Copy constructor
Card::Card(const Card &c) : type(c.type) {}

Card::~Card() {}

Card::Card(cardType r_type) {
    this->type = r_type;
}

cardType Card::getType() const { return this->type; }


DevelopmentCard::~DevelopmentCard() {}

DevelopmentCard::DevelopmentCard(cardType devType) {
  this->type = devType;
}

DevelopmentCard* DevelopmentCard::clone() const {
  return new DevelopmentCard(this->type);
}


int DevelopmentCard::getQuantity() const {
  if (type == VICTORY_POINT) {
          return 4;
      } else if (type == MONOPOL) {
          return 100;
      } else if (type == YEAR_OF_PLENTY) {
          return 100;
      } else if (type  == KNIGHT) {
          return 3;
      } else if (type  == BUILD_2_ROAD) {
          return 100;
      }
    else {
      return 0;
    }
}

cardType DevelopmentCard::getType() const {
  return this->type;
}