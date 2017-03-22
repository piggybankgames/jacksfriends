#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "game.h"

int digitToInt(char c)
{
	return (static_cast<int>(c) - static_cast<int>('0') );
}
int main ( int argc, char *argv[] )
{
	std::cout << "(This is a manually entered game of Juggernaut. This is to help test the rules are being correctly adhered to in code.\n";
	std::cout << "The game now accepts any number of players $./testapp 3\n";
	std::cout << "Would run the game with 3 players 1 juggernaut and 2 humans.\n";
	std::cout << "The location IDs are 0=Hen House, 1=Kitchen, 2=Garden, 3=Village\n";
	srand(unsigned(time(NULL)));
	Game AGame(digitToInt(*argv[1]));
	while ( !AGame.endGameConditions() ) {
		AGame.advanceTurn();
		AGame.inputChoices();
		int jug = AGame.getJuggernaut();
		int hum[AGame.getHumans()];
		for (int i=0; i < AGame.getHumans(); i++) {
			hum[i] = AGame.getHuman(i+1);
		}
		AGame.resolveConflict(jug, hum);
	}
	std::cout << AGame << std::endl;
	std::cout << AGame.endGameConditions() << std::endl;
	if ( AGame.throneOfBone() )
		std::cout << "The juggernaut is sitting on a throne of bones." << std::endl;
	if ( AGame.scourchedEarth() )
		std::cout << "The earth is scourched." << std::endl;
	if ( AGame.captainsOfIndustry() )
		std::cout << "You are a captain of industry." << std::endl;
	if ( AGame.feasting() )
		std::cout << "The juggernaut is feasting." << std::endl;
}
