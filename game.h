#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include "game.h"

class Game {
  public:
    Game(int players);
    //Logic Setters

    //Logic variables
    bool throneOfBone();
    bool feasting();
    bool scourchedEarth();
    bool captainsOfIndustry();
    bool endGameConditions();
    //Game Setters
    void advanceTurn();
    void inputChoices();
    void determineChoices();
    void resolveConflict(int juggernaut, int human[10]);
    void humanReward(int location, int index);
    void juggernautReward(int location, int humanIndex);
    void killHuman(int index);
    //Game Getters and print statements
    int getHumans();
    int getJuggernautGoldenEggs();
    int getJuggernautTBones();
    int getJuggernautCrops();
    int getHumanGoldenEggs(int index);
    int getHumanTBones(int index);
    int getHumanCrops(int index);
    int getJuggernaut();
    int getHuman(int index);
    friend std::ostream& operator<<(std::ostream& out, Game g);
  private:
    //Game Variables
    std::string name;
    int ID;
    int humans;
    int turn;
    int skulls, skullsGoal;
    int juggernautGoldenEggs, juggernautTBones, juggernautCrops;
    int humanSettlements, settlementsGoal;
    int humanGoldenEggs [10];
    int humanTBones [10];
    int humanCrops [10];
    bool humanAlive [10];
    int choices [11];
};
#endif //GAME_H
