// yehonatan768@gmail.com
#include "Player.hpp"

using namespace std;
using namespace catan;
// Default constructor for Player class
Player::Player() {}
// destructor
Player::~Player() {
  for (auto &pair : _developmentCards) {
    delete pair.first;
  }
}
// Parameterized constructor for Player class
Player::Player(string name) : _name(name),
                              _cards({{LUMBER, 0},
                                      {GRAIN, 0},
                                      {WOOL, 0},
                                      {ORE, 0},
                                      {BRICK, 0}}) {
  // Initialize the development cards with their respective quantities set to 0
  _developmentCards[new DevelopmentCard(MONOPOL)] = 0;
  _developmentCards[new DevelopmentCard(VICTORY_POINT)] = 0;
  _developmentCards[new DevelopmentCard(YEAR_OF_PLENTY)] = 0;
  _developmentCards[new DevelopmentCard(BUILD_2_ROAD)] = 0;
  _developmentCards[new DevelopmentCard(KNIGHT)] = 0;
}
// return the name of the player
string Player::getName() {
  return this->_name;
}
// Function to get the number of points of the player
int catan::Player::getVictoryPoints() {
  return this->victoryPoints;
}
// Function to check if it's the player's turn
bool catan::Player::getTurn() {
  return this->turn;
}
// Function to set whether it's the player's turn
void Player::setTurn(bool b) {
  this->turn = b;
}
// Function for the player to buy a development card
void catan::Player::BuyDevelopCard() {
  // check the resources
  if (this->getNumOfCard(GRAIN) < 1 || getNumOfCard(ORE) < 1 || getNumOfCard(WOOL) < 1) {
    __throw_logic_error("Error: cannot buy Development card because don't have the resource");
    return;
  }
  // generate a random development card from the pile that in the board
  DevelopmentCard *c = this->b->generateRandomDevCard();
  this->_developmentCards[c]++;
  cout << this->getName() << " Buy a Development Card. The card is: " << c->getType() << endl;
}
// Function for the player to use a development card
void catan::Player::useDevelpCard(DevelopmentCard *d) {
  if (d == nullptr) {
    cout << "Error: No Development card to use" << endl;
    return;
  }
  if (this->_developmentCards[d] == 0) { // id the player dont have this card
    __throw_invalid_argument("Error: cannot implements development card because the player dont have the card.");
    return;
  }
  this->implementDevelopCard(d); // call to helper function --->
}
// An helper Function to implement the effects of a development card
void catan::Player::implementDevelopCard(DevelopmentCard *d) {
  // monopol card- i will iterate on _cards, and i will choose the card with the smaller amount. this source card will be
  // the choose of the player and all the other players will give to this playr this card.
  if (d->getType() == MONOPOL) {
    if (this->_cards.empty()) {
      // Handle empty map case- throwing an exception or returning a specific value
      throw std::runtime_error("_cards is empty");
    }
    int minValue = numeric_limits<int>::max();
    cardType s; // null value for card
    for (const auto &pair : _cards) { // go over all the card in order to find the less amount.
      if (pair.second < minValue) {
        minValue = pair.second;
        s = pair.first;
      }
    }
    for (Player *p : this->_otherPlayers) {                                  // go over the other players
      int amountToGive = p->_cards[s]; // find the amount of this card
      p->_cards[s] -= amountToGive;    // take this cards from another player
      this->_cards[s] += amountToGive; // add this card to this player.
    }
    cout << this->getName() << " implements monopol card and got: " << s << " from all the players!" << endl;
    this->_developmentCards[d]--;
    return;
  }
  // this is bonus 1 point to this palyer
  if (d->getType() == VICTORY_POINT) {
    this->victoryPoints++;
    cout << this->getName() << " Implements bonus point development card and got 1 point!" << endl;
    this->_developmentCards[d]--;
    return;
  }
  if (d->getType() == YEAR_OF_PLENTY) { // find the 2 card withthe min amount- and add them to the player's dev cards
  
    int minValue1 = numeric_limits<int>::max();
    int minValue2 = numeric_limits<int>::max();
    cardType s1 = DESERT; // null value for card
    cardType s2 = DESERT;  // null value for card

    for (const auto &pair : _cards) {
      if (pair.second < minValue1) {
        minValue2 = minValue1;
        s2 = s1;
        minValue1 = pair.second;
        s1 = pair.first;
      }
      else if (pair.second < minValue2) {
        minValue2 = pair.second;
        s2 = pair.first;
      }
    }
    _cards[s1]++;
    _cards[s2]++;

    cout << this->getName() << " Implements year of plenty development card and got: " << s1 << " and " << s2 << " new cards!" << endl;
    this->_developmentCards[d]--;
  }
  // road card will give to this player 2 tree card and 2 brick card(that is the 2 road resources)
  if (d->getType() == BUILD_2_ROAD) {
    Card *t = new Card(LUMBER);
    Card *b = new Card(BRICK);
    this->add2Card(t);
    this->add2Card(b);
    cout << this->getName() << " Implements road development card ,and got 4 new resource card for this!" << endl;
    this->_developmentCards[d]--;
    delete t; // delete this card after i add them to the player cards.
    delete b;
    return;
  }
  // only if one player got 3 knight- he got 2 point
  if (d->getType() == KNIGHT) {
    if (this->_developmentCards[d] == 3) { // have 3 knight card
      cout << this->getName() << " Implements the 3'rd knight development card and got 2 points!" << endl;
      this->victoryPoints += 2;
    }
    else {
      cout << this->getName() << " Implements knight development card ! more 1/2 to get 2 points..." << endl;
    }
    return;
  }
}
// Function to add a card to the player's hand
void catan::Player::addCard(Card *c) {
  for (auto &card : this->_cards) { //  get a reference to each pair
    if (card.first == c->getType()) {
      card.second++;
      cout << "Player: " << this->getName() << " , got 1 card of: " << c->getType() << endl;
      return;
    }
  }
}
// Function to add 2 cards to the player's hand
void catan::Player::add2Card(Card *c) {
  for (auto &card : this->_cards) {
    if (card.first == c->getType()) {
      card.second += 2;
      cout << "Player: " << this->getName() << " got 2 cards of: " << c->getType() << endl;
      return;
    }
  }
}
// Function to print the player's development cards
void catan::Player::printDevelopCard() {
  cout << "Player " << this->getName() << ". Development Cards: ";

  for (const auto &pair : _developmentCards) {
    DevelopmentCard *card = pair.first;
    int quantity = pair.second;
    if (quantity != 0) {
      cout << card->getType() << ", Amount: " << quantity << endl;
    }
  }
}

// Function for the player to place their first settlement
void Player::placeFirstSettlement(int JunctionNumber) {
  if (this->b->getCrossSection(JunctionNumber)->isOccupied() == false) { // cheach if the junction is clear
    cout << this->getName() << " Placed First Settlement at junction number: " << this->b->getCrossSection(JunctionNumber)->getIndex() << endl;
    this->b->getCrossSection(JunctionNumber)->setOccupiedStatus(true); // set to occupate
    Settlement *s = new Settlement(this);
    this->b->getCrossSection(JunctionNumber)->setSettlement(s); // set the settelment to player
                                                                   // add this settelment to the relevant lands
    cout << "add settelment to land number : " << this->b->getCrossSection(JunctionNumber)->getLand1()->getIndex() << endl;
    if (this->b->getCrossSection(JunctionNumber)->getLand2() != nullptr) {
      cout << "add settelment to land number: " << this->b->getCrossSection(JunctionNumber)->getLand2()->getIndex() << endl;
    }
    if (this->b->getCrossSection(JunctionNumber)->getLand3() != nullptr) {
      cout << "add settelment to land number: " << this->b->getCrossSection(JunctionNumber)->getLand3()->getIndex() << endl;
    } // give to the players all the resource card fron those lands
    this->giveCardsAfterPlacing(JunctionNumber);
    this->victoryPoints++;
  }
  else {
    throw std::logic_error("Error: this Cross_Section is already occupied");
  }
}

// Function for the player to place their first road
void catan::Player::placeFirstRoad(int wayNumber) {
  if (this->b->getPath(wayNumber)->isOccupied() == false) {
    this->b->getPath(wayNumber)->setOccupiedStatus(true);
    Road *r = new Road(this);
    this->b->getPath(wayNumber)->setRoad(r);
    cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
    // delete r;
  }
  else {
    __throw_logic_error("Error: this Path is already occupate");
  }
}

// Function to set the game board for the player
void Player::setBoard(Board *b) {
  this->b = b;
}
// Function to set the next player in the game sequence
void catan::Player::setNextPlayer(Player *p) {
  this->nextPlayer = p;
}

// Function to set another player in the game
void catan::Player::setOtherPlayer(Player *p) {
  if (p != nullptr) {
    this->_otherPlayers.push_back(p);
  }
}

// Function to print the player's cards
void catan::Player::printCard() {
  cout << "Player: " << this->getName();
  for (const auto &card : this->_cards) {
    if (card.second != 0) {
      cout << ". Cards: " << card.first << " Amount: " << card.second;
    }
  }
  cout << "" << endl;
}

// Function for the player to roll the dice
int Player::rollDices()
{
  if (this->getTurn())
  {
    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 6);
    // Roll two dice
    int dice1 = dis(gen);
    int dice2 = dis(gen);
    int ans = (dice1 + dice2);
    cout << this->getName() << " Roll the dice. the result: " << ans << endl;

    if (ans == 7) // if the result is 7
    {
      cout << "Players with more than 7 card need to get rid of half of the cards." << endl;
      throwCards(); // each player with more than 7 cards will randomly throw half of his cards.
    }
    for (int i = 0; i < 19; i++) { // go over all the land in the board(19)
      if (this->b->getTile(i)->getNumber() == ans) { // if the land have the ans number on it
        for (int j = 0; j < 6; j++) { // so go over the land's junctions(6)
          if (this->b->getTile(i)->getJunc()[j] != nullptr) { // chack if not null
            if (this->b->getTile(i)->getJunc()[j]->isOccupied() == true) { // if the junc is occupate(settelment\town)
              if (this->b->getTile(i)->getJunc()[j]->getSettelment() != nullptr) { // if settelment
                if (this->b->getTile(i)->getJunc()[j]->getSettelment()->getPlayer()->getName() == this->getName()) { // check if its my settelment
                  this->addCard(this->b->getTile(i)->getCard()); // if yes- add a card to me
                }
                if (this->b->getTile(i)->getJunc()[j]->getSettelment()->getPlayer()->getName() == this->_otherPlayers[0]->getName()) { // same check for other players
                  this->_otherPlayers[0]->addCard(this->b->getTile(i)->getCard());
                }
                if (this->b->getTile(i)->getJunc()[j]->getSettelment()->getPlayer() == this->_otherPlayers[1]) {
                  this->_otherPlayers[1]->addCard(this->b->getTile(i)->getCard());
                }
              }
              if (this->b->getTile(i)->getJunc()[j]->getTown() != nullptr) { // if i have a town in this junction
                if (this->b->getTile(i)->getJunc()[j]->getTown()->getPlayer() == this) { // it its belongs to me
                  this->add2Card(this->b->getTile(i)->getCard()); // add 2 cards
                }
                if (this->b->getTile(i)->getJunc()[j]->getTown()->getPlayer() == this->_otherPlayers[0]) { // same check for other players
                  this->_otherPlayers[0]->add2Card(this->b->getTile(i)->getCard());
                }
                if (this->b->getTile(i)->getJunc()[j]->getTown()->getPlayer() == this->_otherPlayers[1]) {
                  this->_otherPlayers[1]->add2Card(this->b->getTile(i)->getCard());
                }
              }
            }
          }
        }
      }
    }
    this->turn = false;              // finish my turn
    this->nextPlayer->setTurn(true); // next player turn
    return ans;
  }
  else {
    throw logic_error("Error: Not your turn");
    return 0;
  }
}

// Function for the player to place a road
void catan::Player::placeRoad(int wayNumber) {
  // if this Path isnt occupate- i cannot sat a road.
  if (this->b->getPath(wayNumber)->isOccupied()) {
    __throw_logic_error("Error: This Path is Already occupate");
  }
  else { // if the way is clear:make sure you have the card source for road 
    if (this->getNumOfCard(LUMBER) < 1 || getNumOfCard(BRICK) < 1) {
      __throw_logic_error("Error: cannot place Road because dont have the resource");
      return;
    }
    this->_cards[LUMBER]--;
    this->_cards[BRICK]--;
    Cross_Section *j1 = this->b->getPath(wayNumber)->getCrossSection1();
    Cross_Section *j2 = this->b->getPath(wayNumber)->getCrossSection2();
    // if j1 is my junction- i can set a road on this way.
    if (j2->isOccupied()) {

      if (j2->getSettelment()->getPlayer()->getName() == this->getName() || j2->getTown()->getPlayer()->getName() == this->getName()) {
        b->getPath(wayNumber)->setOccupiedStatus(true);
        Road *r = new Road(this);
        b->getPath(wayNumber)->setRoad(r);
        cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
        // delete r;
        return;
      }
    }
    // if j1 is my junction- i can set a road on this way.
    else if (j1->isOccupied()) {
      if (j1->getSettelment()->getPlayer()->getName() == this->getName() || j1->getTown()->getPlayer()->getName() == this->getName()) {
        b->getPath(wayNumber)->setOccupiedStatus(true);
        Road *r = new Road(this);
        b->getPath(wayNumber)->setRoad(r);
        cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
        // delete r;
        return;
      }
    }
    // check all the neighbrood ways and roads;if they belong to me- i can set a road on this way.
    else if (j1->getPath1() != nullptr) {
      if (j1->getPath1()->isOccupied()) {
        if (j1->getPath1()->getRoad()->getPlayer() == this) {
          Road *r = new Road(this);
          b->getPath(wayNumber)->setRoad(r);
          cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
          // delete r;
          return;
        }
      }
    }
    else if (j1->getPath2() != nullptr) {
      if (j1->getPath2()->isOccupied()) {
        if (j1->getPath2()->getRoad()->getPlayer() == this) {
          Road *r = new Road(this);
          b->getPath(wayNumber)->setRoad(r);
          cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
          // delete r;
          return;
        }
      }
    }
    else if (j1->getPath3() != nullptr) {
      if (j1->getPath3()->isOccupied()) {
        if (j1->getPath3()->getRoad()->getPlayer() == this) {
          Road *r = new Road(this);
          b->getPath(wayNumber)->setRoad(r);
          cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
          return;
        }
      }
    }
    else if (j2->getPath1() != nullptr) {
      if (j2->getPath1()->isOccupied()) {
        if (j2->getPath1()->getRoad()->getPlayer() == this) {
          Road *r = new Road(this);
          b->getPath(wayNumber)->setRoad(r);
          cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
          return;
        }
      }
    }
    else if (j2->getPath2() != nullptr) {
      if (j2->getPath2()->isOccupied()) {
        if (j2->getPath2()->getRoad()->getPlayer() == this) {
          Road *r = new Road(this);
          b->getPath(wayNumber)->setRoad(r);
          cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
          return;
        }
      }
    }
    else if (j2->getPath3() != nullptr) {
      if (j2->getPath3()->isOccupied()) {
        if (j2->getPath3()->getRoad()->getPlayer() == this)
        {
          Road *r = new Road(this);
          b->getPath(wayNumber)->setRoad(r);
          cout << this->getName() << " Place Road at way number: " << this->b->getPath(wayNumber)->getIndex() << endl;
          return;
        }
      }
    }
    else {
      __throw_logic_error("Error: canot replace road  in this way");
    }
  }
}
// Function for the player to place a settlement
void catan::Player::placeSettlement(int juncNumber) {
  // Check if the junction is already occupied
  if (this->b->getCrossSection(juncNumber)->isOccupied()) {
    __throw_invalid_argument("Error: this Cross_Section is already occupied");
  }

  // Check if the player has the required resources
  if ((this->getNumOfCard(LUMBER) < 1) ||
      (this->getNumOfCard(BRICK) < 1) ||
      (this->getNumOfCard(GRAIN) < 1) ||
      (this->getNumOfCard(WOOL) < 1)) {
    __throw_logic_error("Error: cannot place Settlement because don't have the resource cards");
  }
  // Deduct the resources
  this->_cards[LUMBER]--;
  this->_cards[BRICK]--;
  this->_cards[GRAIN]--;
  this->_cards[WOOL]--;
  // Get the junction object
  Cross_Section *j = this->b->getCrossSection(juncNumber);
  // check if there is a way that belong to this player next to this junction:(2/3 options to ways from junction)
  if (j->getPath1() != nullptr && j->getPath1()->isOccupied()) { // check if the road belong to this player:
    if (j->getPath1()->getRoad()->getPlayer() == this) { // if at the end of the road there is no junction with settelment\town- the player can place settelment.
      if ((j->getPath1()->getCrossSection2() != j && j->getPath1()->getCrossSection2()->isOccupied() == false) ||
          (j->getPath1()->getCrossSection1() != j && j->getPath1()->getCrossSection1()->isOccupied() == false)) {
        j->setSettlement(new Settlement(this));
        cout << this->getName() << " Placed Settlement at junction number: " << this->b->getCrossSection(juncNumber)->getIndex() << endl;
        this->victoryPoints++;
        return;
      }
    }
  } // go over the same check in way2
  if (j->getPath2() != nullptr && j->getPath2()->isOccupied()) {
    if (j->getPath2()->getRoad()->getPlayer() == this) {
      if ((j->getPath2()->getCrossSection2() != j && j->getPath2()->getCrossSection2()->isOccupied() == false) ||
          (j->getPath2()->getCrossSection1() != j && j->getPath2()->getCrossSection1()->isOccupied() == false)) {
        j->setSettlement(new Settlement(this));
        cout << this->getName() << " Placed Settlement at junction number: " << this->b->getCrossSection(juncNumber)->getIndex() << endl;
        this->victoryPoints++;
        return;
      }
    }
  } // go over the same check in way3
  if (j->getPath3() != nullptr && j->getPath3()->isOccupied()) {
    if (j->getPath3()->getRoad()->getPlayer() == this) {
      if ((j->getPath3()->getCrossSection2() != j && j->getPath3()->getCrossSection2()->isOccupied() == false) ||
          (j->getPath3()->getCrossSection1() != j && j->getPath3()->getCrossSection1()->isOccupied() == false)) {
        j->setSettlement(new Settlement(this));
        cout << this->getName() << " Placed Settlement at junction number: " << this->b->getCrossSection(juncNumber)->getIndex() << endl;
        this->victoryPoints++;
        return;
      }
    }
  }
  else { // there is no way that next to this junction- cannot place here settelment
    __throw_logic_error("Error: cannot place Settlement because don't have a road to this junction");
  }
}
// Function for the player to place a town
void catan::Player::placeTown(int JunctionNumber) {
  // if this junction has a town on it already / this junction dont have a settelment on it- cannot replace town:
  if (this->b->getCrossSection(JunctionNumber)->getTown() != nullptr) {
    __throw_invalid_argument("Error: this town already occupate");
    return;
  }
  if (this->b->getCrossSection(JunctionNumber)->getSettelment() == nullptr) {
    __throw_invalid_argument("Error:there is not settelment on this junction");
    return;
  }
  // if i am the owner of this setelment in this junction
  if (this->b->getCrossSection(JunctionNumber)->getSettelment()->getPlayer() == this) {
    if ( // make sure i have the card to buy the town
        this->getNumOfCard(GRAIN) < 2 ||
        this->getNumOfCard(ORE) < 3) {
      __throw_logic_error("Error: cannot place Town because don't have the resource");
      return;
    }
    // Deduct the resources
    this->_cards[ORE] -= 3;
    this->_cards[GRAIN] -= 2;
    Town *t = new Town(this);
    this->b->getCrossSection(JunctionNumber)->setTown(t);
    this->victoryPoints++;
    cout << this->getName() << " Placed Town at junction number: " << this->b->getCrossSection(JunctionNumber)->getIndex() << endl;
  }
  else {
    __throw_logic_error("Error: this Cross_Section already had a settelment of another player");
  }
}
// Function for the player to discard cards when the dice is rolled and a 7 is thrown,chosen randomly
void Player::throwCards() {
  int amount = 0;
  for (auto &card : _cards) {
    if (card.second > 0) {
      amount += card.second;
    }
  }
  // Reduce cards for the player if needed
  if (amount > 7) {
    reduceCards(this->_cards);
    cout << this->_name << " get rid of cards" << endl;
  }
  // Reduce cards for the other players if needed
  for (auto *player : this->_otherPlayers) {
    int amount = 0;
    for (auto &card : player->_cards) {
      if (card.second > 0) {
        amount += card.second;
      }
    }
    if (amount > 7) {
      cout << player->_name << " get rid of cards" << endl;
      reduceCards(player->_cards);
    }
  }
}

// Function to reduce cards for the player if needed
void Player::reduceCards(map<cardType, int> &cards) {
  int totalCards = 0;
  for (const auto &card : cards) { // calculate the sum of the cards
    totalCards += card.second;
  }
  // If the total number of cards is greater than 7
  if (totalCards > 7) {
    // Calculate the number of cards to remove
    int targetTotal = totalCards / 2;
    vector<cardType> card_types;
    for (const auto &card : cards) {
      if (card.second > 0) { // find cards that the amount is not 0
        card_types.push_back(card.first);
      }
    }
    // Randomly discard cards until the target total is reached
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, card_types.size() - 1);
    // complete the while loop untill half of the card thrown
    while (totalCards > targetTotal) {
      int index = dis(gen);
      cardType card_type = card_types[index];
      if (cards[card_type] > 0) {
        cards[card_type]--;
        totalCards--;
        if (cards[card_type] == 0) {
          card_types.erase(card_types.begin() + index);
          if (card_types.empty()) {
            break;
          }
        }
      }
    }
  }
}

// Function for the player to give cards after placing the first settlement
// Gives card according to the land that belong to this junction. could be 1 or 2 or 3 lands.
void Player::giveCardsAfterPlacing(int Junctionnumber) {
  Tile *tile1 = this->b->getCrossSection(Junctionnumber)->getLand1();
  if (tile1) {
    Card *card1 = tile1->getCard();
    if (card1) {
      Card *newCard1 = new Card(*card1);
      this->addCard(newCard1);
      delete newCard1;
    }
    else {
      cerr << "Error: card1 is null" << endl;
    }
  }

  Tile *tile2 = this->b->getCrossSection(Junctionnumber)->getLand2();
  if (tile2) {
    Card *card2 = tile2->getCard();
    if (card2) {
      Card *newCard2 = new Card(*card2);
      this->addCard(newCard2);
      delete newCard2;
    }
    else {
      cerr << "Error: card2 is null" << endl;
    }
  }
  Tile *tile3 = this->b->getCrossSection(Junctionnumber)->getLand3();
  if (tile3) {
    Card *card3 = tile3->getCard();
    if (card3) {
      Card *newCard3 = new Card(*card3);
      this->addCard(newCard3);
      delete newCard3;
    }
    else {
      cerr << "Error: card3 is null" << endl;
    }
  }
}

// Function to get the number of a specific card in the player's hand
int catan::Player::getNumOfCard(cardType type) {
  return this->_cards[type];
}
// Function for the player to trade resources with another player
void catan::Player::trade(Player *p, cardType give, cardType get, int amountGive, int amountGet) {
  if (p == this) { // cannot trade with myself
    __throw_invalid_argument("Error: cannot trade with myself...");
  } // check that the given/get cards amount is legal
  if (this->getNumOfCard(give) >= amountGive && p->getNumOfCard(get) >= amountGet) {
    this->_cards[give] -= amountGive;
    this->_cards[get] += amountGet;
    p->_cards[get] -= amountGet;
    p->_cards[give] += amountGive;
    cout << this->getName() << " Trades: give " << amountGive << " " << give << " To " << p->getName() << ", and get " << amountGet << " " << get << endl;
  }
  else {
    __throw_invalid_argument("Error: this trade couldn't be completed");
  }
}
// Function that returns some development card
DevelopmentCard *catan::Player::getDevCard() {
  // Iterate through the development cards map
  for (auto &pair : _developmentCards) {
    // If the quantity of the card at position i is greater than 0, return that card
    if (pair.second > 0) {
      return pair.first;
    }
  }
  // If no card with quantity > 0 is found, return nullptr or handle the case accordingly
  return nullptr;
}