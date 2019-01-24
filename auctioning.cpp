//
// Created by kevin on 2/21/2018.
//

#include <iostream>
#include <map>
#include "auctioning.h"
#include "Property.h"
void handleAuction(Monopoly::Gamestate &gameState, Monopoly::Property &propLandedOn) {
  int currBid = 1;
  int playerWithBid;
  int & playerBidRef = playerWithBid;

  bool firstPlayer = true;
  std::map<int, bool> playersInAuction;
  int playerWinningID;
  for (int i = 1; i <= gameState.numOrigPlayers; ++i){
    if (gameState.playerWithID(i).isInGame()){
      playersInAuction.insert(std::pair<int, bool>(i, true));
    }
    // finds first player in game
    if (firstPlayer) {
      playerWithBid = i;
      firstPlayer = false;
    }
  }
  std::cout << "Starting the auction for " << propLandedOn.name << std::endl;
  while (true){
    int playerBid;
    int numPlayersInAuction = 0;
    bool nextPlayerInAuction = false;

    Monopoly::Player biddingPlayer = gameState.playerWithID(playerWithBid);
    if (currBid == 1) {
      std::cout << "No one has bid on " << propLandedOn.name << " [$" << propLandedOn.getPropertyCost()
                << "] yet" << std::endl;
      std::cout << biddingPlayer.name << ", enter a bid of at least $" << currBid
                << " to bid on the property or a value less than that to leave the auction" << std::endl;
    }

    else {
      std::cout << "The current bid for " << propLandedOn.name << " [$" << propLandedOn.getPropertyCost() << "]"
                << " is $" << currBid << " by " << gameState.playerWithID((playerWinningID)).name << std::endl;
      std::cout << biddingPlayer.name << ", enter a bid of at least $" << currBid + 1
                << " to bid on the property or a value less than that to leave the auction" << std::endl;
    }
      std::cout << "Your bid:";
    std::cin >> playerBid;
    if (playerBid >= currBid + 1){
      playerWinningID = playerWithBid;
      currBid = playerBid;
    }
    else{
      playersInAuction[playerWithBid] = false;
    }
    for (auto it = playersInAuction.begin(); it != playersInAuction.end(); ++it){
      if (it->second)
        numPlayersInAuction++;
    }

    if (currBid != 1) {
      if (numPlayersInAuction <= 1) {
        std::cout << gameState.playerWithID((playerWinningID)).name << " won " << propLandedOn.name << " for $"
                  << currBid << std::endl;
        auto winningPlayer = gameState.playerWithID(playerWinningID);
        propLandedOn.setOwner(&winningPlayer);
        winningPlayer.setCash(winningPlayer.getCash() - currBid);
        std::vector<int> spacesOwned = gameState.playerWithID(playerWinningID).getSpacesOwned();
        spacesOwned.push_back(propLandedOn.getSpaceID());
        gameState.playerWithID(playerWinningID).setSpacesOwned(spacesOwned);
        break;
      }
    }
    else{
      // check if curr auctioner is last player, if so then
      if (playerWithBid == (playersInAuction.rbegin())->first) {
        std::cout << "No one decided to purchase " << propLandedOn.name << std::endl;
        break;
      }

    }
    while (!nextPlayerInAuction) {
      playerWithBid = nextPlayer(gameState, playerBidRef);
      if (playersInAuction[playerWithBid])
        nextPlayerInAuction = true;
    }
  }
}
