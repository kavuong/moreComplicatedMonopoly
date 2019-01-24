//
// Created by kevin on 2/5/2018.
//

#ifndef HOARDING_SPACE_H
#define HOARDING_SPACE_H
#include "Player.h"
#include "Gamestate.h"
namespace Monopoly {
enum class spaceType{goSpace, Property, freeParking, payBank, jail, goToJail};
  class Space {
   public:
    Space();
    //go space
    //Space(int goCash, std::string name);
    //prop space
    //Space(Property aProperty, std::string name);

    //bool isType() const;
    //void setType(bool type);
    //const Property &getProperty() const;
    //void setProperty(const Property &property);
    spaceType type;
    std::string name;


   private:
    // GO -> false, property -> true
    //bool type = NULL;
    //Property property;
//    int owner;
    int spaceID;
    std::vector<Monopoly::Player> playersOnSpace;
    Gamestate * gameStatePtr;
   public:
    Gamestate *getGameStatePtr() const;
    void setGameStatePtr(Gamestate *gameStatePtr);
   public:

   public:


   public:
    const std::vector<Player> &getPlayersOnSpace() const;
    void setPlayersOnSpace(const std::vector<Player> &playersOnSpace);
/*
    int numHouses;
    int numHotels;
    */


   public:
    virtual void activate(Monopoly::Player& activatingPlayer) = 0;
    virtual void display();

/*
    int getNumHouses() const;
    void setNumHouses(int numHouses);
    int getNumHotels() const;
    void setNumHotels(int numHotels);
    */
   public:
    int getSpaceID() const;
    void setSpaceID(int spaceID);
   public:
//    int getOwner() const;
//    void setOwner(int owner);
   public:


  };
}

#endif //HOARDING_SPACE_H
