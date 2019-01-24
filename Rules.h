//
// Created by kevin on 2/5/2018.
//
#include <memory>
#ifndef HOARDING_RULES_H
#define HOARDING_RULES_H
namespace Monopoly {
  class Rules {
   public:
    // empty constructor
    Rules();
    Rules(char * ruleFile);
   private:
    bool makeLowerCase(std::string inputStr);
    int startingCash;
    int turnLimit;
    int playersLeftToEnd;
    int propertyMultiplier;
    int housesBeforeHotels;
    // true -> yes false -> no
    bool buildHousesEvenly = NULL;
   public:
    bool isBuildHousesEvenly() const;
   private:
    bool moneyInFreeParking = NULL;
    bool auctionProp = NULL;
    int goLandingMultiplier;
    int maxDoubleRerolls;
   public:
    int getMaxDoubleRerolls() const;
    void setMaxDoubleRerolls(int maxDoubleRerolls);
   public:
    int getStartingCash() const;
    void setStartingCash(int startingCash);
    int getTurnLimit() const;
    void setTurnLimit(int turnLimit);
    int getPlayersLeftToEnd() const;
    void setPlayersLeftToEnd(int playersLeftToEnd);
    int getPropertyMultiplier() const;
    void setPropertyMultiplier(int propertyMultiplier);
    int getHousesBeforeHotels() const;
    void setHousesBeforeHotels(int housesBeforeHotels);
    void setBuildHousesEvenly(bool buildHousesEvenly);
    bool isMoneyInFreeParking() const;
    void setMoneyInFreeParking(bool moneyInFreeParking);
    bool isAuctionProp() const;
    void setAuctionProp(bool auctionProp);
    int getGoLandingMultiplier() const;
    void setGoLandingMultiplier(int goLandingMultiplier);
  };
}

#endif //HOARDING_RULES_H
