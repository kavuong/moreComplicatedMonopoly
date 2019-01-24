//
// Created by kevin on 2/17/2018.
//

#include "Gamestate.h"
#include "propUpgrade.h"
#include "monopolyGame.h"
int upgradeCost(const Monopoly::Property &aProp, PropUpgrade houseOrHotel) {
  int upgradeCost;
  if (houseOrHotel == PropUpgrade::house){
    upgradeCost = aProp.getHouseCost();
  }
  else if (houseOrHotel == PropUpgrade::hotel){
    upgradeCost = aProp.getHotelCost();
  }
  return upgradeCost;
}
//true -> house false -> hotel
PropUpgrade upHouseOrHotel(Monopoly::Gamestate &gameState, const Monopoly::Property &aProp) {
  int housesBeforeHotels = gameState.rules.getHousesBeforeHotels();
  if (aProp.getNumHouses() < housesBeforeHotels && aProp.getNumHouses() != -1 && housesBeforeHotels > 0)
    return PropUpgrade::house;
  else
    return PropUpgrade::hotel;
}
void upgradeSpace(Monopoly::Gamestate& gameState, Monopoly::Player& currPlayer, int spaceID, int upgradeCost, PropUpgrade houseOrHotel) {
  if (houseOrHotel == PropUpgrade::house)
    gameState.board.getSpace(spaceID).setNumHouses(gameState.board.getSpace(spaceID).getNumHouses() + 1);
  else if (houseOrHotel == PropUpgrade::hotel)
    gameState.board.getSpace(spaceID).setNumHotels(gameState.board.getSpace(spaceID).getNumHotels() + 1);
  currPlayer.setCash(currPlayer.getCash() - upgradeCost);
  currPlayer.setUpgradeCosts(currPlayer.getUpgradeCosts() + upgradeCost);
  // setting numHouses to -1 if hotels are starting
  if (gameState.board.getSpace(spaceID).getNumHotels() > 0)
    gameState.board.getSpace(spaceID).setNumHouses(-1);
}
int numUpgradesInProp(Monopoly::Gamestate &gameState, Monopoly::Space aSpace) {
  if (aSpace.getNumHouses() > 0)
    return aSpace.getNumHouses();
  else if (aSpace.getNumHotels() > 0)
    return gameState.rules.getHousesBeforeHotels() + 1;
  return 0;
}
std::vector<int> spaceUpgradeOptions(Monopoly::Gamestate &gameState, Monopoly::Player& currPlayer, int currPlayerID) {

  std::vector<int> setsOwned;
  std::vector<int> currOwnedSpaces = currPlayer.getSpacesOwned();

  for (unsigned int i = 0; i < currOwnedSpaces.size(); ++i) {
    bool matchesSetsOwned = false;
    int spaceSetID = gameState.board.getSpace(currOwnedSpaces[i]).getProperty().getSetId();
    for (unsigned int j = 0; j < setsOwned.size(); ++j) {
      if (spaceSetID == setsOwned[j]) {
        matchesSetsOwned = true;
        break;
      }
    }
    if (!matchesSetsOwned) {
      setsOwned.push_back(spaceSetID);
    }
  }
  std::vector<int> spaceUpgradeOptions;
  for (unsigned int k = 0; k < setsOwned.size(); ++k) {
    bool ownsSet = doesOwnerOwnSet(gameState, setsOwned[k], currPlayerID);
    if (ownsSet) {
      for (int l = 0; l < gameState.board.getNumBoardSpaces(); ++l) {
        Monopoly::Space currSpace = gameState.board.getSpace(l);
        if (currSpace.getProperty().getSetId() == setsOwned[k]
            && currPlayer.getCash() > upgradeCost(currSpace, upHouseOrHotel(gameState, currSpace)) && currSpace.getNumHotels() < 1) {
          spaceUpgradeOptions.push_back(currSpace.getSpaceID());
        }
      }
    }
  }
  if (gameState.rules.isBuildHousesEvenly())
    spaceUpgradeOptions = organizeSpaceSetUpgrades(gameState, spaceUpgradeOptions, setsOwned);
  return spaceUpgradeOptions;

}
int sellUpgradeCost(const Monopoly::Property &aProp, PropUpgrade houseOrHotel) {
  return 0.5 * upgradeCost(aProp, houseOrHotel);
}
std::vector<int> spaceDowngradeOptions(Monopoly::Gamestate &gameState, Monopoly::Player &currPlayer, int currPlayerID) {
  std::vector<int> setsOwned;
  std::vector<int> currOwnedSpaces = currPlayer.getSpacesOwned();
  for (unsigned int i = 0; i < currOwnedSpaces.size(); ++i) {
    bool matchesSetsOwned = false;
    int spaceSetID = gameState.board.getSpace(currOwnedSpaces[i]).getProperty().getSetId();
    for (unsigned int j = 0; j < setsOwned.size(); ++j) {
      if (spaceSetID == setsOwned[j]) {
        matchesSetsOwned = true;
        break;
      }
    }
    if (!matchesSetsOwned) {
      setsOwned.push_back(spaceSetID);
    }
  }

  std::vector<int> spaceDowngradeOptions;
  for (unsigned int i = 0; i < currOwnedSpaces.size(); ++i){
    if (gameState.board.getSpace(currOwnedSpaces[i]).getNumHouses() > 0 || gameState.board.getSpace(currOwnedSpaces[i]).getNumHotels() > 0){
      spaceDowngradeOptions.push_back(currOwnedSpaces[i]);
    }
  }
  if (gameState.rules.isBuildHousesEvenly())
    spaceDowngradeOptions = organizeSpaceSetDowngrades(gameState, spaceDowngradeOptions, setsOwned);
  return spaceDowngradeOptions;
}
void downgradeSpace(Monopoly::Gamestate &gameState,
                    Monopoly::Player &currPlayer,
                    int spaceID,
                    int downgradeCost,
                    PropUpgrade houseOrHotel) {
  if (houseOrHotel == PropUpgrade::house)
    gameState.board.getSpace(spaceID).setNumHouses(gameState.board.getSpace(spaceID).getNumHouses() - 1);
  else if (houseOrHotel == PropUpgrade::hotel)
    gameState.board.getSpace(spaceID).setNumHotels(gameState.board.getSpace(spaceID).getNumHotels() - 1);
  currPlayer.setCash(currPlayer.getCash() + downgradeCost);
  currPlayer.setUpgradeCosts(currPlayer.getUpgradeCosts() - downgradeCost * 2);
  // setting numHouses to housesBeforeHotels if hotels == 0
  if (houseOrHotel == PropUpgrade::hotel && gameState.board.getSpace(spaceID).getNumHotels() == 0)
    gameState.board.getSpace(spaceID).setNumHouses(gameState.rules.getHousesBeforeHotels());

}
PropUpgrade downHouseOrHotel(Monopoly::Gamestate &gameState, const Monopoly::Property &aProp) {
  int housesBeforeHotels = gameState.rules.getHousesBeforeHotels();
  if (aProp.getNumHouses() <= housesBeforeHotels && aProp.getNumHouses() != -1 && housesBeforeHotels > 0)
    return PropUpgrade::house;
  else
    return PropUpgrade::hotel;
}


