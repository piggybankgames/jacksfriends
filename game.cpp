#include <iostream>
#include <string>
#include <stdlib.h>
#include "game.h"

Game::Game(int players) {
  name = "A random game of Juggernaut";
  ID = 101;
  humans = players-1;
  turn = 0;
  skulls = 0;
  if (players <= 4) {
    if (players == 2) {
      settlementsGoal = (players)*2 - 1;
      skullsGoal = players*2 - 1;
    } else {
      settlementsGoal = (players)*2;
      skullsGoal = players*2;
    }
    juggernautGoldenEggs = players;
    juggernautTBones = players;
  } else {
    juggernautGoldenEggs = players + 1;
    juggernautTBones = players + 1;
    settlementsGoal = (players)*2 + 1;
    skullsGoal = players*2 + 1;
  }
  juggernautCrops = (players - 1)*2 + 1;
  humanSettlements = 0;
  for(int i=0;i<(players - 1);i++) {
    humanGoldenEggs[i] = 0;
  }
  for(int i=0;i<(players - 1);i++) {
    humanTBones[i] = 0;
  }
  for(int i=0;i<(players - 1);i++) {
    humanCrops[i] = 0;
  }
  for(int i=0;i<(players - 1);i++) {
    humanAlive[i] = true;
  }
  for(int i=0;i<players;i++) {
    choices[i] = 8;
  }
}
bool Game::throneOfBone() {
  if (skulls >= skullsGoal) {
    return true;
  }
  return false;
}
bool Game::feasting() {
  if ( turn >= 10 ) {
    return true;
  }
  return false;
}
bool Game::scourchedEarth() {
  int clauses = 0;
  if (juggernautGoldenEggs == 0)
    clauses += 1;
  if (juggernautTBones == 0)
    clauses += 1;
  if (juggernautCrops == 0)
    clauses += 1;
  if (clauses >= 2) {
    return true;
  }
  return false;
}
bool Game::captainsOfIndustry() {
  if (humanSettlements >= settlementsGoal) {
    return true;
  }
  return false;
}

bool Game::endGameConditions() {
  if ( throneOfBone() || feasting() || scourchedEarth() || captainsOfIndustry() ) {
    return true;
  }
  return false;
}
void Game::advanceTurn() {
  turn = turn + 1;
}
void Game::inputChoices() {
  std::cout << "inputChoices called.\n";
  std::cout << "Pick for the Juggernaut.\n";
  std::cin >> choices[0];
  for(int i=1; i<=humans; i++) {
    std::cout << "Pick for human " << i << "\n";
    std::cin >> choices[i];
  }
  for (int i=0; i<humans; i++) {
    if (!humanAlive[i]) {
      choices[i+1] = 11;
      humanAlive[i] = true;
    }
  }
  std::cout << "The juggernaut choses " << choices[0] << std::endl;
  for (int i=1; i<=humans; i++) {
    std::cout << "Human " << i << " chose " << choices[i] << std::endl;
  }
}
void Game::determineChoices() {
  for (int i=0; i<(humans + 1); i++) {
    choices[i] = rand() % 4;
  }
  for (int i=0; i<humans; i++) {
    if (!humanAlive[i]) {
      choices[i+1] = 11;
      humanAlive[i] = true;
    }
  }
}
void Game::resolveConflict(int juggernaut, int human [10]) {
  for (int i=0; i < humans; i++) {
    if (juggernaut == human[i]) {
      juggernautReward(juggernaut, i);
      killHuman(i+1);
    } else if (humanAlive[i]) {
      humanReward(human[i], i);
    }
  }
}
void Game::humanReward(int location, int index) {
  int number = index + 1;
  if (location == 0) {
    int gain = juggernautGoldenEggs;
    juggernautGoldenEggs = juggernautGoldenEggs - 1;
    if (juggernautGoldenEggs < 0)
      juggernautGoldenEggs = 0;
    humanGoldenEggs[index] = humanGoldenEggs[index] + (gain - juggernautGoldenEggs);
  }
  if (location == 1) {
    int gain = juggernautTBones;
    juggernautTBones = juggernautTBones - 1;
    if (juggernautTBones < 0)
      juggernautTBones = 0;
    humanTBones[index] = humanTBones[index] + (gain - juggernautTBones);
  }
  if (location == 2) {
    int gain = juggernautCrops;
    juggernautCrops = juggernautCrops - 1;
    if (juggernautCrops < 0)
      juggernautCrops = 0;
    humanCrops[index] = humanCrops[index] + (gain - juggernautCrops);
  }
  if (location == 3) {
    humanSettlements += 1;
    if (humanGoldenEggs[index] > 0) {
      humanSettlements = humanSettlements + humanGoldenEggs[index];
      humanGoldenEggs[index] = 0;
    }
  }
}
void Game::juggernautReward(int location, int humanIndex) {
  if (location == 3) {
    if(humanGoldenEggs[humanIndex] > 0) {
      humanGoldenEggs[humanIndex] -= 1;
      juggernautGoldenEggs += 1;
    } else if (humanTBones[humanIndex] > 0) {
      humanTBones[humanIndex] -= 1;
      juggernautTBones += 1;
    } else if (humanCrops[humanIndex] > 0) {
      humanCrops[humanIndex] -= 1;
      juggernautCrops += 1;
    }
  }
}
void Game::killHuman(int number) {
  skulls += 1;
  int index = number-1;
  if (humanTBones[index] > 0) {
    humanTBones[index] = humanTBones[index] - 1;
  } else if (humanCrops[index] > 1) {
    humanCrops[index] = humanCrops[index] - 2;
  } else {
    humanAlive[index] = false;
  }
}
int Game::getHumans() {
  return humans;
}
int Game::getJuggernautGoldenEggs() {
  return juggernautGoldenEggs;
}
int Game::getJuggernautTBones() {
  return juggernautTBones;
}
int Game::getJuggernautCrops() {
  return juggernautCrops;
}
int Game::getHumanGoldenEggs(int index) {
  return humanGoldenEggs[index];
}
int Game::getHumanTBones(int index) {
  return humanTBones[index];
}
int Game::getHumanCrops(int index) {
  return humanCrops[index];
}
int Game::getJuggernaut() {
  return choices[0];
}
int Game::getHuman(int number) {
  return choices[number];
}
std::ostream& operator<<(std::ostream& out, Game g) {
  out << "The game ended in " << g.turn << " turns.\n";
  out << "Juggernaut's Golden Eggs: " << g.juggernautGoldenEggs << std::endl;
  out << "The Juggernaut collected " << g.skulls << " skulls.\n";
  out << "T Bones: " << g.juggernautTBones << " Crops: " << g.juggernautCrops << std::endl;
  for (int i=0; i < g.humans; i++) {
    int number = i + 1;
    out << "Human " << number << " had T Bones: " << g.humanTBones[i] << " Golden Eggs: " << g.humanGoldenEggs[i] << " Crops: " << g.humanCrops[i] << std::endl;
  }
  out << "There were " << g.humanSettlements << " human settlements." << std::endl;
}
