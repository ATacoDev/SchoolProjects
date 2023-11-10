#ifndef WORLD_H
#define WORLD_H

using namespace std;

class World {

public:
    World();
    virtual ~World();
    char*** createWorld(int levels, int dimension);
    void fillWorld(int lives, int pCoin, int pNothing, int pGoom, int pKoop, int pMush);
    int pickRandomItem();
    void placeHeroWarpBoss();
    void printWorld();
    void printLevel();

    int getHeroLevel();
    int getHeroRow();
    int getHeroColumn();

    void setHeroLevel(int level);
    void setHeroRow(int row);
    void setHeroColumn(int column);

    int getDimension();
    int getLevels();

    void changeHeroRow(int change);
    void changeHeroColumn(int change);

    char*** getArray();

private:

  int m_levels;
  int m_dimension;
  int m_lives;
  double m_pCoin;
  double m_pNothing;
  double m_pGoom;
  double m_pKoop;
  double m_pMush;

  int m_heroLevel;
  int m_heroRow;
  int m_heroColumn;

  char*** gameArray;

};

#endif
