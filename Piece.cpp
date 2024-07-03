// yehonatan768@gmail.com
#include "Piece.hpp"
#include <stdexcept>

using namespace catan;

// Piece class

Piece::Piece() : _player(nullptr) {
    // Default constructor initializes _player to nullptr
}

Piece::~Piece() {
    // Virtual destructor
}

// Road class

Road::Road() {
    // Default constructor for Road
}

Road::~Road() {
    // Destructor for Road
}

Road::Road(Player *p) {
    // Constructor for Road that sets the owner player
    this->_player = p;
}

Player* Road::getPlayer() {
    // Get the player who owns the road
    return this->_player;
}

const string Road::getType() {
    // Get the type of the asset (Road)
    return "Road";
}

// Town class

Town::Town(Player *p) {
    // Constructor for Town that sets the owner player
    this->_player = p;
}

Town::Town() {
    // Default constructor for Town
}

Town::~Town() {
    // Destructor for Town
}

const string Town::getType() {
    // Get the type of the asset (Town)
    return "Town";
}

Player* Town::getPlayer() {
    // Get the player who owns the town
    return this->_player;
}

// Settlement class

Settlement::Settlement(Player *p) {
    // Constructor for Settlement that sets the owner player
    this->_player = p;
}

Settlement::Settlement() {
    // Default constructor for Settlement
}

Settlement::~Settlement() {
    // Destructor for Settlement
}

const string Settlement::getType() {
    // Get the type of the asset (Settlement)
    return "Settlement";
}

Player* Settlement::getPlayer() {
    // Get the player who owns the settlement
    if (this->_player != nullptr) {
        return this->_player;
    }
    throw logic_error("Error: Tried to access settlement without owner.");
}
