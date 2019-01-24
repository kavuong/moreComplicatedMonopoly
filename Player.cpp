//
// Created by kevin on 2/5/2018.
//

#include "Player.h"
int Monopoly::Player::getCash() const {
  return cash;
}
void Monopoly::Player::setCash(int cash) {
  Player::cash = cash;
}
int Monopoly::Player::getPosition() {
  return position;
}
void Monopoly::Player::setPosition(int position) {
  Player::position = position;
}
bool Monopoly::Player::isInGame() const {
  return inGame;
}
void Monopoly::Player::setInGame(bool inGame) {
  Player::inGame = inGame;
}
Monopoly::Player::Player(int startingCash, std::string playerName, int playerId) {
  setCash(startingCash);
  this->name = playerName;
  this->playerId = playerId;
  setInGame(true);

}
std::vector<int> Monopoly::Player::getSpacesOwned () {
  return spacesOwned;
}
void Monopoly::Player::setSpacesOwned(const std::vector<int> &spacesOwned) {
  Player::spacesOwned = spacesOwned;
}
int Monopoly::Player::getUpgradeCosts() const {
  return upgradeCosts;
}
void Monopoly::Player::setUpgradeCosts(int upgradeCosts) {
  Player::upgradeCosts = upgradeCosts;
}
