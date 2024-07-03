// yehonatan768@gmail.com
#include "Card.hpp"
#include "Tile.hpp"
#include <map>
#include <vector>
using namespace std;

namespace catan {
/**
 * class Board
 * The game board consists of several components:
 * 1. About 19 different plots of land consisting of 5 different resources and a
 * single desert. Each land has a unique number from 2 to 12.
 * 2. About 54 junctions sitting on the vertices of the plots of land. A
 * settlement or a town can be established on a junction.
 * 3. About 72 ways passing between the intersections. A road can be set up on a
 * way.
 * 4. A pack of development cards. Players can buy development cards.
 */
class Board {
private:
  vector<Cross_Section *> crossSections;        //< Vector of pointers to the junctions on the board
  vector<Path *> paths;                 //< Vector of pointers to the ways on the board
  vector<Tile *> tiles;               //< Vector of pointers to the lands on the board
  map<DevelopmentCard *, int>eventCard_Deck; //< Map of development cards and their quantities

public:
  Board();
  ~Board();
  Cross_Section *getCrossSection(int index);       // Get the junction at the specified index.
  Path *getPath(int index);                 // Get the way at the specified index.
  Tile *getTile(int index);               // Get the land at the specified index.
  DevelopmentCard *generateRandomDevCard(); // Generate a random development card from the pile
  void printBoard();
  void createTiles(map<int, Tile* > *t);
  void createAllPaths(map<int, Path* > *w, map<int, Cross_Section* > *j);
  void addPath(map<int, Path* > *ways, map<int, Cross_Section* > *jncs, int i, int j, int gap);
  void setAllTiles(map<int, Path* > *w, map<int, Cross_Section* > *j, map<int, Tile* > *t);
};
}