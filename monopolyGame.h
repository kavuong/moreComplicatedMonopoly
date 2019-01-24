//
// Created by kevin on 2/9/2018.
//

#ifndef HOARDING_MONOPOLYGAME_H
#define HOARDING_MONOPOLYGAME_H

#endif //HOARDING_MONOPOLYGAME_H

#include "Gamestate.h"
#include "DiceRoller.h"
#include "Property.h"

void setUpPlayers(Monopoly::Gamestate& gameState, int numPlayers, int startingCash);
bool handleCurrPlayer(Monopoly::Gamestate &gameState,
                      int currPlayerID,
                      Monopoly::DiceRoller &diceRoller,
                      int &doubleRollCount);
int nextPlayer(Monopoly::Gamestate &gameState, int &currPlayerID);
int handleRoll(int spacesToGo, Monopoly::Player& currPlayer, int roll, int numBoardSpaces);
bool doesOwnerOwnSet(Monopoly::Gamestate &gameState, int setID, int ownerLandedOn);
void payOwner(Monopoly::Gamestate &gameState,
              bool setMultiplierExist,
              Monopoly::Player &payingPlayer,
              Monopoly::Player * ownerPlayer,
              Monopoly::Property & propLandedOn);
void handleGo(Monopoly::Gamestate &gameState, Monopoly::Player &player, int goCount);
void leaveGame(Monopoly::Gamestate & gameState, Monopoly::Player & playerToDelete);
void leaveGameBankrupt(Monopoly::Gamestate &gameState, Monopoly::Player &playerToDelete, Monopoly::Player &ownerPlayer, Monopoly::Space spaceLandedOn);
bool isGameOver(Monopoly::Gamestate & gameState);
void gameOver(Monopoly::Gamestate & gameState);
int calcTotAssets(Monopoly::Gamestate &gameState, Monopoly::Player player);
std::vector<int> organizeSpaceSetUpgrades(Monopoly::Gamestate &gameState,
                                          std::vector<int> spaceSet,
                                          std::vector<int> setsOwned);
std::vector<int> organizeSpaceSetDowngrades(Monopoly::Gamestate &gameState,
                                            std::vector<int> spaceSet,
                                            std::vector<int> setsOwned);
std::vector<int> organizeUpDowngradeSet(Monopoly::Gamestate &gameState, std::vector<int> spaceSet);
void sellUpgrades(Monopoly::Gamestate &gameState, Monopoly::Player &currPlayer);
void sellUpgradesBankrupt(Monopoly::Gamestate &gameState,
                          Monopoly::Player &currPlayer,
                          Monopoly::Player *ownerPlayer,
                          Monopoly::Property propLandedOn,
                          int paymentAmount);
