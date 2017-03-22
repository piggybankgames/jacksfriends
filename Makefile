all: main

main: oneHundredThousandGames.o game.o
	g++ -fpermissive oneHundredThousandGames.o game.o -o oneHundredThousandGames

oneGame: oneGame.o game.o
	g++ -fpermissive oneGame.o game.o -o oneGame

oneInputGame: oneInputGame.o game.o
	g++ -fpermissive oneInputGame.o game.o -o oneInputGame

oneHundredThousandGames.o: oneHundredThousandGames.cpp

oneInputGame.o: oneInputGame.cpp
	g++ -c oneInputGame.cpp

oneGame.o: oneGame.cpp
	g++ -c oneGame.cpp

game.o: game.cpp
	g++ -c game.cpp

clean:
	rm *o oneHundredThousandGames oneGame oneInputGame
