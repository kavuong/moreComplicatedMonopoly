//
// Created by kevin on 2/5/2018.
//

#ifndef HOARDING_BOARD_H
#define HOARDING_BOARD_H
#include <vector>
#include <memory>
#include "Space.h"
namespace Monopoly {
  class Board {
   public:
    Board();
    explicit Board(char *boardFile, Monopoly::Rules &gameRules);

   private:
    int numBoardSpaces;
   public:
    const int getNumBoardSpaces() const;
    std::unique_ptr<Space> getSpacePtr(int position);
    Space & getSpace(int position);
   private:
    std::vector<std::unique_ptr<Space>> boardArr;

    void initNonSpaceData(std::ifstream &inFS, Monopoly::Rules &gameRules);
    void initSpaceData(std::ifstream &inFS, Monopoly::Rules &gameRules);

  };
}

#endif //HOARDING_BOARD_H
