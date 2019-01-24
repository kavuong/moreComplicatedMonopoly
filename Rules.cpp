//
// Created by kevin on 2/5/2018.
//

#include <string>
#include <iostream>
#include <fstream>
#include "Rules.h"
#include "Gamestate.h"
int Monopoly::Rules::getStartingCash() const {
  return startingCash;
}
void Monopoly::Rules::setStartingCash(int startingCash) {
  Rules::startingCash = startingCash;
}
int Monopoly::Rules::getTurnLimit() const {
  return turnLimit;
}
void Monopoly::Rules::setTurnLimit(int turnLimit) {
  Rules::turnLimit = turnLimit;
}
int Monopoly::Rules::getPlayersLeftToEnd() const {
  return playersLeftToEnd;
}
void Monopoly::Rules::setPlayersLeftToEnd(int playersLeftToEnd) {
  Rules::playersLeftToEnd = playersLeftToEnd;
}
int Monopoly::Rules::getPropertyMultiplier() const {
  return propertyMultiplier;
}
void Monopoly::Rules::setPropertyMultiplier(int propertyMultiplier) {
  Rules::propertyMultiplier = propertyMultiplier;
}
int Monopoly::Rules::getHousesBeforeHotels() const {
  return housesBeforeHotels;
}
void Monopoly::Rules::setHousesBeforeHotels(int housesBeforeHotels) {
  Rules::housesBeforeHotels = housesBeforeHotels;
}

void Monopoly::Rules::setBuildHousesEvenly(bool buildHousesEvenly) {
  Rules::buildHousesEvenly = buildHousesEvenly;
}
bool Monopoly::Rules::isMoneyInFreeParking() const {
  return moneyInFreeParking;
}
void Monopoly::Rules::setMoneyInFreeParking(bool moneyInFreeParking) {
  Rules::moneyInFreeParking = moneyInFreeParking;
}
bool Monopoly::Rules::isAuctionProp() const {
  return auctionProp;
}
void Monopoly::Rules::setAuctionProp(bool auctionProp) {
  Rules::auctionProp = auctionProp;
}
int Monopoly::Rules::getGoLandingMultiplier() const {
  return goLandingMultiplier;
}
void Monopoly::Rules::setGoLandingMultiplier(int goLandingMultiplier) {
  Rules::goLandingMultiplier = goLandingMultiplier;
}
Monopoly::Rules::Rules(char * ruleFile) {
  if (ruleFile != NULL) {
    std::ifstream inFS;
    int startingCash;
    int turnLimit;
    int playersToEnd;
    int setMultiplier;
    int housesBeforeHotels;
    std::string buildHousesInput;
    std::string freeParkingInput;
    std::string auctionInput;
    int goLandingMultiplier;
    int maxDoubleRerolls;
    bool buildHousesEvenly;
    bool moneyInFreeParking;
    bool auctionProp;

    inFS.open(ruleFile);
    inFS.ignore(1000, ':');
    inFS >> startingCash;
    inFS.ignore(1000, ':');
    inFS >> turnLimit;
    inFS.ignore(1000, ':');
    inFS >> playersToEnd;
    inFS.ignore(1000, ':');
    inFS >> setMultiplier;
    inFS.ignore(1000, ':');
    inFS >> housesBeforeHotels;
    inFS.ignore(1000, ':');
    inFS >> buildHousesInput;
    inFS.ignore(1000, ':');
    inFS >> freeParkingInput;
    inFS.ignore(1000, ':');
    inFS >> auctionInput;
    inFS.ignore(1000, ':');
    inFS >> goLandingMultiplier;
    inFS.ignore(1000, ':');
    inFS >> maxDoubleRerolls;

    buildHousesEvenly = makeLowerCase(buildHousesInput);
    moneyInFreeParking = makeLowerCase(freeParkingInput);
    auctionProp = makeLowerCase(auctionInput);

    setStartingCash(startingCash);
    setTurnLimit(turnLimit);
    setPlayersLeftToEnd(playersToEnd);
    setPropertyMultiplier(setMultiplier);
    setHousesBeforeHotels(housesBeforeHotels);
    setBuildHousesEvenly(buildHousesEvenly);
    setMoneyInFreeParking(moneyInFreeParking);
    setAuctionProp(auctionProp);
    setGoLandingMultiplier(goLandingMultiplier);
    setMaxDoubleRerolls(maxDoubleRerolls);
  }

}
bool Monopoly::Rules::makeLowerCase(std::string inputStr) {
  for (unsigned int i = 0; i < inputStr.length(); ++i)
    inputStr[i] = tolower(inputStr[i]);
  if (inputStr == "yes")
    return true;
  else
    return false;
}
Monopoly::Rules::Rules() {

}
bool Monopoly::Rules::isBuildHousesEvenly() const {
  return buildHousesEvenly;
}
int Monopoly::Rules::getMaxDoubleRerolls() const {
  return maxDoubleRerolls;
}
void Monopoly::Rules::setMaxDoubleRerolls(int maxDoubleRerolls) {
  Rules::maxDoubleRerolls = maxDoubleRerolls;
}
