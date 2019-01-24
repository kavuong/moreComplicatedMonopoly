//
// Created by kevin on 2/5/2018.
//

#include <iostream>
#include "Property.h"
#include "auctioning.h"
int Monopoly::Property::getSetId() const {
  return setId;
}
void Monopoly::Property::setSetId(int setId) {
  Property::setId = setId;
}
int Monopoly::Property::getIntraId() const {
  return intraId;
}
void Monopoly::Property::setIntraId(int intraId) {
  Property::intraId = intraId;
}
const std::string &Monopoly::Property::getName() const {
  return name;
}
void Monopoly::Property::setName(const std::string &name) {
  Property::name = name;
}
int Monopoly::Property::getPropertyCost() const {
  return propertyCost;
}
void Monopoly::Property::setPropertyCost(int propertyCost) {
  Property::propertyCost = propertyCost;
}
int Monopoly::Property::getHouseCost() const {
  return houseCost;
}
void Monopoly::Property::setHouseCost(int houseCost) {
  Property::houseCost = houseCost;
}
int Monopoly::Property::getHotelCost() const {
  return hotelCost;
}
void Monopoly::Property::setHotelCost(int hotelCost) {
  Property::hotelCost = hotelCost;
}
int Monopoly::Property::getRent() const {
  return rent;
}
void Monopoly::Property::setRent(int rent) {
  Property::rent = rent;
}
int Monopoly::Property::getHouseRent() const {
  return houseRent;
}
void Monopoly::Property::setHouseRent(int houseRent) {
  Property::houseRent = houseRent;
}
int Monopoly::Property::getHotelRent() const {
  return hotelRent;
}
void Monopoly::Property::setHotelRent(int hotelRent) {
  Property::hotelRent = hotelRent;
}
int Monopoly::Property::getNumHouses() const {
  return numHouses;
}
void Monopoly::Property::setNumHouses(int numHouses) {
  Property::numHouses = numHouses;
}
int Monopoly::Property::getNumHotels() const {
  return numHotels;
}
void Monopoly::Property::setNumHotels(int numHotels) {
  Property::numHotels = numHotels;
}
Monopoly::Property::Property() {


}
void Monopoly::Property::display() {
  std::cout << Space::getSpaceID() << " | " << name;
  if (owner != NULL)
    std::cout << " | " << owner->name << " | ";
  else
    std::cout << " | None | ";

  // playerArr.size() = number of players currently in the game

  if (this->getNumHouses() > 0) {
    for (int a = 0; a < this->getNumHouses(); ++a)
      std::cout << "h";
  } else if (this->getNumHotels() > 0) {
    for (int a = 0; a < this->getNumHotels(); ++a)
      std::cout << "H";
  }

  if (getPlayersOnSpace().size() > 0){
    for (unsigned int i = 0; i < getPlayersOnSpace().size(); ++i){
      std::cout << "[" << getPlayersOnSpace()[i].name << " : $" << getPlayersOnSpace()[i].getCash() << "]";
      if (i != getPlayersOnSpace().size() - 1)
        std::cout << ",";
    }
  }

}
Monopoly::Player *Monopoly::Property::getOwner() const {
  return owner;
}
void Monopoly::Property::setOwner(Monopoly::Player *owner) {
  Property::owner = owner;
}
void Monopoly::Property::activate(Monopoly::Player &activatingPlayer) {
  char inputChar;
  auto propertyLandedOn = static_cast<Monopoly::Property &>(this);
  Gamestate gameState = *(propertyLandedOn.getGameStatePtr());
  if (propertyLandedOn.getOwner() == nullptr) {
    if (activatingPlayer.getCash() >= propertyLandedOn.getPropertyCost()) {
      std::cout << "Would you like to buy " << propertyLandedOn.name << " for $"
                << propertyLandedOn.getPropertyCost() << "?" << std::endl;
      std::cout << "Rent on " << propertyLandedOn.name << " is $" << propertyLandedOn.getRent() << std::endl;
      std::cout << "Enter y for yes or n for no: ";
      std::cin >> inputChar;
      if (inputChar == 'y') {
        std::vector<int> spacesOwned = activatingPlayer.getSpacesOwned();
        activatingPlayer.setCash(activatingPlayer.getCash() - propertyLandedOn.getPropertyCost());
        propertyLandedOn.setOwner(&activatingPlayer);
        std::cout << activatingPlayer.name << " bought " << propertyLandedOn.name << " for $"
                  << propertyLandedOn.getPropertyCost() << std::endl;
        spacesOwned.push_back(propertyLandedOn.getSpaceID());
        activatingPlayer.setSpacesOwned(spacesOwned);
      } else if (inputChar == 'n') {
        if (gameState.rules.isAuctionProp()) {
          handleAuction(*(propertyLandedOn.getGameStatePtr()), propertyLandedOn);
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


