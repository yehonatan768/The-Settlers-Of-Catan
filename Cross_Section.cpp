#include "Cross_Section.hpp"
#include "Tile.hpp"

namespace catan {
// Default constructor for Cross_Section
Cross_Section::Cross_Section() : _num(0) {}

// Parameterized constructor for Cross_Section
// @param num: Cross_Section number
// @param ways: Vector of Path pointers
// @param lands: Vector of Tile pointers
Cross_Section::Cross_Section(int num, vector<Path *> ways, vector<Tile *> lands)
    : _num(num), _town(nullptr), _settelment(nullptr),occupied(false), paths(ways),
      tiles(lands) {}

// Destructor for Cross_Section
Cross_Section::~Cross_Section() {
  // Delete the settlement pointer and the town pointers
  if (_settelment != nullptr) {
    delete _settelment;
  }
  if (_town != nullptr) {
    delete _town;
  }
};

// Get the number of the Cross_Section
int Cross_Section::getIndex() { return _num; }

// Add a Path to the Cross_Section
void Cross_Section::addWay(Path *w) { paths.push_back(w); }

// Add a Tile to the Cross_Section
void Cross_Section::addLand(Tile *l) { this->tiles.push_back(l); }

// Get the first Tile associated with the Cross_Section
Tile *Cross_Section::getLand1() { return !tiles.empty() ? tiles[0] : nullptr; }

// Get the second Tile associated with the Cross_Section
Tile *Cross_Section::getLand2() { return tiles.size() > 1 ? tiles[1] : nullptr; }

// Get the third Tile associated with the Cross_Section
Tile *Cross_Section::getLand3() { return tiles.size() > 2 ? tiles[2] : nullptr; }

// Get the first Path associated with the Cross_Section
Path *Cross_Section::getPath1() { return this->paths[0]; }

// Get the second Path associated with the Cross_Section
Path *Cross_Section::getPath2() { return paths[1] == nullptr ? nullptr : paths[1]; }

// Get the third Path associated with the Cross_Section
Path *Cross_Section::getPath3() { return paths[2] == nullptr ? nullptr : paths[2]; }

// Set a Settlement at the Cross_Section
void Cross_Section::setSettlement(Settlement *s) {
  delete this->_settelment; // Delete existing Settlement
  delete this->_town;       // Delete existing Town
  this->_settelment = s;
  this->_town = nullptr; // Ensure _town is null after assigning Settlement
  this->occupied = true;
}

// Set a Town at the Cross_Section
void Cross_Section::setTown(Town *t) {
  delete this->_settelment;
  delete this->_town;
  this->_town = t;
  this->_settelment = nullptr;
  this->occupied = true;
}

// Check if the Cross_Section is occupied
bool Cross_Section::isOccupied() { return this->occupied; }

// Set the occupied status of the Cross_Section
void Cross_Section::setOccupiedStatus(bool b) { this->occupied = b; }

// Get the Settlement at the Cross_Section
Settlement *Cross_Section::getSettelment() {
  if (this->_settelment != nullptr) {
    return this->_settelment;
  }
  return nullptr;
}

// Get the Town at the Cross_Section
Town *Cross_Section::getTown() {
  if (this->_town != nullptr) {
    return this->_town;
  }
  return nullptr;
}

// Print information about the Cross_Section
void Cross_Section::printJunction() {
  cout << "Cross_Section number: " << this->getIndex() - 1;
  cout << " , On Lands: " << endl;
  if (this->tiles[2] != nullptr) {
    this->tiles[0]->printTile();
    this->tiles[1]->printTile();
    this->tiles[2]->printTile();
  } else if (this->tiles[1] != nullptr) {
    this->tiles[0]->printTile();
    this->tiles[1]->printTile();
  } else {
    this->tiles[0]->printTile();
  }
  cout << endl;
}

Path::Path() {}

Path::Path(int n, Cross_Section *j1, Cross_Section *j2) : _road(nullptr) {
  this->_num = n;
  this->crossSections.push_back(j1);
  this->crossSections.push_back(j2);
  this->is_occupate = false;
}

Path::~Path() { delete _road; }

// Get the first Cross_Section associated with the Path
Cross_Section *Path::getCrossSection1() { return this->crossSections[0]; }

// Get the second Cross_Section associated with the Path
Cross_Section *Path::getCrossSection2() { return this->crossSections[1]; }

// Set a Road on the Path
void Path::setRoad(Road *a) {
  this->_road = a;
  this->is_occupate = true;
}

// Get the Road on the Path
Road *Path::getRoad() { return this->_road; }

// Get the number of the Path
int Path::getIndex() { return this->_num; }

// Print information about the Path
void Path::printPath() {
  cout << "Path number: " << this->getIndex() << " is occupied? "
       << this->isOccupied() << endl;
}

// Check if the Path is occupied
bool Path::isOccupied() { return this->is_occupate; }

// Set the occupied status of the Path
void Path::setOccupiedStatus(bool b) { this->is_occupate = b; }
} 
