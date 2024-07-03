// yehonatan768@gmail.com
#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <vector>
using namespace std;

namespace catan {

class Player; // Forward declaration of Player class

/**
 * @class Piece
 * @brief Abstract base class representing a game piece.
 * 
 * This class serves as the base for game pieces such as Road, Settlement, and Town.
 * It contains a pointer to the owning Player and a string indicating the type of the piece.
 */
class Piece {
public:
  Player *_player; ///< Pointer to the player who owns the Piece.
  string _type;    ///< Type of the Piece.

  /**
   * @brief Pure virtual function to get the type of the Piece.
   * @return The type of the Piece as a string.
   */
  virtual const string getType() = 0;

  /**
   * @brief Constructor for Piece.
   */
  Piece();

  /**
   * @brief Virtual destructor for Piece.
   */
  virtual ~Piece();
};

/**
 * @class Road
 * @brief Represents a road game piece.
 * 
 * Inherits from Piece. Contains functionality specific to roads in the game.
 */
class Road : public Piece {
public:
  /**
   * @brief Default constructor for Road.
   */
  Road();

  /**
   * @brief Constructor for Road that sets the owner player.
   * @param p Pointer to the Player who owns the Road.
   */
  Road(Player *p);

  /**
   * @brief Destructor for Road.
   */
  ~Road();

  /**
   * @brief Get the player who owns the road.
   * @return Pointer to the Player who owns the road.
   */
  Player *getPlayer();

  /**
   * @brief Get the type of the Piece (Road).
   * @return The type of the Piece as a string.
   */
  const string getType() override;
};

/**
 * @class Town
 * @brief Represents a town game piece.
 * 
 * Inherits from Piece. Contains functionality specific to towns in the game.
 */
class Town : public Piece {
public:
  /**
   * @brief Constructor for Town that sets the owner player.
   * @param p Pointer to the Player who owns the Town.
   */
  Town(Player *p);

  /**
   * @brief Default constructor for Town.
   */
  Town();

  /**
   * @brief Destructor for Town.
   */
  ~Town();

  /**
   * @brief Get the type of the Piece (Town).
   * @return The type of the Piece as a string.
   */
  const string getType() override;

  /**
   * @brief Get the player who owns the town.
   * @return Pointer to the Player who owns the town.
   */
  Player *getPlayer();
};

/**
 * @class Settlement
 * @brief Represents a settlement game piece.
 * 
 * Inherits from Piece. Contains functionality specific to settlements in the game.
 */
class Settlement : public Piece {
public:
  /**
   * @brief Constructor for Settlement that sets the owner player.
   * @param p Pointer to the Player who owns the Settlement.
   */
  Settlement(Player *p);

  /**
   * @brief Default constructor for Settlement.
   */
  Settlement();

  /**
   * @brief Destructor for Settlement.
   */
  ~Settlement();

  /**
   * @brief Get the type of the Piece (Settlement).
   * @return The type of the Piece as a string.
   */
  const string getType() override;

  /**
   * @brief Get the player who owns the settlement.
   * @return Pointer to the Player who owns the settlement.
   */
  Player *getPlayer();
};

} // namespace catan

#endif // PIECE_HPP
