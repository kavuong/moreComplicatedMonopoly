hoarding.out: auctioning.o Board.o DiceRoller.o Gamestate.o goSpace.o main.o monopolyGame.o Player.o Property.o propUpgrade.o Rules.o Space.o
	g++ -g -Wall -Werror -std=c++14 -o hoarding.out auctioning.o Board.o DiceRoller.o Gamestate.o goSpace.o main.o monopolyGame.o Player.o propUpgrade.o Property.o Rules.o Space.o

auctioning.o: auctioning.cpp auctioning.h Property.h
	g++ -g -Wall -Werror -c -std=c++14 auctioning.cpp

Board.o: Board.cpp Board.h Gamestate.h goSpace.h Property.h
	g++ -g -Wall -Werror -c -std=c++14 Board.cpp

DiceRoller.o: DiceRoller.cpp DiceRoller.h
	g++ -g -Wall -Werror -c -std=c++14 DiceRoller.cpp

Gamestate.o: Gamestate.cpp Gamestate.h
	g++ -g -Wall -Werror -c -std=c++14 Gamestate.cpp

goSpace.o: goSpace.cpp goSpace.h
	g++ -g -Wall -Werror -c -std=c++14 goSpace.cpp

main.o: main.cpp Gamestate.h monopolyGame.h
	g++ -g -Wall -Werror -c -std=c++14 main.cpp

monopolyGame.o: monopolyGame.cpp monopolyGame.h propUpgrade.h Property.h
	g++ -g -Wall -Werror -c -std=c++14 monopolyGame.cpp

Player.o: Player.cpp Player.h
	g++ -g -Wall -Werror -c -std=c++14 Player.cpp

Property.o: Property.cpp auctioning.h Property.h
	g++ -g -Wall -Werror -c -std=c++14 Property.cpp

propUpgrade.o: propUpgrade.cpp Gamestate.h propUpgrade.h
	g++ -g -Wall -Werror -c -std=c++14 propUpgrade.cpp

Rules.o: Rules.cpp Gamestate.h Rules.h
	g++ -g -Wall -Werror -c -std=c++14 Rules.cpp

Space.o: Space.cpp Board.h property.h Space.h
	g++ -g -Wall -Werror -c -std=c++14 Space.cpp

clean:
	rm -f *.o *.out
