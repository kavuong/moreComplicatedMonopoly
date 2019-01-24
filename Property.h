//
// Created by kevin on 2/5/2018.
//

#ifndef HOARDING_PROPERTY_H
#define HOARDING_PROPERTY_H
#include <string>
#include "Space.h"
namespace Monopoly {
  class Property : public Space {
   public:
    Property();
   private:
    int setId;
    int intraId;
    int propertyCost;
    int houseCost;
   public:
    int getSetId() const;
    void setSetId(int setId);
    int getIntraId() const;
    void setIntraId(int intraId);
    /*
    const std::string &getName() const;
    void setName(const std::string &name);
     */
    int getPropertyCost() const;
    void setPropertyCost(int propertyCost);
    int getHouseCost() const;
    void setHouseCost(int houseCost);
    int getHotelCost() const;
    void setHotelCost(int hotelCost);
    int getRent() const;
    void setRent(int rent);
    int getHouseRent() const;
    void setHouseRent(int houseRent);
    int getHotelRent() const;
    void setHotelRent(int hotelRent);


   private:
    int hotelCost;
    int rent;
    int houseRent;
    int hotelRent;
    Player * owner;
   public:
    Player *getOwner() const;
    void setOwner(Player *owner);
   public:

   private:

    // make inheritance work with JUST property and go spaces, start with making numHouses and numHotels native to Property class NOT Space class
    int numHouses;
   public:
    int getNumHouses() const;
    void setNumHouses(int numHouses);
    int getNumHotels() const;
    void setNumHotels(int numHotels);

    void activate(Monopoly::Player & activatingPlayer);
    void display() override ;
   private:
    int numHotels;



  };
}

#endif //HOARDING_PROPERTY_H
