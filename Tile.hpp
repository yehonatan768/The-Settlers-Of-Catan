// yehonatan768@gmail.com
#include "Card.hpp"
#include "Cross_Section.hpp"
#include <vector>
using namespace std;

namespace catan {

/// Represents a tile on the game board of Catan.
class Tile {
private:
  cardType _resource;                ///< The type of resource the tile produces.
  int _num;                          ///< Unique identifier for the tile.
  int number;                        ///< Number associated with the tile.
  vector<Road> _roads;               ///< Roads associated with the tile.
  Card *_card;                       ///< Pointer to a Card representing the resource.
  vector<Cross_Section *> crossSections;///< Junctions located on the vertices of the tile.

public:
  /// Constructor for Tile.
  /// \param type The type of resource the tile produces.
  /// \param num Unique identifier for the tile.
  /// \param towns Vector of Town objects on the tile.
  /// \param roads Vector of Road objects on the tile.
  /// \param settlements Vector of Settlement objects on the tile.
  Tile(cardType type, int num, vector<Town> towns, vector<Road> roads, vector<Settlement> settlements);

  /// Default constructor for Tile.
  Tile();

  /// Destructor for Tile.
  ~Tile();

  /// Get the type of resource produced by the tile.
  /// \return The resource type.
  cardType getResourceNameOfLand();

  /// Get a pointer to the road at the specified index.
  /// \param index Index of the road.
  /// \return Pointer to the Road object.
  Road *getRoad(size_t index);

  /// Set the roads associated with the tile.
  /// \param r Road object to add.
  void setRoads(Road r);

  /// Print information about the tile.
  void printTile();

  /// Set the junctions associated with the tile.
  /// \param junction Vector of pointers to Cross_Section objects.
  void setCrossSection(vector<Cross_Section *> junction);

  /// Get the junctions associated with the tile.
  /// \return Vector of pointers to Cross_Section objects.
  vector<Cross_Section *> getJunc();

  /// Get the unique identifier of the tile.
  /// \return The unique identifier.
  int getIndex();

  /// Get the card representing the resource on the tile.
  /// \return Pointer to the Card object.
  Card* getCard();

  /// Set the card representing the resource on the tile.
  /// \param c Pointer to the Card object.
  void setCard(Card* c);

  /// Get the number associated with the tile.
  /// \return The number associated with the tile.
  int getNumber();

  /// Set the number associated with the tile.
  /// \param n The number to set.
  void setNumber(int n);
};

} // namespace catan
