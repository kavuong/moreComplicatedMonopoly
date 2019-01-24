//
// Created by kevin on 2/5/2018.
//
#include <iostream>
#include <fstream>
#include "Board.h"
#include "Gamestate.h"
#include "goSpace.h"
#include "Property.h"

Monopoly::Board::Board(char *boardFile, Monopoly::Rules &gameRules) {
  if (boardFile != NULL) {
    std::ifstream inFS;

    std::string line = "";
    std::string dummyStr = "";

    inFS.open(boardFile);
    initNonSpaceData(inFS, gameRules);
    initSpaceData(inFS, gameRules);

    inFS.close();
  }
}
// accounts for first 5 lines of board CSV, including GO space
void Monopoly::Board::initNonSpaceData(std::ifstream &inFS, Monopoly::Rules &gameRules) {
  int numBoardSpaces;
  int goCash;
  std::string goName;
  char c;
  inFS.ignore(17, '\n');
  inFS >> numBoardSpaces;

  inFS.ignore(1000, '\n');
  inFS.ignore(1000, '\n');
  inFS.ignore(1000, '\n');
  inFS.ignore(1000, '\n');
  inFS.ignore(3, '\n');
  inFS >> goCash;
  inFS.ignore(1, '\n');
  while (!inFS.eof()){
    inFS.get(c);
    if (c == ',')
      break;
    else
      goName += c;

  }
  inFS.ignore(1000, '\n');

  goSpace goSpaceToAdd = goSpace(goCash, goName);
  goSpaceToAdd.type = Monopoly::spaceType::goSpace;
  goSpaceToAdd.setSpaceID(0);

  auto spaceToAddPtr = std::make_unique(goSpaceToAdd);
  boardArr.push_back(spaceToAddPtr);
}
void Monopoly::Board::initSpaceData(std::ifstream &inFS, Monopoly::Rules &gameRules) {
  // go space
  int boardSpaces = 1;
  int setId = 0;
  int intraId = 0;

  int propertyCost = 0;
  int houseCost = 0;
  int hotelCost = 0;
  int rent = 0;
  int houseRent = 0;
  int hotelRent = 0;
  int owner = -1;
  char c;

  while (!inFS.eof()){
    std::string name;
    inFS.ignore(9, '\n');
    Property aProperty;

    inFS >> setId;
    inFS.ignore(1, ',');
    inFS >> intraId;
    inFS.ignore(1, ',');
    while (true) {
      inFS.get(c);
      if (c == ',')
        break;
      else
        name += c;
    }
    inFS >> propertyCost;
    inFS.ignore(1, ',');
    inFS >> houseCost;
    inFS.ignore(1, ',');
    inFS >> hotelCost;
    inFS.ignore(1, ',');
    inFS >> rent;
    inFS.ignore(1, ',');
    inFS >> houseRent;
    inFS.ignore(1, ',');
    inFS >> hotelRent;
    inFS.ignore(1000, '\n');

    aProperty.setSetId(setId);
    aProperty.setIntraId(intraId);
    aProperty.name = name;
    aProperty.setPropertyCost(propertyCost);
    aProperty.setHouseCost(houseCost);
    aProperty.setHotelCost(hotelCost);
    aProperty.setRent(rent);
    aProperty.setHouseRent(houseRent);
    aProperty.setHotelRent(hotelRent);

    aProperty.setOwner(nullptr);
    aProperty.setSpaceID(boardSpaces);
    aProperty.setNumHouses(0);
    aProperty.setNumHotels(0);

    aProperty.type = Monopoly::spaceType::Property;
    auto propPtr = std::make_unique(aProperty);

    boardArr.push_back(std::move(propPtr));
    boardSpaces++;
  }
  this->numBoardSpaces = boardSpaces;
}
const int Monopoly::Board::getNumBoardSpaces() const {
  return numBoardSpaces;
}
Monopoly::Space& Monopoly::Board::getSpace(int position) {
  return *(boardArr[position]);
}
Monopoly::Board::Board() {

}
std::unique_ptr<Space> Monopoly::Board::getSpacePtr(int position) {
  return boardArr[position];
}

