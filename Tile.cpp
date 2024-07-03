// yehonatan768@gmail.com
#include "Tile.hpp"
using namespace std;
using namespace catan;

Tile::Tile(cardType type, int num, vector<Town> towns, vector<Road> roads, vector<Settlement> settlements)
    : _resource(type), _num(num), _card(nullptr) {
    // Initialize the resource type and unique identifier
    // Free previous card memory if it exists
    delete this->_card;
    // Create a new Card object if the tile is not a desert
    if (type != DESERT) {
        this->_card = new Card();
    } else {
        this->_card = nullptr;
    }
}

Tile::Tile() {
    // Default constructor does not perform any additional initialization
}

Tile::~Tile() {
    // Destructor to clean up dynamically allocated card memory
    delete this->_card;
}

cardType Tile::getResourceNameOfLand() {
    // Returns the type of resource produced by the tile
    return this->_resource;
}

Road* Tile::getRoad(size_t index) {
    // Returns a pointer to the road at the specified index
    if (index < this->_roads.size()) {
        return &this->_roads[index];
    }
    return nullptr;
}

void Tile::setRoads(Road r) {
    // Adds a road to the tile
    this->_roads.push_back(r);
}

void Tile::printTile() {
    // Prints information about the tile, including its number and resource type
    cout << "Tile number: " << this->_num << ", Tile resource: " << this->_resource << endl;
}

void Tile::setCrossSection(vector<Cross_Section *> junction) {
    // Sets the junctions associated with the tile
    this->crossSections = junction;
}

vector<Cross_Section *> Tile::getJunc() {
    // Returns the junctions associated with the tile
    return this->crossSections;
}

int Tile::getIndex() {
    // Returns the unique identifier (number) of the tile
    return this->_num;
}

Card* Tile::getCard() {
    // Returns the card representing the resource on the tile, creating it if necessary
    if (this->_card != nullptr) {
        return this->_card; // Return the existing card if it has been created
    }
    // Create a new card based on the resource type of the tile
    this->_card = new Card(this->getResourceNameOfLand());
    return this->_card;
}

void Tile::setCard(Card* c) {
    // Sets the card representing the resource on the tile
    this->_card = c;
}

int Tile::getNumber() {
    // Returns the number associated with the tile
    return this->number;
}

void Tile::setNumber(int n) {
    // Sets the number associated with the tile
    this->number = n;
}
