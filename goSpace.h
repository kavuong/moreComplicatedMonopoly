//
// Created by kevin on 2/27/2018.
//

#ifndef HOARDING_GOSPACE_H
#define HOARDING_GOSPACE_H
#include "Space.h"
namespace Monopoly {
class goSpace : public Space{
 public:
  explicit goSpace(int goCashInput, std::string nameIn);
 private:
  int goCash;
 public:
  int getGoCash() const;
  void setGoCash(int goCash);
  void display() override;

};
}
#endif //HOARDING_GOSPACE_H
