#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "game.h"

int digitToInt(char c)
{
	return (static_cast<int>(c) - static_cast<int>('0') );
}
int main ( int argc, char *argv[]  ) {
	std::cout << "This is a self generated 100,000 games of Juggernaut.\n";
	std::cout <<	"The juggernaut as well as the humans will choose locations by RNG.\n";
	std::cout << "The game now accepts any number of players $./testapp 3\n";
	std::cout << "Would run the game with 3 players 1 juggernaut and 2 humans.\n";
	std::cout << "This will output winrate\n";
	srand(unsigned(time(NULL)));
	int throne = 0 , feast = 0 , scorched = 0 , captain = 0;
	double  juggernautW = 0, humanW = 0, n = 0;
	for(int i=0; i<100000; i++) {
		Game AGame(digitToInt(*argv[1]));
		while ( !AGame.endGameConditions() ) {
			AGame.advanceTurn();
			AGame.determineChoices();
			int jug = AGame.getJuggernaut();
			int hum[AGame.getHumans()];
			for (int i=0; i < AGame.getHumans(); i++) {
				hum[i] = AGame.getHuman(i+1);
			}
			AGame.resolveConflict(jug, hum);
		}
		if ( AGame.throneOfBone() ) {
			throne += 1;
			juggernautW += 1;
		} else if ( AGame.scourchedEarth() ) {
			scorched += 1;
			humanW += 1;
		} else if ( AGame.captainsOfIndustry() ) {
			captain += 1;
			humanW += 1;
		} else if ( AGame.feasting() ) {
			feast += 1;
			juggernautW += 1;
	  }
	}
	double humanWinRate = humanW / (humanW + juggernautW);
	std::cout << "Throne Wins: " << throne << " Feast Wins: " << feast << std::endl;
	std::cout << "Scorched Wins: " << scorched << " Captain Wins: " << captain << std::endl;
	std::cout << "The humans have a win rate of " << humanWinRate << " with a total of " << humanW << " wins.\n";
}
