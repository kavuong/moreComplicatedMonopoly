//
// Created by kevin on 2/17/2018.
//

#ifndef HOARDING_PROPUPGRADE_H
#define HOARDING_PROPUPGRADE_H

#endif //HOARDING_PROPUPGRADE_H
#include "Gamestate.h"
#include "Property.h"

enum class PropUpgrade {house, hotel};
int upgradeCost(const Monopoly::Property &aProp, PropUpgrade houseOrHotel);
int sellUpgradeCost(const Monopoly::Property &aProp, PropUpgrade houseOrHotel);
PropUpgrade upHouseOrHotel(Monopoly::Gamestate &gameState, const Monopoly::Property &aProp);
PropUpgrade downHouseOrHotel(Monopoly::Gamestate &gameState, const Monopoly::Property &aProp);

void upgradeSpace(Monopoly::Gamestate& gameState, Monopoly::Player& currPlayer, int spaceID, int upgradeCost, PropUpgrade houseOrHotel);
void downgradeSpace(Monopoly::Gamestate &gameState,
                    Monopoly::Player &currPlayer,
                    int spaceID,
                    int downgradeCost,
                    PropUpgrade houseOrHotel);
int numUpgradesInProp(Monopoly::Gamestate &gameState, Monopoly::Space aSpace);
std::vector<int> spaceUpgradeOptions(Monopoly::Gamestate &gameState, Monopoly::Player& currPlayer, int currPlayerID);
std::vector<int> spaceDowngradeOptions(Monopoly::Gamestate &gameState, Monopoly::Player& currPlayer, int currPlayerID);