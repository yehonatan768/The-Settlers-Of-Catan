// yehonatan768@gmail.com
#include "Board.hpp"


using namespace catan;
/**
This class represents the game board.
The game board consists of several components:
1. About 19 different plots of land consisting of 5 different resources and a
single desert.each land have a uniqu nomber from 2 to 12.
2. About 54 junctions sitting on the vertices of the plots of land. A settlement
or a town can be established on a cross_sections.
3. About 72 ways passing between the intersections. A road can be set up on a
way.
4. Pack of resource cards. Each piece of land is associated with a resource card
that can be obtained by rolling out the number associated with that piece of
land.
**/
// this function return *cross_sections of speceifed index
Cross_Section *Board::getCrossSection(int index) { return this->crossSections[index]; }
// this function return way* of speceifed index
Path *Board::getPath(int index) { return this->paths[index]; }
// this function return land* of speceifed index
Tile *Board::getTile(int index) { return this->tiles[index]; }
// this is board distructor
Board::~Board() {
  // // Clean up dynamically allocated DevelopmentCard objects in the map
  for (auto &pair : eventCard_Deck) {
    delete pair.first; // Delete each DevelopmentCard object
  }

  // Clean up dynamically allocated Cross_Section objects
  for (auto cross_sections : crossSections) {
    delete cross_sections;
  }
  // Clean up dynamically allocated Tile objects
  for (auto tile : tiles) {
    delete tile;
  }
  // Clean up dynamically allocated Path objects
  for (auto way : paths) {
    delete way;
  }
}
// this function return a development card randomly
DevelopmentCard *Board::generateRandomDevCard() {
  if (eventCard_Deck.empty()) {
    return nullptr; // No cards available
  }
  // Create a vector to hold the non-zero quantity cards
  vector<DevelopmentCard *> availableCards;
  for (const auto &pair : eventCard_Deck) {
    if (pair.second > 0) {
      availableCards.push_back(pair.first);
    }
  }
  if (availableCards.empty()) {
    return nullptr; // No available cards with non-zero quantity
  }
  // Randomly select a card from the available cards
  int randomIndex = rand() % availableCards.size();
  DevelopmentCard *selectedCard = availableCards[randomIndex];
  // Decrease the quantity of the selected card
  eventCard_Deck[selectedCard]--;
  // Return a clone of the selected card
  return selectedCard->clone();
}
//this function print all the junctions in the board with all the lands and their resources.
void catan::Board::printBoard()
{
  for(int i=0; i<54;i++){
    this->crossSections[i]->printJunction();
  }
}

void Board::addPath(map<int, Path* > *ways, map<int, Cross_Section* > *jncs, int i, int j, int gap) {
    for (int k=i; k<=j; k++) {
      (*ways)[k] = new Path(k, (*jncs)[k-gap-1], (*jncs)[k-gap]);
    }
}

void Board::createTiles(map<int, Tile* > *t) {
    // create all the land on the board:
  (*t)[1] = new Tile(LUMBER, 1, vector<Town>(), vector<Road>(), vector<Settlement>()); 
  (*t)[2] = new Tile(WOOL, 2, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[3] = new Tile(BRICK, 3, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[4] = new Tile(GRAIN, 4, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[5] = new Tile(ORE, 5, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[6] = new Tile(GRAIN, 6, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[7] = new Tile(WOOL, 7, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[8] = new Tile(DESERT, 8, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[9] = new Tile(LUMBER, 9, vector<Town>(), vector<Road>(), vector<Settlement>());;
  (*t)[10] = new Tile(BRICK, 10, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[11] = new Tile(LUMBER, 11, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[12] = new Tile(BRICK, 12, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[13] = new Tile(GRAIN, 13, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[14] = new Tile(WOOL, 14, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[15] = new Tile(WOOL, 15, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[16] = new Tile(ORE, 16, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[17] = new Tile(WOOL, 2, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[18] = new Tile(BRICK, 18, vector<Town>(), vector<Road>(), vector<Settlement>());
  (*t)[19] = new Tile(LUMBER, 19, vector<Town>(), vector<Road>(), vector<Settlement>());


  (*t)[1]->setNumber(11);
  (*t)[2]->setNumber(12);
  (*t)[3]->setNumber(9);
  (*t)[4]->setNumber(4);
  (*t)[5]->setNumber(6);
  (*t)[6]->setNumber(5);
  (*t)[7]->setNumber(10);
  (*t)[8]->setNumber(0);
  (*t)[9]->setNumber(3);
  (*t)[10]->setNumber(11);
  (*t)[11]->setNumber(4);
  (*t)[12]->setNumber(8);
  (*t)[13]->setNumber(8);
  (*t)[14]->setNumber(10);
  (*t)[15]->setNumber(9);
  (*t)[16]->setNumber(3);
  (*t)[17]->setNumber(5);
  (*t)[18]->setNumber(2);
  (*t)[19]->setNumber(6);
}


void Board::createAllPaths(map<int, Path* > *w, map<int, Cross_Section* > *j) {
  (*w)[1] = new Path(1, (*j)[1], (*j)[14]);
  addPath(w, j, 2, 10, 0);

  (*w)[11] = new Path(11, (*j)[10], (*j)[5]);
  addPath(w, j, 12, 13, 1);
  (*w)[14] = new Path(14, (*j)[12], (*j)[3]);

  addPath(w, j, 15, 17, 2);

  (*w)[18] = new Path(18, (*j)[18], (*j)[18]);
  addPath(w, j, 19, 20, 2);
  (*w)[21] = new Path(21, (*j)[18], (*j)[13]);

  addPath(w, j, 22, 23, 3);
  (*w)[24] = new Path(24, (*j)[20], (*j)[11]);

  addPath(w, j, 25, 26, 4);
  (*w)[27] = new Path(27, (*j)[22], (*j)[9]);
  (*w)[28] = new Path(28, (*j)[22], (*j)[23]);
  (*w)[29] = new Path(29, (*j)[23], (*j)[25]);
  (*w)[30] = new Path(30, (*j)[25], (*j)[24]);
  (*w)[31] = new Path(31, (*j)[24], (*j)[8]);
  (*w)[32] = new Path(32, (*j)[25], (*j)[26]);

  addPath(w, j, 33, 35, 6);
  (*w)[36] = new Path(36, (*j)[29], (*j)[23]);

  addPath(w, j, 37, 39, 7);
  addPath(w, j, 40, 41, 8);
  (*w)[42] = new Path(42, (*j)[33], (*j)[19]);

  addPath(w, j, 43, 44, 10);
  (*w)[45] = new Path(45, (*j)[35], (*j)[17]);
  (*w)[46] = new Path(46, (*j)[35], (*j)[36]);
  (*w)[47] = new Path(47, (*j)[36], (*j)[38]);
  (*w)[48] = new Path(48, (*j)[38], (*j)[37]);
  (*w)[49] = new Path(49, (*j)[37], (*j)[16]);
  (*w)[50] = new Path(50, (*j)[36], (*j)[39]);

  addPath(w, j, 51, 52, 11);
  (*w)[53] = new Path(53, (*j)[41], (*j)[34]);

  addPath(w, j, 54, 55, 12);
  (*w)[56] = new Path(56, (*j)[43], (*j)[32]);

  addPath(w, j, 57, 58, 13);
  (*w)[59] = new Path(59, (*j)[45], (*j)[30]);
  (*w)[60] = new Path(60, (*j)[45], (*j)[46]);
  (*w)[61] = new Path(61, (*j)[46], (*j)[47]);
  (*w)[62] = new Path(62, (*j)[47], (*j)[28]);
  (*w)[63] = new Path(63, (*j)[46], (*j)[48]);

  addPath(w, j, 64, 65, 15);
  (*w)[66] = new Path(66, (*j)[50], (*j)[44]);

  addPath(w, j, 67, 68, 16);
  (*w)[69] = new Path(69, (*j)[52], (*j)[42]);

  addPath(w, j, 70, 71, 17);
  (*w)[72] = new Path(72, (*j)[54], (*j)[40]);

}


void Board::setAllTiles(map<int, Path* > *w, map<int, Cross_Section* > *j, map<int, Tile* > *t) {
  // place all the ways and the kands into junctions
  (*j)[1]->addWay((*w)[1]);
  (*j)[1]->addWay((*w)[2]);
  (*j)[1]->addLand((*t)[1]);

  (*j)[2]->addWay((*w)[2]);
  (*j)[2]->addWay((*w)[3]);
  (*j)[2]->addLand((*t)[1]);

  (*j)[3]->addWay((*w)[3]);
  (*j)[3]->addWay((*w)[4]);
  (*j)[3]->addLand((*t)[1]);
  (*j)[3]->addLand((*t)[2]);

  (*j)[4]->addWay((*w)[4]);
  (*j)[4]->addWay((*w)[5]);
  (*j)[4]->addLand((*t)[2]);

  (*j)[5]->addWay((*w)[5]);
  (*j)[5]->addWay((*w)[6]);
  (*j)[5]->addLand((*t)[2]);
  (*j)[5]->addLand((*t)[3]);

  (*j)[6]->addWay((*w)[6]);
  (*j)[6]->addWay((*w)[7]);
  (*j)[6]->addLand((*t)[3]);

  (*j)[7]->addWay((*w)[7]);
  (*j)[7]->addWay((*w)[8]);
  (*j)[7]->addLand((*t)[3]);

  (*j)[8]->addWay((*w)[8]);
  (*j)[8]->addWay((*w)[9]);
  (*j)[8]->addWay((*w)[31]);
  (*j)[8]->addLand((*t)[3]);
  (*j)[8]->addLand((*t)[7]);

  (*j)[9]->addWay((*w)[9]);
  (*j)[9]->addWay((*w)[10]);
  (*j)[9]->addWay((*w)[27]);
  (*j)[9]->addLand((*t)[3]);
  (*j)[9]->addLand((*t)[7]);
  (*j)[9]->addLand((*t)[6]);

  (*j)[10]->addWay((*w)[11]);
  (*j)[10]->addWay((*w)[10]);
  (*j)[10]->addWay((*w)[12]);
  (*j)[10]->addLand((*t)[2]);
  (*j)[10]->addLand((*t)[3]);
  (*j)[10]->addLand((*t)[6]);

  (*j)[11]->addWay((*w)[12]);
  (*j)[11]->addWay((*w)[13]);
  (*j)[11]->addWay((*w)[24]);
  (*j)[11]->addLand((*t)[2]);
  (*j)[11]->addLand((*t)[5]);
  (*j)[11]->addLand((*t)[6]);

  (*j)[12]->addWay((*w)[13]);
  (*j)[12]->addWay((*w)[14]);
  (*j)[12]->addWay((*w)[15]);
  (*j)[12]->addLand((*t)[1]);
  (*j)[12]->addLand((*t)[2]);
  (*j)[12]->addLand((*t)[5]);

  (*j)[13]->addWay((*w)[15]);
  (*j)[13]->addWay((*w)[16]);
  (*j)[13]->addWay((*w)[21]);
  (*j)[13]->addLand((*t)[1]);
  (*j)[13]->addLand((*t)[4]);
  (*j)[13]->addLand((*t)[5]);

  (*j)[14]->addWay((*w)[1]);
  (*j)[14]->addWay((*w)[16]);
  (*j)[14]->addWay((*w)[17]);
  (*j)[14]->addLand((*t)[1]);
  (*j)[14]->addLand((*t)[4]);

  (*j)[15]->addWay((*w)[17]);
  (*j)[15]->addWay((*w)[18]);
  (*j)[15]->addLand((*t)[4]);

  (*j)[16]->addWay((*w)[18]);
  (*j)[16]->addWay((*w)[19]);
  (*j)[16]->addWay((*w)[49]);
  (*j)[16]->addLand((*t)[4]);
  (*j)[16]->addLand((*t)[8]);

  (*j)[17]->addWay((*w)[20]);
  (*j)[17]->addWay((*w)[19]);
  (*j)[17]->addWay((*w)[45]);
  (*j)[17]->addLand((*t)[4]);
  (*j)[17]->addLand((*t)[8]);
  (*j)[17]->addLand((*t)[9]);

  (*j)[18]->addWay((*w)[20]);
  (*j)[18]->addWay((*w)[21]);
  (*j)[18]->addWay((*w)[22]);
  (*j)[18]->addLand((*t)[4]);
  (*j)[18]->addLand((*t)[5]);
  (*j)[18]->addLand((*t)[9]);

  (*j)[19]->addWay((*w)[22]);
  (*j)[19]->addWay((*w)[23]);
  (*j)[19]->addWay((*w)[42]);
  (*j)[19]->addLand((*t)[5]);
  (*j)[19]->addLand((*t)[10]);
  (*j)[19]->addLand((*t)[9]);

  (*j)[20]->addWay((*w)[24]);
  (*j)[20]->addWay((*w)[23]);
  (*j)[20]->addWay((*w)[25]);
  (*j)[20]->addLand((*t)[5]);
  (*j)[20]->addLand((*t)[6]);
  (*j)[20]->addLand((*t)[10]);

  (*j)[21]->addWay((*w)[25]);
  (*j)[21]->addWay((*w)[26]);
  (*j)[21]->addWay((*w)[39]);
  (*j)[21]->addLand((*t)[6]);
  (*j)[21]->addLand((*t)[10]);
  (*j)[21]->addLand((*t)[11]);

  (*j)[22]->addWay((*w)[27]);
  (*j)[22]->addWay((*w)[28]);
  (*j)[22]->addWay((*w)[26]);
  (*j)[22]->addLand((*t)[6]);
  (*j)[22]->addLand((*t)[7]);
  (*j)[22]->addLand((*t)[11]);

  (*j)[23]->addWay((*w)[28]);
  (*j)[23]->addWay((*w)[29]);
  (*j)[23]->addWay((*w)[36]);
  (*j)[23]->addLand((*t)[7]);
  (*j)[23]->addLand((*t)[11]);
  (*j)[23]->addLand((*t)[12]);

  (*j)[24]->addWay((*w)[31]);
  (*j)[24]->addWay((*w)[30]);
  (*j)[24]->addLand((*t)[7]);

  (*j)[25]->addWay((*w)[29]);
  (*j)[25]->addWay((*w)[30]);
  (*j)[25]->addWay((*w)[32]);
  (*j)[25]->addLand((*t)[7]);
  (*j)[25]->addLand((*t)[12]);

  (*j)[26]->addWay((*w)[33]);
  (*j)[26]->addWay((*w)[32]);
  (*j)[26]->addLand((*t)[12]);

  (*j)[27]->addWay((*w)[33]);
  (*j)[27]->addWay((*w)[34]);
  (*j)[27]->addLand((*t)[12]);

  (*j)[28]->addWay((*w)[34]);
  (*j)[28]->addWay((*w)[35]);
  (*j)[28]->addWay((*w)[62]);
  (*j)[28]->addLand((*t)[6]);
  (*j)[28]->addLand((*t)[12]);

  (*j)[29]->addWay((*w)[35]);
  (*j)[29]->addWay((*w)[36]);
  (*j)[29]->addWay((*w)[37]);
  (*j)[29]->addLand((*t)[1]);
  (*j)[29]->addLand((*t)[12]);
  (*j)[29]->addLand((*t)[16]);

  (*j)[30]->addWay((*w)[37]);
  (*j)[30]->addWay((*w)[38]);
  (*j)[30]->addWay((*w)[59]);
  (*j)[30]->addLand((*t)[11]);
  (*j)[30]->addLand((*t)[15]);
  (*j)[30]->addLand((*t)[16]);

  (*j)[31]->addWay((*w)[40]);
  (*j)[31]->addWay((*w)[38]);
  (*j)[31]->addWay((*w)[39]);
  (*j)[31]->addLand((*t)[10]);
  (*j)[31]->addLand((*t)[15]);
  (*j)[31]->addLand((*t)[11]);

  (*j)[32]->addWay((*w)[40]);
  (*j)[32]->addWay((*w)[41]);
  (*j)[32]->addWay((*w)[56]);
  (*j)[32]->addLand((*t)[10]);
  (*j)[32]->addLand((*t)[15]);
  (*j)[32]->addLand((*t)[14]);

  (*j)[33]->addWay((*w)[41]);
  (*j)[33]->addWay((*w)[42]);
  (*j)[33]->addWay((*w)[43]);
  (*j)[33]->addLand((*t)[10]);
  (*j)[33]->addLand((*t)[9]);
  (*j)[33]->addLand((*t)[14]);

  (*j)[34]->addWay((*w)[43]);
  (*j)[34]->addWay((*w)[44]);
  (*j)[34]->addWay((*w)[53]);
  (*j)[34]->addLand((*t)[9]);
  (*j)[34]->addLand((*t)[13]);
  (*j)[34]->addLand((*t)[14]);

  (*j)[35]->addWay((*w)[44]);
  (*j)[35]->addWay((*w)[45]);
  (*j)[35]->addWay((*w)[46]);
  (*j)[35]->addLand((*t)[8]);
  (*j)[35]->addLand((*t)[9]);
  (*j)[35]->addLand((*t)[13]);

  (*j)[36]->addWay((*w)[46]);
  (*j)[36]->addWay((*w)[47]);
  (*j)[36]->addWay((*w)[50]);
  (*j)[36]->addLand((*t)[8]);
  (*j)[36]->addLand((*t)[13]);

  (*j)[37]->addWay((*w)[49]);
  (*j)[37]->addWay((*w)[48]);
  (*j)[37]->addLand((*t)[8]);

  (*j)[38]->addWay((*w)[47]);
  (*j)[38]->addWay((*w)[48]);
  (*j)[38]->addLand((*t)[8]);

  (*j)[39]->addWay((*w)[50]);
  (*j)[39]->addWay((*w)[51]);
  (*j)[39]->addLand((*t)[13]);

  (*j)[40]->addWay((*w)[51]);
  (*j)[40]->addWay((*w)[52]);
  (*j)[40]->addWay((*w)[72]);
  (*j)[40]->addLand((*t)[13]);
  (*j)[40]->addLand((*t)[17]);

  (*j)[41]->addWay((*w)[52]);
  (*j)[41]->addWay((*w)[53]);
  (*j)[41]->addWay((*w)[54]);
  (*j)[41]->addLand((*t)[13]);
  (*j)[41]->addLand((*t)[14]);
  (*j)[41]->addLand((*t)[17]);

  (*j)[42]->addWay((*w)[54]);
  (*j)[42]->addWay((*w)[55]);
  (*j)[42]->addWay((*w)[69]);
  (*j)[42]->addLand((*t)[18]);
  (*j)[42]->addLand((*t)[14]);
  (*j)[42]->addLand((*t)[17]);

  (*j)[43]->addWay((*w)[55]);
  (*j)[43]->addWay((*w)[56]);
  (*j)[43]->addWay((*w)[57]);
  (*j)[43]->addLand((*t)[18]);
  (*j)[43]->addLand((*t)[14]);
  (*j)[43]->addLand((*t)[15]);

  (*j)[44]->addWay((*w)[57]);
  (*j)[44]->addWay((*w)[58]);
  (*j)[44]->addWay((*w)[66]);
  (*j)[44]->addLand((*t)[18]);
  (*j)[44]->addLand((*t)[19]);
  (*j)[44]->addLand((*t)[15]);

  (*j)[45]->addWay((*w)[58]);
  (*j)[45]->addWay((*w)[59]);
  (*j)[45]->addWay((*w)[60]);
  (*j)[45]->addLand((*t)[16]);
  (*j)[45]->addLand((*t)[19]);
  (*j)[45]->addLand((*t)[15]);

  (*j)[46]->addWay((*w)[60]);
  (*j)[46]->addWay((*w)[61]);
  (*j)[46]->addWay((*w)[63]);
  (*j)[46]->addLand((*t)[16]);
  (*j)[46]->addLand((*t)[19]);

  (*j)[47]->addWay((*w)[62]);
  (*j)[47]->addWay((*w)[61]);
  (*j)[47]->addLand((*t)[16]);

  (*j)[48]->addWay((*w)[64]);
  (*j)[48]->addWay((*w)[63]);
  (*j)[48]->addLand((*t)[19]);

  (*j)[49]->addWay((*w)[64]);
  (*j)[49]->addWay((*w)[65]);
  (*j)[49]->addLand((*t)[19]);

  (*j)[50]->addWay((*w)[65]);
  (*j)[50]->addWay((*w)[66]);
  (*j)[50]->addWay((*w)[67]);
  (*j)[50]->addLand((*t)[19]);
  (*j)[50]->addLand((*t)[18]);

  (*j)[51]->addWay((*w)[67]);
  (*j)[51]->addWay((*w)[68]);
  (*j)[51]->addLand((*t)[18]);

  (*j)[52]->addWay((*w)[68]);
  (*j)[52]->addWay((*w)[69]);
  (*j)[52]->addWay((*w)[70]);
  (*j)[52]->addLand((*t)[17]);
  (*j)[52]->addLand((*t)[18]);

  (*j)[53]->addWay((*w)[70]);
  (*j)[53]->addWay((*w)[71]);
  (*j)[53]->addLand((*t)[17]);

  (*j)[54]->addWay((*w)[72]);
  (*j)[54]->addWay((*w)[71]);
  (*j)[54]->addLand((*t)[17]);

}

//this constructor creates the board pueces.
Board::Board() {
  map<int, Cross_Section* > jncs;
  // create all the junctions on the board
  for (int i=1; i<=54; i++) {
    jncs[i] = new Cross_Section(i, vector<Path *>(), vector<Tile *>());
  }
  // create all the ways on the board
  map<int, Path* > ways;
  createAllPaths(&ways, &jncs);

  map<int, Tile* > tiles;
  createTiles(&tiles);

  setAllTiles(&ways, &jncs, &tiles);

  map<int, vector<Cross_Section *>> jl;
  jl[1] = {jncs[1], jncs[2], jncs[3], jncs[12], jncs[13], jncs[14]};
  jl[2] = {jncs[3], jncs[4], jncs[5], jncs[12], jncs[11], jncs[10]};
  jl[3]= {jncs[5], jncs[6], jncs[7], jncs[8], jncs[9], jncs[10]};
  jl[4] = {jncs[13], jncs[14], jncs[15], jncs[16], jncs[17], jncs[18]};
  jl[5] = {jncs[11], jncs[12], jncs[13], jncs[18], jncs[19], jncs[20]};
  jl[6] = {jncs[9], jncs[10], jncs[11], jncs[20], jncs[21], jncs[22]};
  jl[7] = {jncs[8], jncs[9], jncs[3], jncs[22], jncs[23], jncs[25]};
  jl[8] = {jncs[16], jncs[17], jncs[35], jncs[36], jncs[38], jncs[37]};
  jl[9] = {jncs[17], jncs[18], jncs[19], jncs[33], jncs[34], jncs[35]};
  jl[10] = {jncs[19], jncs[20], jncs[21], jncs[31], jncs[32], jncs[33]};
  jl[11] = {jncs[21], jncs[22], jncs[23], jncs[29], jncs[30], jncs[31]};
  jl[12] = {jncs[23], jncs[25], jncs[26], jncs[27], jncs[28], jncs[29]};
  jl[13] = {jncs[34], jncs[35], jncs[36], jncs[39], jncs[40], jncs[41]};
  jl[14] = {jncs[32], jncs[33], jncs[34], jncs[41], jncs[42], jncs[43]};
  jl[15] = {jncs[30], jncs[31], jncs[32], jncs[43], jncs[44], jncs[45]};
  jl[16] = {jncs[28], jncs[29], jncs[30], jncs[45], jncs[46], jncs[47]};
  jl[17] = {jncs[40], jncs[41], jncs[42], jncs[52], jncs[53], jncs[54]};
  jl[18] = {jncs[42], jncs[43], jncs[44], jncs[50], jncs[51], jncs[52]};
  jl[19] = {jncs[44], jncs[45], jncs[46], jncs[48], jncs[49], jncs[50]};

  for (int i=1; i<=19; i++) {
    tiles[i]->setCrossSection(jl[i]);
  }

  for (int i=1; i<=54; i++) {
    this->crossSections.push_back(jncs[i]);
  }
  for (int i=1; i<=72; i++) {
    this->paths.push_back(ways[i]);
  }

  for (int i=1; i<=19; i++) {
    this->tiles.push_back(tiles[i]);
  }


  DevelopmentCard *monopol = new DevelopmentCard(MONOPOL);
  DevelopmentCard *bonusPoint = new DevelopmentCard(VICTORY_POINT);
  DevelopmentCard *yearOfPlenty = new DevelopmentCard(YEAR_OF_PLENTY);
  DevelopmentCard *road = new DevelopmentCard(BUILD_2_ROAD);
  DevelopmentCard *knight = new DevelopmentCard(KNIGHT);

  // Populate the map with card instances and their quantities
  eventCard_Deck[monopol] = monopol->getQuantity();
  eventCard_Deck[bonusPoint] = bonusPoint->getQuantity();
  eventCard_Deck[yearOfPlenty] = yearOfPlenty->getQuantity();
  eventCard_Deck[road] = road->getQuantity();
  eventCard_Deck[knight] = knight->getQuantity();
}
