cmake_minimum_required(VERSION 3.8)
project(hoarding__)

set(CMAKE_CXX_STANDARD 14)

set(GPP_ENABLE_WARNINGS "-O0 -Wall -Werror -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GPP_ENABLE_WARNINGS}")

set(SOURCE_FILES main.cpp Board.cpp Board.h Gamestate.cpp Gamestate.h Player.cpp Player.h Space.cpp Space.h Property.cpp Property.h DiceRoller.cpp DiceRoller.h Rules.cpp Rules.h monopolyGame.cpp monopolyGame.h propUpgrade.cpp propUpgrade.h auctioning.cpp auctioning.h goSpace.cpp goSpace.h)
add_executable(hoarding__ ${SOURCE_FILES})