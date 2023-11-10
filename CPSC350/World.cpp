#include "World.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

World::World() {
  m_levels = 1;
  m_dimension = 2;
  m_lives = 10;
  m_pCoin = 0.2;
  m_pNothing = 0.2;
  m_pGoom = 0.2;
  m_pKoop = 0.2;
  m_pMush = 0.2;
  gameArray = createWorld(m_levels, m_dimension);
}

World::~World() {

}

char*** World::createWorld(int levels, int dimension) { // create's world of (level) levels with dimensions of dimension x dimension
  if (levels < 1) {
    int exitLevel = 0;
    cout << "ERROR: Levels <= 0" << endl;
    exit(exitLevel);
  }

  m_levels = levels;
  m_dimension = dimension;
char*** levelsRowsColumns = new char**[levels]; // levels
for (int i = 0; i < levels; ++i) {
  levelsRowsColumns[i] = new char*[dimension]; // rows
  for (int j = 0; j < dimension; ++j) {
    levelsRowsColumns[i][j] = new char[dimension]; // columns
    }
  }
  gameArray = levelsRowsColumns;
  return gameArray;
}

void World::fillWorld(int lives, int pCoin, int pNothing, int pGoom, int pKoop, int pMush) { // fills world with items based on preset weighting
  srand(time(NULL));
  if((pCoin + pNothing + pGoom + pKoop + pMush) != 100) { // checks to makes sure all percentages from input are == to 100
    int exitInt = pCoin + pNothing + pGoom + pKoop + pMush;
    cout << "ERROR: Percentages don't equal 100, please enter new inputs." << endl;
    exit(exitInt);
  }

  int spotsToFill = m_dimension * m_dimension * m_levels;

  m_lives = lives;
  m_pCoin = pCoin/100.0;
  m_pNothing = pNothing/100.0;
  m_pGoom = pGoom/100.0;
  m_pKoop = pKoop/100.0;
  m_pMush = pMush/100.0;

  int numCoin = m_pCoin * spotsToFill;
  int numNothing = m_pNothing * spotsToFill;
  int numGoom = m_pGoom * spotsToFill;
  int numKoop = m_pKoop * spotsToFill;
  int numMush = m_pMush * spotsToFill;

  int spotsRemaining = spotsToFill - (numCoin + numNothing + numGoom + numKoop + numMush); // takes remaining spaces and seperates them


  // If (numNothing / 4) > 1, that means that I can take the excess from the number of nothing spaces, and fill them with other interactions

  int addOthers = (spotsRemaining / 4);
  if (addOthers >= 1) {
  for (int i = 0; i < addOthers; ++i) {
    numCoin++;
    numGoom++;
    numKoop++;
    numMush++;
    spotsRemaining -= 4;
  }
}
  numNothing += spotsRemaining;

  for (int i = 0; i < m_levels; ++i) {
    for (int j = 0; j < m_dimension; ++j) {
      for (int k = 0; k < m_dimension; ++k) {

          int temp = pickRandomItem();
          if (temp == 1) {
            if (numCoin > 0) {
              numCoin--;
              gameArray[i][j][k] = 'C';
            } else {
              --k;
            }
          } else if (temp == 2) {
            if (numNothing > 0) {
              numNothing--;
              gameArray[i][j][k] = 'X';
            } else {
            --k;
            }
          } else if (temp == 3) {
            if (numGoom > 0) {
              numGoom--;
              gameArray[i][j][k] = 'G';
            } else {
            --k;
            }
          } else if (temp == 4) {
            if (numKoop > 0) {
              numKoop--;
              gameArray[i][j][k] = 'K';
            } else {
            --k;
            }
          } else if (temp == 5) {
            if (numMush > 0) {
              numMush--;
              gameArray[i][j][k] = 'M';
            } else {
            --k;
            }
          }

    }
  }
}
}

int World::pickRandomItem() { // pick random number, which will determine item at space (1) Coin (2) Nothing (3) Goomba (4) Koops (5) Mushroom

  int rand();
  int randomNum;
  randomNum = (rand() % 5) + 1;
  return randomNum;
}

void World::placeHeroWarpBoss() { // place the hero, warp, and boss randomly on the grid

  for (int i = 0; i < m_levels; ++i) { // placing warp portal everywhere but last level
    int tempRowWarp = (rand() % m_dimension);
    int tempColumnWarp = (rand() % m_dimension);
    if (i == m_levels - 1) {
    } else {
      gameArray[i][tempRowWarp][tempColumnWarp] = 'W';
    }
  }

  bool heroExists = false; // boolean to ensure that Mario isn't placed on a Warp portal on first level
  while (!heroExists) { // ensures that Mario isn't placed on a Warp portal on first level
    int tempRowHero = (rand() % m_dimension);
    int tempColumnHero = (rand() % m_dimension);

    if (m_dimension == 1) {
      gameArray[0][tempRowHero][tempColumnHero] = 'H';
      heroExists = true;
    }

    if (gameArray[0][tempRowHero][tempColumnHero] != 'W') {
      gameArray[0][tempRowHero][tempColumnHero] = 'H';
      m_heroRow = tempRowHero;
      m_heroColumn = tempColumnHero;
      m_heroLevel = 0;
      heroExists = true;
    } else {
      heroExists = false;
    }
  }

  for (int i = 0; i < m_levels; ++i) { // places boss, but ensures that it's not on a space with the Hero or the Warp Portal
    int tempRowBoss = (rand() % m_dimension);
    int tempColumnBoss = (rand() % m_dimension);
    if (m_dimension == 1) {
      gameArray[i][tempRowBoss][tempColumnBoss] = 'B';
      gameArray[0][tempRowBoss][tempColumnBoss] = 'H';
    } else if (gameArray[i][tempRowBoss][tempColumnBoss] == 'H') {
      --i;
    } else if (gameArray[i][tempRowBoss][tempColumnBoss] == 'W') {
      --i;
    } else {
      gameArray[i][tempRowBoss][tempColumnBoss] = 'B';
    }
  }
}

void World::printWorld() { // prints every level
  for (int i = 0; i < m_levels; ++i) {
    for (int j = 0; j < m_dimension; ++j) {
      for (int k = 0; k < m_dimension; ++k) {
          cout << gameArray[i][j][k] << " ";
      }
      cout << endl;
    }
      cout << endl;
  }
}

void World::printLevel() { // print only the current level that Mario is on
  for (int i = m_heroLevel; i < m_heroLevel + 1; ++i) {
    for (int j = 0; j < m_dimension; ++j) {
      for (int k = 0; k < m_dimension; ++k) {
          cout << gameArray[i][j][k] << " ";
      }
      cout << endl;
    }
      cout << endl;
  }
}

int World::getHeroLevel() {
  return m_heroLevel;
}

int World::getHeroRow() {
  return m_heroRow;
}

int World::getHeroColumn() {
  return m_heroColumn;
}

void World::setHeroLevel(int level) {
  m_heroLevel = level;
}

void World::setHeroRow(int row) {
  m_heroRow = row;
}

void World::setHeroColumn(int column) {
  m_heroColumn = column;
}

char*** World::getArray() {
  return gameArray;
}

void World::changeHeroRow(int change) {
  m_heroRow += change;
}

void World::changeHeroColumn(int change) {
  m_heroColumn += change;
}

int World::getDimension() {
  return m_dimension;
}

int World::getLevels() {
  return m_levels;
}
