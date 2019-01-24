//
// Created by kevin on 2/5/2018.
//

#include <iostream>
#include "Space.h"
#include "Board.h"
#include "Property.h"
#include "Gamestate.h"
/*
Monopoly::Space::Space(int goCash, std::string name) {
  setType(true);
  setGoCash(goCash);
  setName(name);

}

Monopoly::Space::Space(Property aProperty, std::string name) {
  setType(false);
  setProperty(aProperty);
  setName(name);
}

bool Monopoly::Space::isType() const {
  return type;
}
void Monopoly::Space::setType(bool type) {
  Space::type = type;
}
const Monopoly::Property &Monopoly::Space::getProperty() const {
  return property;
}
void Monopoly::Space::setProperty(const Monopoly::Property &property) {
  Space::property = property;
}
int Monopoly::Space::getGoCash() const {
  return goCash;
}
void Monopoly::Space::setGoCash(int goCash) {
  Space::goCash = goCash;
}

const std::string &Monopoly::Space::getName() const {
  return name;
}
void Monopoly::Space::setName(const std::string &name) {
  Space::name = name;
}
 */
int Monopoly::Space::getOwner() const {
  return owner;
}
void Monopoly::Space::setOwner(int owner) {
  Space::owner = owner;
}
int Monopoly::Space::getSpaceID() const {
  return spaceID;
}
void Monopoly::Space::setSpaceID(int spaceID) {
  Space::spaceID = spaceID;
}
/*
int Monopoly::Space::getNumHouses() const {
  return numHouses;
}
void Monopoly::Space::setNumHouses(int numHouses) {
  Space::numHouses = numHouses;
}
int Monopoly::Space::getNumHotels() const {
  return numHotels;
}
void Monopoly::Space::setNumHotels(int numHotels) {
  Space::numHotels = numHotels;
}
 */
Monopoly::Space::Space() {

}
void Monopoly::Space::display() {


}
const std::vector<Monopoly::Player> &Monopoly::Space::getPlayersOnSpace() const {
  return playersOnSpace;
}
void Monopoly::Space::setPlayersOnSpace(const std::vector<Monopoly::Player> &playersOnSpace) {
  Space::playersOnSpace = playersOnSpace;
}
Monopoly::Gamestate *Monopoly::Space::getGameStatePtr() const {
  return gameStatePtr;
}
void Monopoly::Space::setGameStatePtr(Monopoly::Gamestate *gameStatePtr) {
  Space::gameStatePtr = gameStatePtr;
}



