#include "World.h"
#ifndef HERO_H
#define HERO_H

using namespace std;

class Hero {

public:

void playGame(string input, string output);
void setCurrIndex(int level, int row, int column);
bool interactWithSpace(char c, int count);
void addCoin();
int findCoin(int coin, int health);
int findGoomba(int health, int power, int attack);
int findKoopa(int health, int power, int attack);
int findBoss(int health, int power, int attack);
int changePowerG(int power, int attack);
int changePowerK(int power, int attack);
int changePowerB(int power, int attack);
void printWorldToOutput(string file, char*** arr, int l, int d);


// void advanceHeroLevel();

private:

int m_power;
int m_reactRow;
int m_reactColumn;
int m_reactLevel;
int m_health;
int m_enemiesDefeated;
int m_coinsCollected;
int m_count;

};

#endif
