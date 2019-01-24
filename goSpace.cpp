//
// Created by kevin on 2/27/2018.
//

#include <iostream>
#include "goSpace.h"
int Monopoly::goSpace::getGoCash() const {
  return goCash;
}
void Monopoly::goSpace::setGoCash(int goCash) {
  goSpace::goCash = goCash;
}
Monopoly::goSpace::goSpace(int goCashInput, std::string nameIn) {
  goCash = goCashInput;
  name = nameIn;
}
void Monopoly::goSpace::display() {
  std::cout << Space::getSpaceID() << " | " << name;
  std::cout << " | None | None ";
  if (getPlayersOnSpace().size() > 0){
    for (unsigned int i = 0; i < getPlayersOnSpace().size(); ++i){
      std::cout << "[" << getPlayersOnSpace()[i].name << " : $" << getPlayersOnSpace()[i].getCash() << "]";
      if (i != getPlayersOnSpace().size() - 1)
        std::cout << ",";
    }
  }


}
