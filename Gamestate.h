//
// Created by kevin on 2/5/2018.
//

#ifndef HOARDING_GAMESTATE_H
#define HOARDING_GAMESTATE_H
#include <vector>
#include <memory>
#include "Board.h"
#include "Player.h"
#include "Rules.h"
namespace Monopoly {
  class Gamestate {
   public:
    Gamestate();
    Gamestate(char ruleFile[], char boardFile[]);
    Rules rules;
    std::vector<std::unique_ptr<Player>> playerArr;
    void printGamestate();
    int numPlayers;
    int numOrigPlayers;
    int currPlayer;
    int numTurns;

    Player & playerWithID(int playerID);
    std::string playerNameWithID(int playerID);

    Board board;


   private:
    char ruleFile[];
    char boardFile[];
    std::string ownerInText(int spaceNum);


   public:


  };
}
#endif //HOARDING_GAMESTATE_H
