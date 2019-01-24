//
// Created by kevin on 2/9/2018.
//

#include <iostream>
#include <memory>
#include <algorithm>
#include "monopolyGame.h"
#include "propUpgrade.h"
#include "auctioning.h"
#include "Property.h"
void setUpPlayers(Monopoly::Gamestate& gameState, int numPlayers, int startingCash) {

  for (int i = 1; i <= numPlayers; ++i){
    std::string playerName;
    printf("Enter the name of player %d: ", i);
    std::cin >> playerName;

    Monopoly::Player addedPlayer = Monopoly::Player(startingCash, playerName, i);
    addedPlayer.setPosition(0);
    addedPlayer.setUpgradeCosts(0);

    auto playerPtr = std::make_unique<Monopoly::Player>(addedPlayer);

    gameState.playerArr.push_back(std::move(playerPtr));
  }
}


bool handleCurrPlayer(Monopoly::Gamestate &gameState,
                      int currPlayerID,
                      Monopoly::DiceRoller &diceRoller,
                      int &doubleRollCount) {
  int playerInput;
  bool doubleRoll = false;
  Monopoly::Player& currPlayer = gameState.playerWithID(currPlayerID);
  std::string playerName = currPlayer.name;
  std::cout << playerName << " please enter your move" << std::endl;
  std::cout << "1 to roll dice" << std::endl;
  std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
  std::cout << "3 to sell a house or hotel" << std::endl;
  std::cout << "4 to leave the game" << std::endl;
  std::cout << "Your move: ";
  std::cin >> playerInput;
  if (playerInput == 1){
    int diceRoll = diceRoller.getDiceRoll(doubleRoll);
    int playerPosition = currPlayer.getPosition();
    int spacesToGo = gameState.board.getNumBoardSpaces() - playerPosition;
    int goCount = handleRoll(spacesToGo, currPlayer, diceRoll, gameState.board.getNumBoardSpaces());
    char inputChar;
    handleGo(gameState, currPlayer, goCount);

    std::cout << playerName << ", you rolled a " << diceRoll << std::endl;

    int newPlayerPosition = currPlayer.getPosition();
    Monopoly::Space& spaceLandedOn = gameState.board.getSpace(newPlayerPosition);
    spaceLandedOn.activate(currPlayer);
    if (spaceLandedOn.type == Monopoly::spaceType::Property) {
      char inputChar;
      auto propertyLandedOn = static_cast<Monopoly::Property &>(spaceLandedOn);
      if (propertyLandedOn.getOwner() == nullptr) {
        if (currPlayer.getCash() >= propertyLandedOn.getPropertyCost()) {
          std::cout << "Would you like to buy " << propertyLandedOn.name << " for $"
                    << propertyLandedOn.getPropertyCost() << "?" << std::endl;
          std::cout << "Rent on " << propertyLandedOn.name << " is $" << propertyLandedOn.getRent() << std::endl;
          std::cout << "Enter y for yes or n for no: ";
          std::cin >> inputChar;
          if (inputChar == 'y') {
            std::vector<int> spacesOwned = currPlayer.getSpacesOwned();
            currPlayer.setCash(currPlayer.getCash() - propertyLandedOn.getPropertyCost());
            propertyLandedOn.setOwner(&currPlayer);
            std::cout << playerName << " bought " << propertyLandedOn.name << " for $"
                      << propertyLandedOn.getPropertyCost() << std::endl;
            spacesOwned.push_back(propertyLandedOn.getSpaceID());
            currPlayer.setSpacesOwned(spacesOwned);
          } else if (inputChar == 'n') {
            if (gameState.rules.isAuctionProp()) {
              handleAuction(gameState, propertyLandedOn);
            }
          }
        } else {
          std::cout << currPlayer.name << ", you don't have enough money to afford "
                    << propertyLandedOn.name << "." << std::endl;
          std::cout << propertyLandedOn.name << " costs $" << propertyLandedOn.getPropertyCost()
                    << " but you only have $" << currPlayer.getCash() << std::endl;
        }
      } else if (propertyLandedOn.getOwner()->playerId != currPlayer.playerId) {
        int setIDLandedOn = propertyLandedOn.getSetId();
        bool doesMultiplierExist = doesOwnerOwnSet(gameState, setIDLandedOn, propertyLandedOn.getOwner()->playerId);
        payOwner(gameState,
                 doesMultiplierExist,
                 currPlayer,
                 propertyLandedOn.getOwner(),
                 propertyLandedOn);
      } else if (currPlayerID == propertyLandedOn.getOwner()->playerId)
        std::cout << currPlayer.name << ", you landed on " << propertyLandedOn.name << " which you already own"
                  << std::endl;
      if (!doubleRoll || doubleRollCount == gameState.rules.getMaxDoubleRerolls()) {
        gameState.numTurns++;
        doubleRollCount = 0;
        return false;
      } else {
        doubleRollCount++;
        return true;
      }
    }
  }
  else if (playerInput == 2){
    // buy upgrade
    std::vector<int> currOwnedSpaces = currPlayer.getSpacesOwned();
    if (!currOwnedSpaces.empty()) {
      std::vector<int> spaceUpgrades;
      spaceUpgrades = organizeUpDowngradeSet(gameState, spaceUpgradeOptions(gameState, currPlayer, currPlayerID));

      if (spaceUpgrades.size() > 0) {
        int userInput;
        std::cout << "Which property do you want to upgrade?" << std::endl;
        for (unsigned int m = 0; m < spaceUpgrades.size(); ++m) {
          Monopoly::Space space = gameState.board.getSpace(spaceUpgrades[m]);
          std::cout << m << ". " << space.getName();
          std::cout << " [$" << upgradeCost(space, upHouseOrHotel(gameState, space)) << "]" << std::endl;
        }
        std::cout << "Your choice:";
        std::cin >> userInput;
        Monopoly::Space spaceToUpgrade = gameState.board.getSpace(spaceUpgrades[userInput]);
        int upgradeSpaceID = spaceToUpgrade.getSpaceID();

        upgradeSpace(gameState,
                     currPlayer,
                     upgradeSpaceID,
                     upgradeCost(spaceToUpgrade, upHouseOrHotel(gameState, spaceToUpgrade)),
                     upHouseOrHotel(gameState, spaceToUpgrade));
      } else {
        std::cout << "You don't have any properties that you can upgrade" << std::endl;
      }
    }
    else {
      std::cout << "You don't have any properties that you can upgrade" << std::endl;
    }
    return true;
    // must build evenly
  }
  else if (playerInput == 3){
    // sell upgrade
    sellUpgrades(gameState, currPlayer);
    return true;
  }
  else if (playerInput == 4){
    leaveGame(gameState, currPlayer);
    gameState.numTurns++;
    return false;
  }
  return NULL;

}
int nextPlayer(Monopoly::Gamestate &gameState, int &currPlayerID) {
  bool isValidPlayer = false;
  while (!isValidPlayer) {
    currPlayerID++;
    if (currPlayerID == gameState.numOrigPlayers + 1)
      currPlayerID = 1;
    if (gameState.playerWithID(currPlayerID).isInGame())
      isValidPlayer = true;
  }
  return currPlayerID;
}

// function handles position after dice roll; returns amount of times GO is PASSED (not landed on)
int handleRoll(int spacesToGo, Monopoly::Player& currPlayer, int roll, int numBoardSpaces) {
  int goCount = 0;
  int currPosition = currPlayer.getPosition();
  if (roll < spacesToGo)
    currPlayer.setPosition(currPosition + roll);
  else if (roll == spacesToGo)
    currPlayer.setPosition(0);

  else{
    currPlayer.setPosition((currPosition + roll) % numBoardSpaces);
    if (spacesToGo != numBoardSpaces) {
      roll -= spacesToGo;
      while (roll > 0) {
        roll -= numBoardSpaces;
        goCount++;
      }
      if (currPosition == 0)
        goCount--;
    }
    else {
      goCount = roll / spacesToGo - 1;
    }
  }
  return goCount;
}
bool doesOwnerOwnSet(Monopoly::Gamestate &gameState, int setID, int ownerLandedOn) {
  bool setMultiplierApplies = true;
  std::vector<int> spaceSet;
  for (int i = 1; i < gameState.board.getNumBoardSpaces(); ++i){
    auto property = static_cast<Monopoly::Property &>(gameState.board.getSpace(i));
    int spaceSetID = property.getSetId();
    if (spaceSetID == setID)
      spaceSet.push_back(i);
  }
  // comparing all owners of a set to owner of first prop of a set
  for (unsigned int j = 0; j < spaceSet.size(); ++j){
    auto property = static_cast<Monopoly::Property &>(gameState.board.getSpace(spaceSet[j]));

    if (property.getOwner()->playerId == ownerLandedOn)
      continue;
    else{
      setMultiplierApplies = false;
      break;
    }
  }
  return setMultiplierApplies;
}
void payOwner(Monopoly::Gamestate &gameState,
              bool setMultiplierExist,
              Monopoly::Player &payingPlayer,
              Monopoly::Player *ownerPlayer,
              Monopoly::Property &propLandedOn) {
  int paymentAmount;
  int rent;
  int noImprovRent = propLandedOn.getRent();
  int houseRent = propLandedOn.getNumHouses() * propLandedOn.getHouseRent();
  int hotelRent = propLandedOn.getNumHotels() * propLandedOn.getHotelRent();
  if (propLandedOn.getNumHouses() == 0 && propLandedOn.getNumHotels() == 0)
    rent = noImprovRent;
  else if (propLandedOn.getNumHouses() > 0)
    rent = houseRent * (1 << (propLandedOn.getNumHouses() - 1));
  else if (propLandedOn.getNumHotels() > 0)
    rent = hotelRent;

  if (setMultiplierExist)
    paymentAmount = rent * gameState.rules.getPropertyMultiplier();
  else
    paymentAmount = rent;
  // bankrupt case - HANDLE LATER asdf
  if (paymentAmount > payingPlayer.getCash()) {
    sellUpgradesBankrupt(gameState, payingPlayer, ownerPlayer, propLandedOn, paymentAmount);
  }
  else
  {
    payingPlayer.setCash(payingPlayer.getCash() - paymentAmount);
    (*ownerPlayer).setCash((*ownerPlayer).getCash() + paymentAmount);
    std::cout << payingPlayer.name << " paid " << ownerPlayer->name << " $" << paymentAmount << " for landing on " << propLandedOn.name << std::endl;
  }
}
void handleGo(Monopoly::Gamestate &gameState, Monopoly::Player &player, int goCount) {
  int passGoCash = gameState.board.getSpace(0).getGoCash();
  player.setCash(player.getCash() + goCount * passGoCash);
  if (player.getPosition() == 0)
    player.setCash(player.getCash() + passGoCash * gameState.rules.getGoLandingMultiplier());
}

void leaveGame(Monopoly::Gamestate &gameState, Monopoly::Player & playerToDelete) {
  gameState.numPlayers--;
  playerToDelete.setInGame(false);
  playerToDelete.setCash(0);
  for (int i = 1; i < gameState.board.getNumBoardSpaces(); ++i){
    if (gameState.board.getSpace(i).getOwner() == playerToDelete.playerId){
      gameState.board.getSpace(i).setOwner(-1);
      gameState.board.getSpace(i).setNumHouses(0);
      gameState.board.getSpace(i).setNumHotels(0);
    }
  }
  std::vector<int> deletedPlayerSpaces = playerToDelete.getSpacesOwned();
  deletedPlayerSpaces.clear();
  playerToDelete.setSpacesOwned(deletedPlayerSpaces);
}
bool isGameOver(Monopoly::Gamestate &gameState) {
  return gameState.numPlayers <= gameState.rules.getPlayersLeftToEnd() || (gameState.rules.getTurnLimit() != -1 && gameState.numTurns >= gameState.rules.getTurnLimit());
}
void gameOver(Monopoly::Gamestate &gameState) {
  gameState.printGamestate();
  std::vector<Monopoly::Player> playersLeft;
  std::vector<std::string> winnerNames;
  for (int i = 0; i < gameState.numOrigPlayers; ++i){
    if (gameState.playerArr[i]->isInGame())
      playersLeft.push_back(*(gameState.playerArr[i]));
  }
  if (playersLeft.size() == 1){
    winnerNames.push_back(playersLeft.at(0).name);
  }
  else {
    int maxNetWorth = calcTotAssets(gameState, playersLeft[0]);
    for (unsigned int j = 1; j < playersLeft.size(); ++j){
      int totAssets = calcTotAssets(gameState, playersLeft[j]);
      if (totAssets > maxNetWorth)
        maxNetWorth = totAssets;
    }
    for (unsigned int k = 0; k < playersLeft.size(); ++k){
      if (calcTotAssets(gameState, playersLeft[k]) == maxNetWorth)
        winnerNames.push_back(playersLeft[k].name);
    }
  }
  std::cout << "The winners are" << std::endl;
  for (unsigned int k = 0; k < winnerNames.size(); ++k)
    std::cout << winnerNames[k] << std::endl;
}
int calcTotAssets(Monopoly::Gamestate &gameState, Monopoly::Player player) {
  int propAssets = 0;
  for (int i = 1; i < gameState.board.getNumBoardSpaces(); ++i){
    Monopoly::Space boardSpace = gameState.board.getSpace(i);
    if (boardSpace.getOwner() == player.playerId)
      propAssets += boardSpace.getProperty().getPropertyCost();
  }
  int upgradeAssets = player.getUpgradeCosts();
  return player.getCash() + propAssets + upgradeAssets;
}
void leaveGameBankrupt(Monopoly::Gamestate &gameState,
                       Monopoly::Player &playerToDelete,
                       Monopoly::Player *ownerPlayer,
                       Monopoly::Property &propLandedOn) {
  gameState.numPlayers--;
  ownerPlayer->setCash(ownerPlayer->getCash() + playerToDelete.getCash());

  for (int i = 0; i < playerToDelete.getSpacesOwned().size(); ++i){
    auto boardSpace = static_cast<Monopoly::Property &>(gameState.board.getSpace(i));
    boardSpace.setOwner(ownerPlayer);
    std::vector<int> ownerSpacesOwned = ownerPlayer->getSpacesOwned();
    ownerSpacesOwned.push_back(boardSpace.getSpaceID());
    ownerPlayer->setSpacesOwned(ownerSpacesOwned);
  }

  ownerPlayer->setUpgradeCosts(ownerPlayer->getUpgradeCosts() + playerToDelete.getUpgradeCosts());
  std::vector<int> deletedPlayerSpaces = playerToDelete.getSpacesOwned();
  deletedPlayerSpaces.clear();
  playerToDelete.setSpacesOwned(deletedPlayerSpaces);
  playerToDelete.setCash(0);
  playerToDelete.setInGame(false);
  playerToDelete.setUpgradeCosts(0);
  std::cout << playerToDelete.name << " went bankrupt to " << ownerPlayer->name << " for landing on " << propLandedOn.name << std::endl;
}
std::vector<int> organizeSpaceSetUpgrades(Monopoly::Gamestate &gameState,
                                          std::vector<int> spaceSet,
                                          std::vector<int> setsOwned) {
  std::vector<int> newSet;

  int minUpgrades;

  for (unsigned int k = 0; k < setsOwned.size(); ++k){
    std::vector<int> spacesWithCertID;
    for (unsigned int l = 0; l < spaceSet.size(); l++){
      Monopoly::Space spaceReferred = gameState.board.getSpace(spaceSet[l]);
      if (setsOwned[k] == spaceReferred.getProperty().getSetId())
        spacesWithCertID.push_back(spaceSet[l]);
    }
    if (spacesWithCertID.size() > 1) {
      minUpgrades = numUpgradesInProp(gameState, gameState.board.getSpace(spacesWithCertID[0]));
      for (unsigned int i = 1; i < spacesWithCertID.size(); ++i) {
        Monopoly::Space spaceReferred = gameState.board.getSpace(spacesWithCertID[i]);
        int numUpgrades = numUpgradesInProp(gameState, spaceReferred);
        if (numUpgrades < minUpgrades)
          minUpgrades = numUpgrades;
      }
    } else if (spacesWithCertID.size() == 1) {
      minUpgrades = numUpgradesInProp(gameState, gameState.board.getSpace(spacesWithCertID[0]));
    }

    for (unsigned int j = 0; j < spacesWithCertID.size(); ++j){
      Monopoly::Space spaceReferred = gameState.board.getSpace(spacesWithCertID[j]);
      if (numUpgradesInProp(gameState, spaceReferred) == minUpgrades){
        newSet.push_back(spacesWithCertID[j]);
      }
    }
  }

  return newSet;
}
std::vector<int> organizeSpaceSetDowngrades(Monopoly::Gamestate &gameState,
                                            std::vector<int> spaceSet,
                                            std::vector<int> setsOwned) {
  std::vector<int> newSet;

  int maxUpgrades;

  for (unsigned int k = 0; k < setsOwned.size(); ++k){
    std::vector<int> spacesWithCertID;
    for (unsigned int l = 0; l < spaceSet.size(); l++){
      Monopoly::Space spaceReferred = gameState.board.getSpace(spaceSet[l]);
      if (setsOwned[k] == spaceReferred.getProperty().getSetId())
        spacesWithCertID.push_back(spaceSet[l]);
    }
    if (spacesWithCertID.size() > 1) {
      maxUpgrades = numUpgradesInProp(gameState, gameState.board.getSpace(spacesWithCertID[0]));
      for (unsigned int i = 1; i < spacesWithCertID.size(); ++i) {
        Monopoly::Space spaceReferred = gameState.board.getSpace(spacesWithCertID[i]);
        int numUpgrades = numUpgradesInProp(gameState, spaceReferred);
        if (numUpgrades > maxUpgrades)
          maxUpgrades = numUpgrades;
      }
    } else if (spacesWithCertID.size() == 1) {
      maxUpgrades = numUpgradesInProp(gameState, gameState.board.getSpace(spacesWithCertID[0]));
    }
    for (unsigned int j = 0; j < spacesWithCertID.size(); ++j){
      Monopoly::Space spaceReferred = gameState.board.getSpace(spacesWithCertID[j]);
      if (numUpgradesInProp(gameState, spaceReferred) == maxUpgrades){
        newSet.push_back(spacesWithCertID[j]);
      }
    }
  }
  return newSet;
}
std::vector<int> organizeUpDowngradeSet(Monopoly::Gamestate &gameState, std::vector<int> spaceSet) {
  // vector that contains dummy values which will help with ordering the spaces
  // each entry of values = 100 * setID + intraID;
  std::vector<int> values;
  std::vector<int> newSet;
  for (unsigned int i = 0; i < spaceSet.size(); ++i){
    auto propReferenced = static_cast<Monopoly::Property &>(gameState.board.getSpace(spaceSet[i]));
    values.push_back(100 * propReferenced.getSetId() + propReferenced.getIntraId());
  }
  std::sort(values.begin(), values.end());
  for (unsigned int j = 0; j < values.size(); ++j){
    for (unsigned int k = 0; k < spaceSet.size(); ++k){
      auto propReferenced = static_cast<Monopoly::Property &>(gameState.board.getSpace(spaceSet[k]));
      int value = 100 * propReferenced.getSetId() + propReferenced.getIntraId();
      if (value == values[j])
        newSet.push_back(spaceSet[k]);
    }
  }
  return newSet;
}
void sellUpgrades(Monopoly::Gamestate &gameState, Monopoly::Player &currPlayer) {
  std::vector<int> currOwnedSpaces = currPlayer.getSpacesOwned();
  if (!currOwnedSpaces.empty()) {
    std::vector<int> spaceDowngrades;
    spaceDowngrades = organizeUpDowngradeSet(gameState, spaceDowngradeOptions(gameState, currPlayer, currPlayer.playerId));

    if (spaceDowngrades.size() > 0) {
      int userInput;
      std::cout << "Which property do you want to downgrade?" << std::endl;
      for (unsigned int m = 0; m < spaceDowngrades.size(); ++m) {
        Monopoly::Space space = gameState.board.getSpace(spaceDowngrades[m]);
        std::cout << m << ". " << space.getName();
        std::cout << " [$" << sellUpgradeCost(space, upHouseOrHotel(gameState, space)) << "]" << std::endl;
      }
      std::cout << "Your choice:";
      std::cin >> userInput;
      Monopoly::Space spaceToDowngrade = gameState.board.getSpace(spaceDowngrades[userInput]);
      int downgradeSpaceID = spaceToDowngrade.getSpaceID();

      downgradeSpace(gameState,
                     currPlayer,
                     downgradeSpaceID,
                     sellUpgradeCost(spaceToDowngrade, upHouseOrHotel(gameState, spaceToDowngrade)),
                     downHouseOrHotel(gameState, spaceToDowngrade));
    } else {
      std::cout << "You don't have any upgrades that you can sell" << std::endl;
    }
  }
  else {
    std::cout << "You don't have any upgrades that you can sell" << std::endl;
  }
}
void sellUpgradesBankrupt(Monopoly::Gamestate &gameState,
                          Monopoly::Player &currPlayer,
                          Monopoly::Player * ownerPlayer,
                          Monopoly::Property propLandedOn,
                          int paymentAmount) {
  // copy and paste sellUpgrades code then modify it to fit bankrupt case
  std::vector<int> currOwnedSpaces = currPlayer.getSpacesOwned();
  if (!currOwnedSpaces.empty()) {
    std::vector<int> spaceDowngrades;

    int leftToPay = paymentAmount - currPlayer.getCash();
    bool actuallyBankrupt = false;
    while (leftToPay > 0) {
      spaceDowngrades =
          organizeUpDowngradeSet(gameState, spaceDowngradeOptions(gameState, currPlayer, currPlayer.playerId));
      if (spaceDowngrades.size() > 0) {
        int userInput;
        std::cout << "You have $" << currPlayer.getCash() << " but you owe $" << paymentAmount << std::endl;
        std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
        for (unsigned int m = 0; m < spaceDowngrades.size(); ++m) {
          auto prop = static_cast<Monopoly::Property &>(gameState.board.getSpace(spaceDowngrades[m]));
          std::cout << m << ". " << prop.name;
          std::cout << " [$" << sellUpgradeCost(prop, upHouseOrHotel(gameState, prop)) << "]" << std::endl;
        }
        std::cout << "Your choice:";
        std::cin >> userInput;
        Monopoly::Space spaceToDowngrade = gameState.board.getSpace(spaceDowngrades[userInput]);
        auto propToDowngrade = static_cast<Monopoly::Property &>(spaceToDowngrade);
        int downgradeSpaceID = spaceToDowngrade.getSpaceID();

        downgradeSpace(gameState,
                       currPlayer,
                       downgradeSpaceID,
                       sellUpgradeCost(propToDowngrade, upHouseOrHotel(gameState, propToDowngrade)),
                       downHouseOrHotel(gameState, propToDowngrade));
        leftToPay -= sellUpgradeCost(propToDowngrade, upHouseOrHotel(gameState, propToDowngrade));
      } else {
        leaveGameBankrupt(gameState, currPlayer, ownerPlayer, propLandedOn);
        actuallyBankrupt = true;
        break;
      }
    }
    // if actually bankrupt, don't pay anything else
    if (!actuallyBankrupt) {
      std::cout << currPlayer.name << " paid " << ownerPlayer->name << " $" << paymentAmount << " for landing on "
                << propLandedOn.name << std::endl;
      currPlayer.setCash(currPlayer.getCash() - paymentAmount);
      ownerPlayer->setCash(ownerPlayer->getCash() + paymentAmount);
    }
  }
  else {
    leaveGameBankrupt(gameState, currPlayer, ownerPlayer, propLandedOn);
  }
}
