#ifndef CROSS_SECTION_HPP
#define CROSS_SECTION_HPP
#include "Piece.hpp"
#include <iostream>
#include <vector>
using namespace std;

namespace catan {

class Path;
class Tile;
/**
 * @class Cross_Section:
 * This class Represents a junction in the board game
 * **/
class Cross_Section {
private:
  int _num;                           // Number of the junction
  Town *_town;                        // Pointer to a Town
  Settlement *_settelment;            // Pointer to a Settlement
  bool occupied ;                 // Occupied status of the junction
  vector<Path *> paths = {3, nullptr}; // Vector of Path pointers 
  vector<Tile *> tiles = {3, nullptr}; // Vector of Tile pointers (initialized

public:
  Cross_Section();            // Default constructor
  Cross_Section(int num, vector<Path *> ways,vector<Tile *> lands); // Parameterized constructor
  ~Cross_Section();           // Destructor
  int getIndex();          // Get the junction number
  void addWay(Path *w);   // Add a Path to the junction
  void printJunction();  // Print information about the junction
  void addLand(Tile *l); // Add a Tile to the junction
  Tile *getLand1();      // Get the first Tile associated with the junction
  Tile *getLand2();      // Get the second Tile associated with the junction
  Tile *getLand3();      // Get the third Tile associated with the junction
  Path *getPath1();        // Get the first Path associated with the junction
  Path *getPath2();        // Get the second Path associated with the junction
  Path *getPath3();        // Get the third Path associated with the junction
  void setSettlement(Settlement *s); // Set a Settlement at the junction
  void setTown(Town *t);             // Set a Town at the junction
  bool isOccupied();             // Check if the junction is occupied
  void setOccupiedStatus(bool b);       // Set the occupied status of the junction
  Settlement *getSettelment();       // Get the Settlement at the junction
  Town *getTown();                   // Get the Town at the junction
};

/**
 * @class Cross_Section:
 * This class Represents a way in the board game
 * **/

class Path {
private:
  int _num;                      // Number of the way
  vector<Cross_Section *> crossSections; // Vector of Cross_Section pointers
  Road *_road ;                  // Pointer to a Road
  bool is_occupate;              // Occupied status of the way

public:
  Path();                                  // Default constructor
  Path(int n, Cross_Section *j1, Cross_Section *j2); // Parameterized constructor
  ~Path();                                 // Destructor

  Cross_Section *getCrossSection1(); // Get the first Cross_Section associated with the way
  Cross_Section *getCrossSection2(); // Get the second Cross_Section associated with the way
  void setRoad(Road *a);    // Set a Road on the way
  Road *getRoad();          // Get the Road on the way
  int getIndex();             // Get the number of the way
  void printPath();          // Print information about the way
  bool isOccupied();    // Check if the way is occupied
  void setOccupiedStatus(bool b); // Set the occupied status of the way
};
}

#endif 
