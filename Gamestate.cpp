//
// Created by kevin on 2/5/2018.
//

#include "Gamestate.h"
#include "Property.h"
#include <iostream>
#include <fstream>



Monopoly::Gamestate::Gamestate(char ruleFile[], char boardFile[]) {

  rules = Rules(ruleFile);
  board = Board(boardFile, <#initializer#>);
  this->currPlayer = 1;
  this->numTurns = 0;


}
void Monopoly::Gamestate::printGamestate() {
  for (unsigned int i = 0; i < board.getNumBoardSpaces(); ++i){
    board.getSpacePtr(i)->display();
  }
}
Monopoly::Player& Monopoly::Gamestate::playerWithID(int playerID) {
  std::vector<std::unique_ptr<Player>>::iterator myIterator;
  for (myIterator = playerArr.begin(); myIterator != playerArr.end(); myIterator++){
    if ((**myIterator).playerId == playerID){
      break;
    }
  }
  return **myIterator;
}
std::string Monopoly::Gamestate::playerNameWithID(int playerID) {
  return std::string();
}
Monopoly::Gamestate::Gamestate() {

}






