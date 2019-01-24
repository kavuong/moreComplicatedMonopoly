// BANKRUPT CASE

#include <iostream>
#include <fstream>
#include "Gamestate.h"
#include "monopolyGame.h"

int main(int argc, char ** argv) {
  int numPlayers;
  using namespace Monopoly;

  Gamestate gameState(argv[1], argv[2]);
  for (int i = 0; i < gameState.board.getNumBoardSpaces(); ++i){
    gameState.board.getSpace(i).setGameStatePtr(&gameState);
  }
  printf("Enter how many players will be playing: ");
  std::cin >> numPlayers;
  gameState.numPlayers = numPlayers;
  gameState.numOrigPlayers = numPlayers;
  // UP NEXT vvv
  setUpPlayers(gameState, numPlayers, gameState.rules.getStartingCash());
  // random file

  DiceRoller diceRoller(argv[3]);
  // for when another turn is required: if doubles is rolled or upgrade occurs
  bool anotherTurn = false;
  int doubleRerollCount = 0;
  while (!isGameOver(gameState)){

    gameState.printGamestate();
    anotherTurn = handleCurrPlayer(gameState, gameState.currPlayer, diceRoller, doubleRerollCount);
    if (!anotherTurn)
      nextPlayer(gameState, gameState.currPlayer);
  }
  gameOver(gameState);
  // game over function code
  return 0;
}