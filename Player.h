//
// Created by kevin on 2/5/2018.
//
#include <string>
#include <vector>
#ifndef HOARDING_PLAYER_H
#define HOARDING_PLAYER_H
namespace Monopoly {
  class Player {
   public:
    std::string name;
    int playerId;
    Player(int startingCash, std::string playerName, int playerId);

   private:
    int cash;
    int position;
    std::vector<int> spacesOwned;
   public:
    std::vector<int> getSpacesOwned();
    void setSpacesOwned(const std::vector<int> &spacesOwned);
   private:
    bool inGame = NULL;
    int upgradeCosts;
   public:
    int getUpgradeCosts() const;
    void setUpgradeCosts(int upgradeCosts);
   public:
    int getCash() const;
    void setCash(int cash);
    int getPosition();
    void setPosition(int position);
    bool isInGame() const;
    void setInGame(bool inGame);

  };
}

#endif //HOARDING_PLAYER_H
