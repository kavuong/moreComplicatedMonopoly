//
// Created by kevin on 2/5/2018.
//

#include "DiceRoller.h"
int Monopoly::DiceRoller::getDiceRoll(bool &doubleOrNot) {
  int rand1 = 0;
  int rand2 = 0;

  randStream >> rand1;
  randStream >> rand2;
// POTENTIAL PROBLEM BERE
  if (rand1 == rand2)
    doubleOrNot = true;
  else
    doubleOrNot = false;

  return rand1 % 6 + rand2 % 6 + 2;
}
int Monopoly::DiceRoller::computeRoll() {
  return 0;
}
const std::ifstream &Monopoly::DiceRoller::getRandStream() const {
  return randStream;
}
Monopoly::DiceRoller::DiceRoller(char *randFile) {
  std::ifstream inFS;
  inFS.open(randFile);
  randStream = std::move(inFS);

}




