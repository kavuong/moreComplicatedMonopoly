//
// Created by kevin on 2/5/2018.
//

#ifndef HOARDING_DICEROLLER_H
#define HOARDING_DICEROLLER_H
#include <fstream>
namespace Monopoly {
  class DiceRoller {
   public:
    int getDiceRoll(bool &doubleOrNot);
    explicit DiceRoller(char * randFile);
   private:
    std::ifstream randStream;
   public:
    const std::ifstream &getRandStream() const;
   private:
    int computeRoll();

  };
}

#endif //HOARDING_DICEROLLER_H
