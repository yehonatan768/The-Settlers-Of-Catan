// yehonatan768@gmail.com
#include "Catan.hpp"
#include <iostream>

using namespace catan;

int main() {
    // Set up players
    Player *p1 = new Player("Jhon");
    Player *p2 = new Player("Noy");
    Player *p3 = new Player("Moshe");
    
    // Set up the game instance
    Catan *catan = new Catan();
    catan->setPlayers(p1, p2, p3);
    
    // Set up the game board
    Board *board = new Board();
    p1->setBoard(board);
    p2->setBoard(board);
    p3->setBoard(board);
    
    // Start the game: each player places 2 settlements and 2 roads
    catan->StartTheGame();
    board->getCrossSection(12)->printJunction(); // Example of printing a junction
    
    p1->placeFirstSettlement(9);
    p1->placeFirstRoad(10);
    
    p2->placeFirstSettlement(29);
    p2->placeFirstRoad(37);
    
    p3->placeFirstSettlement(33);
    p3->placeFirstRoad(42);
    p3->placeFirstSettlement(41);
    p3->placeFirstRoad(53);
    
    p2->placeFirstSettlement(20);
    p2->placeFirstRoad(25);
    
    p1->placeFirstSettlement(11);
    p1->placeFirstRoad(14);
    
    // Print number of cards for each player
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Player cards after initial setup:\n";
    p1->printCard();
    p2->printCard();
    p3->printCard();
    
    // Game rounds
    for (int round = 1; round <= 20; ++round) {
        std::cout << "\n--------------------------------------------------\n";
        std::cout << "ROUND #" << round << "\n";
        
        // Player actions for each round
        try {
          p1->rollDices();
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        try {
          p1->placeRoad(15); // p1 places road
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        try {
            p3->rollDices(); // p3 tries to roll dice but it's not his turn
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }

        try {
          p2->rollDices();
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        try {
          p2->placeRoad(27); // p2 places road
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        try {
            p3->rollDices();
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        try {
            p3->placeRoad(1); // p3 tries to place road in an illegal place
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
        
        // Print player cards after each round
        std::cout << "Player cards after ROUND #" << round << ":\n";
        p1->printCard();
        p2->printCard();
        p3->printCard();
        
        // Print player victory points after each round
        std::cout << "Player victory points after ROUND #" << round << ":\n";
        std::cout << p1->getName() << ": " << p1->getVictoryPoints() << " points\n";
        std::cout << p2->getName() << ": " << p2->getVictoryPoints() << " points\n";
        std::cout << p3->getName() << ": " << p3->getVictoryPoints() << " points\n";
    }
    
    // Clean up and delete objects
    delete p1;
    delete p2;
    delete p3;
    delete catan;
    delete board;
    
    return 0;
}
