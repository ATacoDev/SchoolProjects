#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "Hero.h"

using namespace std;


void Hero::playGame(string input, string output) {
  World w;
  Hero h;

  int levels;
  int dimension;
  int health;
  int c; // assigned to values from the input file
  int n;
  int g;
  int k;
  int m;

  ifstream fin(input);
  int test1;
  int test2;
  int test3;
  int test4;
  int test5;
  int test6;
  int test7;
  int test8;
  while (fin >> test1 >> test2 >> test3 >> test4 >> test5 >> test6 >> test7 >> test8) // stack overflow helped with this (in README)
    {
        levels = test1;
        dimension = test2;
        health = test3;
        c = test4;
        n = test5;
        g = test6;
        k = test7;
        m = test8;

    }

  ofstream outputFile;
  outputFile.open(output);

  w.createWorld(levels, dimension);
  w.fillWorld(health, c, n, g, k, m);
  w.placeHeroWarpBoss();
  char*** thisArray = w.getArray(); // create instance of array in this class, so that I don't have to use getters and setters

  outputFile << "GAME START!" << endl;
  outputFile << "Levels: " << levels << endl;
  outputFile << "Dimension: " << dimension << " x " << dimension << endl;
  outputFile << endl;
  outputFile << endl;

  for (int i = 0; i < levels; ++i) { // in charge of printing every level at start of game, so user can reference the original grids
    for (int j = 0; j < dimension; ++j) {
      for (int k = 0; k < dimension; ++k) {
        outputFile << thisArray[i][j][k] << " ";
      }
      outputFile << endl;
    }
    outputFile << endl;
  }

  outputFile << "-------------------------" << endl;

  bool bossBeaten = false; // used to check whether the boss of that level has been beaten
  int totalMoves = 0;
  m_power = 0;
  m_coinsCollected = 0;
  m_enemiesDefeated = 0;
  m_health = health;
  int count;

while (count >= 0) { // START
  count = 0; // counter of how many tiles there are left to explore (EXCLUDING Hero & Warp)
  for (int i = w.getHeroLevel(); i < w.getHeroLevel() + 1; ++i) {
    for (int j = 0; j < dimension; ++j) {
      for (int k = 0; k < dimension; ++k) {
        if (thisArray[i][j][k] != 'X' && thisArray[i][j][k] != 'W' && thisArray[i][j][k] != 'H') {
          count += 1;
        }
      }
    }
  }
  outputFile << "Level: " << w.getHeroLevel() << endl;
  int moveHero = (rand() % 4) + 1;
  /*
  moveHero is in charge of being assigned a random value from 1 - 4
  based on this value, mario will either move
  (1) up
  (2) right
  (3) down
  (4) left
  */
  int attack;
  int prevPower;
  int tempColumnHero;
  int tempRowHero;
  char temp;
  bool moveOn = false;
  bool exists = false;
  /*
  Lines 114 - 1993 are in charge of taking moveHero and having mario do actions based on what is in the tile that he moved to
  Code is long because switch statements are hard coded in
  Methods wouldn't work so I had to find an alternative way of going about the problem
  */
  if (moveHero == 1) {
    outputFile << "Mario is on position: (" << w.getHeroRow() << ", " << w.getHeroColumn() << ")" << endl;
    outputFile << "Mario is moving UP!" << endl;
    if (w.getHeroRow() != 0) {
      thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
      w.changeHeroRow(-1);
      char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
      switch(x) { //start
        case 'C':
          m_coinsCollected += 1;
          outputFile << "Mario collected a COIN!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          count -= 1;
          if (m_coinsCollected == 20) {
            outputFile << "+1 LIFE! ~20 coins~" << endl;
            m_health += 1;
            m_coinsCollected = 0;
          }
          break;
        case 'G':
        while (moveOn == false) {
          attack = (rand() % 10) + 1;
          prevPower = m_power;
          m_power = h.changePowerG(m_power, attack);
          m_health = h.findGoomba(m_health, prevPower, attack);
          if (attack != 1 && attack != 10) {
            outputFile << "Mario found a GOOMBA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
          break;
        case 'K':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerK(m_power, attack);
          m_health = h.findKoopa(m_health, prevPower, attack);
          if (attack <= 65) {
            outputFile << "Mario found a KOOPA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'B':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerB(m_power, attack);
          m_health = h.findBoss(m_health, prevPower, attack);
          if (attack >= 50) {
            outputFile << "Mario found THE BOSS and WON!" << endl;
            bossBeaten = true;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'X':
        outputFile << "Mario found an EMPTY SPACE!" << endl;
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          break;
        case 'W':
        outputFile << "Mario found the WARP PORTAL!" << endl;
        w.setHeroLevel(w.getHeroLevel() + 1);
          tempRowHero = (rand() % dimension);
          tempColumnHero = (rand() % dimension);
          if (1 == 1) {
            w.setHeroLevel(w.getHeroLevel());
            w.setHeroRow(rand() % dimension);
            w.setHeroColumn(rand() % dimension);
            char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
            bossBeaten = false;
            switch(temp) { //start
              case 'C':
                m_coinsCollected += 1;
                outputFile << "Mario collected a COIN!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                count -= 1;
                if (m_coinsCollected == 20) {
                  outputFile << "+1 LIFE! ~20 coins~" << endl;
                  m_health += 1;
                  m_coinsCollected = 0;
                }
                break;
              case 'G':
              while (moveOn == false) {
                attack = (rand() % 10) + 1;
                prevPower = m_power;
                m_power = h.changePowerG(m_power, attack);
                m_health = h.findGoomba(m_health, prevPower, attack);
                if (attack != 1 && attack != 10) {
                  outputFile << "Mario found a GOOMBA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
                break;
              case 'K':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerK(m_power, attack);
                m_health = h.findKoopa(m_health, prevPower, attack);
                if (attack <= 65) {
                  outputFile << "Mario found a KOOPA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'B':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerB(m_power, attack);
                m_health = h.findBoss(m_health, prevPower, attack);
                if (attack >= 50) {
                  outputFile << "Mario found THE BOSS and WON!" << endl;
                  bossBeaten = true;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'X':
              outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                break;
              case 'W':
              outputFile << "Mario spawned on the WARP PORTAL!" << endl;
              w.setHeroLevel(w.getHeroLevel() + 1);
              while (exists == false) {
                int tempRowHero = (rand() % dimension);
                int tempColumnHero = (rand() % dimension);
                if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                  thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                  w.setHeroLevel(w.getHeroLevel());
                  w.setHeroRow(w.getHeroRow());
                  w.setHeroColumn(w.getHeroColumn());
                  exists = true;
                } else {
                  exists = false;
                }
              }
              break;
              case 'M':
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              outputFile << "Mario spawned on a MUSHROOM!" << endl;
              count -= 1;
                if (m_power == 2) {
                  m_power = 2;
                } else {
                  m_power += 1;
                }
                break;
            } // end :O
          }
        break;
        case 'M':
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        outputFile << "Mario found a MUSHROOM!" << endl;
        count -= 1;
          if (m_power == 2) {
            m_power = 2;
          } else {
            m_power += 1;
          }
          break;
      } // end of switch for UP
      outputFile << "Coins collected: " << m_coinsCollected << endl;
      outputFile << "Health: " << m_health << endl;
      outputFile << "Power: " << m_power << endl;
      outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
    } else {
      thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
      w.changeHeroRow(dimension - 1);
      char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
      switch(x) { //start
        case 'C':
          m_coinsCollected += 1;
          outputFile << "Mario collected a COIN!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          count -= 1;
          if (m_coinsCollected == 20) {
            outputFile << "+1 LIFE! ~20 coins~" << endl;
            m_health += 1;
            m_coinsCollected = 0;
          }
          break;
        case 'G':
        while (moveOn == false) {
          attack = (rand() % 10) + 1;
          prevPower = m_power;
          m_power = h.changePowerG(m_power, attack);
          m_health = h.findGoomba(m_health, prevPower, attack);
          if (attack != 1 && attack != 10) {
            outputFile << "Mario found a GOOMBA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
          break;
        case 'K':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerK(m_power, attack);
          m_health = h.findKoopa(m_health, prevPower, attack);
          if (attack <= 65) {
            outputFile << "Mario found a KOOPA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'B':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerB(m_power, attack);
          m_health = h.findBoss(m_health, prevPower, attack);
          if (attack >= 50) {
            outputFile << "Mario found THE BOSS and WON!" << endl;
            bossBeaten = true;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'X':
        outputFile << "Mario found an EMPTY SPACE!" << endl;
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          break;
        case 'W':
        outputFile << "Mario found the WARP PORTAL!" << endl;
        w.setHeroLevel(w.getHeroLevel() + 1);
          tempRowHero = (rand() % dimension);
          tempColumnHero = (rand() % dimension);
          if (1 == 1) {
            w.setHeroLevel(w.getHeroLevel());
            w.setHeroRow(rand() % dimension);
            w.setHeroColumn(rand() % dimension);
            char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
            bossBeaten = false;
            switch(temp) { //start
              case 'C':
                m_coinsCollected += 1;
                outputFile << "Mario collected a COIN!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                count -= 1;
                if (m_coinsCollected == 20) {
                  outputFile << "+1 LIFE! ~20 coins~" << endl;
                  m_health += 1;
                  m_coinsCollected = 0;
                }
                break;
              case 'G':
              while (moveOn == false) {
                attack = (rand() % 10) + 1;
                prevPower = m_power;
                m_power = h.changePowerG(m_power, attack);
                m_health = h.findGoomba(m_health, prevPower, attack);
                if (attack != 1 && attack != 10) {
                  outputFile << "Mario found a GOOMBA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
                break;
              case 'K':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerK(m_power, attack);
                m_health = h.findKoopa(m_health, prevPower, attack);
                if (attack <= 65) {
                  outputFile << "Mario found a KOOPA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'B':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerB(m_power, attack);
                m_health = h.findBoss(m_health, prevPower, attack);
                if (attack >= 50) {
                  outputFile << "Mario found THE BOSS and WON!" << endl;
                  bossBeaten = true;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'X':
              outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                break;
              case 'W':
              outputFile << "Mario spawned on the WARP PORTAL!" << endl;
              w.setHeroLevel(w.getHeroLevel() + 1);
              while (exists == false) {
                int tempRowHero = (rand() % dimension);
                int tempColumnHero = (rand() % dimension);
                if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                  thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                  w.setHeroLevel(w.getHeroLevel());
                  w.setHeroRow(w.getHeroRow());
                  w.setHeroColumn(w.getHeroColumn());
                  exists = true;
                } else {
                  exists = false;
                }
              }
              break;
              case 'M':
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              outputFile << "Mario spawned on a MUSHROOM!" << endl;
              count -= 1;
                if (m_power == 2) {
                  m_power = 2;
                } else {
                  m_power += 1;
                }
                break;
            } // end :O
          }
        break;
        case 'M':
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        outputFile << "Mario found a MUSHROOM!" << endl;
        count -= 1;
          if (m_power == 2) {
            m_power = 2;
          } else {
            m_power += 1;
          }
          break;
      } // end of switch for UP at the end of the grid
      outputFile << "Coins collected: " << m_coinsCollected << endl;
      outputFile << "Health: " << m_health << endl;
      outputFile << "Power: " << m_power << endl;
      outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
    }
    } else if (moveHero == 2) {
      outputFile << "Mario is on position: (" << w.getHeroRow() << ", " << w.getHeroColumn() << ")" << endl;
      outputFile << "Mario is moving RIGHT!" << endl;
      if (w.getHeroColumn() != dimension - 1) {
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
        w.changeHeroColumn(1);
        char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
        switch(x) { //start
          case 'C':
            m_coinsCollected += 1;
            outputFile << "Mario collected a COIN!" << endl;
            thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
            count -= 1;
            if (m_coinsCollected == 20) {
              outputFile << "+1 LIFE! ~20 coins~" << endl;
              m_health += 1;
              m_coinsCollected = 0;
            }
            break;
          case 'G':
          while (moveOn == false) {
            attack = (rand() % 10) + 1;
            prevPower = m_power;
            m_power = h.changePowerG(m_power, attack);
            m_health = h.findGoomba(m_health, prevPower, attack);
            if (attack != 1 && attack != 10) {
              outputFile << "Mario found a GOOMBA and WON!" << endl;
              moveOn = true;
              count -= 1;
              m_enemiesDefeated += 1;
              if (m_enemiesDefeated == 7) {
                m_enemiesDefeated = 0;
                m_health += 1;
              }
            } else {
              outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
              m_enemiesDefeated = 0;
            }
          }
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          moveOn = false;
            break;
          case 'K':
          while (moveOn == false) {
            attack = (rand() % 100) + 1;
            prevPower = m_power;
            m_power = h.changePowerK(m_power, attack);
            m_health = h.findKoopa(m_health, prevPower, attack);
            if (attack <= 65) {
              outputFile << "Mario found a KOOPA and WON!" << endl;
              moveOn = true;
              count -= 1;
              m_enemiesDefeated += 1;
              if (m_enemiesDefeated == 7) {
                m_enemiesDefeated = 0;
                m_health += 1;
              }
            } else {
              outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
              m_enemiesDefeated = 0;
            }
          }
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          moveOn = false;
          break;
          case 'B':
          while (moveOn == false) {
            attack = (rand() % 100) + 1;
            prevPower = m_power;
            m_power = h.changePowerB(m_power, attack);
            m_health = h.findBoss(m_health, prevPower, attack);
            if (attack >= 50) {
              outputFile << "Mario found THE BOSS and WON!" << endl;
              bossBeaten = true;
              moveOn = true;
              count -= 1;
              m_enemiesDefeated += 1;
              if (m_enemiesDefeated == 7) {
                m_enemiesDefeated = 0;
                m_health += 1;
              }
            } else {
              outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
              m_enemiesDefeated = 0;
            }
          }
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          moveOn = false;
          break;
          case 'X':
          outputFile << "Mario found an EMPTY SPACE!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
            break;
          case 'W':
          outputFile << "Mario found the WARP PORTAL!" << endl;
          w.setHeroLevel(w.getHeroLevel() + 1);
            tempRowHero = (rand() % dimension);
            tempColumnHero = (rand() % dimension);
            if (1 == 1) {
              w.setHeroLevel(w.getHeroLevel());
              w.setHeroRow(rand() % dimension);
              w.setHeroColumn(rand() % dimension);
              char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
              bossBeaten = false;
              switch(temp) { //start
                case 'C':
                  m_coinsCollected += 1;
                  outputFile << "Mario collected a COIN!" << endl;
                  thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                  count -= 1;
                  if (m_coinsCollected == 20) {
                    outputFile << "+1 LIFE! ~20 coins~" << endl;
                    m_health += 1;
                    m_coinsCollected = 0;
                  }
                  break;
                case 'G':
                while (moveOn == false) {
                  attack = (rand() % 10) + 1;
                  prevPower = m_power;
                  m_power = h.changePowerG(m_power, attack);
                  m_health = h.findGoomba(m_health, prevPower, attack);
                  if (attack != 1 && attack != 10) {
                    outputFile << "Mario found a GOOMBA and WON!" << endl;
                    moveOn = true;
                    count -= 1;
                    m_enemiesDefeated += 1;
                    if (m_enemiesDefeated == 7) {
                      m_enemiesDefeated = 0;
                      m_health += 1;
                    }
                  } else {
                    outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                    m_enemiesDefeated = 0;
                  }
                }
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                moveOn = false;
                  break;
                case 'K':
                while (moveOn == false) {
                  attack = (rand() % 100) + 1;
                  prevPower = m_power;
                  m_power = h.changePowerK(m_power, attack);
                  m_health = h.findKoopa(m_health, prevPower, attack);
                  if (attack <= 65) {
                    outputFile << "Mario found a KOOPA and WON!" << endl;
                    moveOn = true;
                    count -= 1;
                    m_enemiesDefeated += 1;
                    if (m_enemiesDefeated == 7) {
                      m_enemiesDefeated = 0;
                      m_health += 1;
                    }
                  } else {
                    outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                    m_enemiesDefeated = 0;
                  }
                }
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                moveOn = false;
                break;
                case 'B':
                while (moveOn == false) {
                  attack = (rand() % 100) + 1;
                  prevPower = m_power;
                  m_power = h.changePowerB(m_power, attack);
                  m_health = h.findBoss(m_health, prevPower, attack);
                  if (attack >= 50) {
                    outputFile << "Mario found THE BOSS and WON!" << endl;
                    bossBeaten = true;
                    moveOn = true;
                    count -= 1;
                    m_enemiesDefeated += 1;
                    if (m_enemiesDefeated == 7) {
                      m_enemiesDefeated = 0;
                      m_health += 1;
                    }
                  } else {
                    outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                    m_enemiesDefeated = 0;
                  }
                }
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                moveOn = false;
                break;
                case 'X':
                outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                  break;
                case 'W':
                outputFile << "Mario spawned on the WARP PORTAL!" << endl;
                w.setHeroLevel(w.getHeroLevel() + 1);
                while (exists == false) {
                  int tempRowHero = (rand() % dimension);
                  int tempColumnHero = (rand() % dimension);
                  if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                    thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                    w.setHeroLevel(w.getHeroLevel());
                    w.setHeroRow(w.getHeroRow());
                    w.setHeroColumn(w.getHeroColumn());
                    exists = true;
                  } else {
                    exists = false;
                  }
                }
                break;
                case 'M':
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                outputFile << "Mario spawned on a MUSHROOM!" << endl;
                count -= 1;
                  if (m_power == 2) {
                    m_power = 2;
                  } else {
                    m_power += 1;
                  }
                  break;
              } // end :O
            }
          break;
          case 'M':
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          outputFile << "Mario found a MUSHROOM!" << endl;
          count -= 1;
            if (m_power == 2) {
              m_power = 2;
            } else {
              m_power += 1;
            }
            break;
        } // end of switch for RIGHT
        outputFile << "Coins collected: " << m_coinsCollected << endl;
        outputFile << "Health: " << m_health << endl;
        outputFile << "Power: " << m_power << endl;
        outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
      } else {
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
        w.changeHeroColumn(-(dimension - 1));
        char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
        switch(x) { //start
          case 'C':
            m_coinsCollected += 1;
            outputFile << "Mario collected a COIN!" << endl;
            thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
            count -= 1;
            if (m_coinsCollected == 20) {
              outputFile << "+1 LIFE! ~20 coins~" << endl;
              m_health += 1;
              m_coinsCollected = 0;
            }
            break;
          case 'G':
          while (moveOn == false) {
            attack = (rand() % 10) + 1;
            prevPower = m_power;
            m_power = h.changePowerG(m_power, attack);
            m_health = h.findGoomba(m_health, prevPower, attack);
            if (attack != 1 && attack != 10) {
              outputFile << "Mario found a GOOMBA and WON!" << endl;
              moveOn = true;
              count -= 1;
              m_enemiesDefeated += 1;
              if (m_enemiesDefeated == 7) {
                m_enemiesDefeated = 0;
                m_health += 1;
              }
            } else {
              outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
              m_enemiesDefeated = 0;
            }
          }
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          moveOn = false;
            break;
          case 'K':
          while (moveOn == false) {
            attack = (rand() % 100) + 1;
            prevPower = m_power;
            m_power = h.changePowerK(m_power, attack);
            m_health = h.findKoopa(m_health, prevPower, attack);
            if (attack <= 65) {
              outputFile << "Mario found a KOOPA and WON!" << endl;
              moveOn = true;
              count -= 1;
              m_enemiesDefeated += 1;
              if (m_enemiesDefeated == 7) {
                m_enemiesDefeated = 0;
                m_health += 1;
              }
            } else {
              outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
              m_enemiesDefeated = 0;
            }
          }
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          moveOn = false;
          break;
          case 'B':
          while (moveOn == false) {
            attack = (rand() % 100) + 1;
            prevPower = m_power;
            m_power = h.changePowerB(m_power, attack);
            m_health = h.findBoss(m_health, prevPower, attack);
            if (attack >= 50) {
              outputFile << "Mario found THE BOSS and WON!" << endl;
              bossBeaten = true;
              moveOn = true;
              count -= 1;
              m_enemiesDefeated += 1;
              if (m_enemiesDefeated == 7) {
                m_enemiesDefeated = 0;
                m_health += 1;
              }
            } else {
              outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
              m_enemiesDefeated = 0;
            }
          }
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          moveOn = false;
          break;
          case 'X':
          outputFile << "Mario found an EMPTY SPACE!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
            break;
          case 'W':
          outputFile << "Mario found the WARP PORTAL!" << endl;
          w.setHeroLevel(w.getHeroLevel() + 1);
            tempRowHero = (rand() % dimension);
            tempColumnHero = (rand() % dimension);
            if (1 == 1) {
              w.setHeroLevel(w.getHeroLevel());
              w.setHeroRow(rand() % dimension);
              w.setHeroColumn(rand() % dimension);
              char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
              bossBeaten = false;
              switch(temp) { //start
                case 'C':
                  m_coinsCollected += 1;
                  outputFile << "Mario collected a COIN!" << endl;
                  thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                  count -= 1;
                  if (m_coinsCollected == 20) {
                    outputFile << "+1 LIFE! ~20 coins~" << endl;
                    m_health += 1;
                    m_coinsCollected = 0;
                  }
                  break;
                case 'G':
                while (moveOn == false) {
                  attack = (rand() % 10) + 1;
                  prevPower = m_power;
                  m_power = h.changePowerG(m_power, attack);
                  m_health = h.findGoomba(m_health, prevPower, attack);
                  if (attack != 1 && attack != 10) {
                    outputFile << "Mario found a GOOMBA and WON!" << endl;
                    moveOn = true;
                    count -= 1;
                    m_enemiesDefeated += 1;
                    if (m_enemiesDefeated == 7) {
                      m_enemiesDefeated = 0;
                      m_health += 1;
                    }
                  } else {
                    outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                    m_enemiesDefeated = 0;
                  }
                }
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                moveOn = false;
                  break;
                case 'K':
                while (moveOn == false) {
                  attack = (rand() % 100) + 1;
                  prevPower = m_power;
                  m_power = h.changePowerK(m_power, attack);
                  m_health = h.findKoopa(m_health, prevPower, attack);
                  if (attack <= 65) {
                    outputFile << "Mario found a KOOPA and WON!" << endl;
                    moveOn = true;
                    count -= 1;
                    m_enemiesDefeated += 1;
                    if (m_enemiesDefeated == 7) {
                      m_enemiesDefeated = 0;
                      m_health += 1;
                    }
                  } else {
                    outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                    m_enemiesDefeated = 0;
                  }
                }
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                moveOn = false;
                break;
                case 'B':
                while (moveOn == false) {
                  attack = (rand() % 100) + 1;
                  prevPower = m_power;
                  m_power = h.changePowerB(m_power, attack);
                  m_health = h.findBoss(m_health, prevPower, attack);
                  if (attack >= 50) {
                    outputFile << "Mario found THE BOSS and WON!" << endl;
                    bossBeaten = true;
                    moveOn = true;
                    count -= 1;
                    m_enemiesDefeated += 1;
                    if (m_enemiesDefeated == 7) {
                      m_enemiesDefeated = 0;
                      m_health += 1;
                    }
                  } else {
                    outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                    m_enemiesDefeated = 0;
                  }
                }
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                moveOn = false;
                break;
                case 'X':
                outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                  break;
                case 'W':
                outputFile << "Mario spawned on the WARP PORTAL!" << endl;
                w.setHeroLevel(w.getHeroLevel() + 1);
                while (exists == false) {
                  int tempRowHero = (rand() % dimension);
                  int tempColumnHero = (rand() % dimension);
                  if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                    thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                    w.setHeroLevel(w.getHeroLevel());
                    w.setHeroRow(w.getHeroRow());
                    w.setHeroColumn(w.getHeroColumn());
                    exists = true;
                  } else {
                    exists = false;
                  }
                }
                break;
                case 'M':
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                outputFile << "Mario spawned on a MUSHROOM!" << endl;
                count -= 1;
                  if (m_power == 2) {
                    m_power = 2;
                  } else {
                    m_power += 1;
                  }
                  break;
              } // end :O
            }
          break;
          case 'M':
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          outputFile << "Mario found a MUSHROOM!" << endl;
          count -= 1;
            if (m_power == 2) {
              m_power = 2;
            } else {
              m_power += 1;
            }
            break;
        } // end of switch for RIGHT at the end of the grid
        outputFile << "Coins collected: " << m_coinsCollected << endl;
        outputFile << "Health: " << m_health << endl;
        outputFile << "Power: " << m_power << endl;
        outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
      }
    }
    else if (moveHero == 3) {
      outputFile << "Mario is on position: (" << w.getHeroRow() << ", " << w.getHeroColumn() << ")" << endl;
      outputFile << "Mario is moving DOWN!" << endl;
    if (w.getHeroRow() != dimension - 1) {
      thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
      w.changeHeroRow(1);
      char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
      switch(x) { //start
        case 'C':
          m_coinsCollected += 1;
          outputFile << "Mario collected a COIN!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          count -= 1;
          if (m_coinsCollected == 20) {
            outputFile << "+1 LIFE! ~20 coins~" << endl;
            m_health += 1;
            m_coinsCollected = 0;
          }
          break;
        case 'G':
        while (moveOn == false) {
          attack = (rand() % 10) + 1;
          prevPower = m_power;
          m_power = h.changePowerG(m_power, attack);
          m_health = h.findGoomba(m_health, prevPower, attack);
          if (attack != 1 && attack != 10) {
            outputFile << "Mario found a GOOMBA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
          break;
        case 'K':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerK(m_power, attack);
          m_health = h.findKoopa(m_health, prevPower, attack);
          if (attack <= 65) {
            outputFile << "Mario found a KOOPA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'B':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerB(m_power, attack);
          m_health = h.findBoss(m_health, prevPower, attack);
          if (attack >= 50) {
            outputFile << "Mario found THE BOSS and WON!" << endl;
            bossBeaten = true;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'X':
        outputFile << "Mario found an EMPTY SPACE!" << endl;
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          break;
        case 'W':
        outputFile << "Mario found the WARP PORTAL!" << endl;
        w.setHeroLevel(w.getHeroLevel() + 1);
          tempRowHero = (rand() % dimension);
          tempColumnHero = (rand() % dimension);
          if (1 == 1) {
            w.setHeroLevel(w.getHeroLevel());
            w.setHeroRow(rand() % dimension);
            w.setHeroColumn(rand() % dimension);
            char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
            bossBeaten = false;
            switch(temp) { //start
              case 'C':
                m_coinsCollected += 1;
                outputFile << "Mario collected a COIN!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                count -= 1;
                if (m_coinsCollected == 20) {
                  outputFile << "+1 LIFE! ~20 coins~" << endl;
                  m_health += 1;
                  m_coinsCollected = 0;
                }
                break;
              case 'G':
              while (moveOn == false) {
                attack = (rand() % 10) + 1;
                prevPower = m_power;
                m_power = h.changePowerG(m_power, attack);
                m_health = h.findGoomba(m_health, prevPower, attack);
                if (attack != 1 && attack != 10) {
                  outputFile << "Mario found a GOOMBA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
                break;
              case 'K':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerK(m_power, attack);
                m_health = h.findKoopa(m_health, prevPower, attack);
                if (attack <= 65) {
                  outputFile << "Mario found a KOOPA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'B':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerB(m_power, attack);
                m_health = h.findBoss(m_health, prevPower, attack);
                if (attack >= 50) {
                  outputFile << "Mario found THE BOSS and WON!" << endl;
                  bossBeaten = true;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'X':
              outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                break;
              case 'W':
              outputFile << "Mario spawned on the WARP PORTAL!" << endl;
              w.setHeroLevel(w.getHeroLevel() + 1);
              while (exists == false) {
                int tempRowHero = (rand() % dimension);
                int tempColumnHero = (rand() % dimension);
                if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                  thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                  w.setHeroLevel(w.getHeroLevel());
                  w.setHeroRow(w.getHeroRow());
                  w.setHeroColumn(w.getHeroColumn());
                  exists = true;
                } else {
                  exists = false;
                }
              }
              break;
              case 'M':
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              outputFile << "Mario spawned on a MUSHROOM!" << endl;
              count -= 1;
                if (m_power == 2) {
                  m_power = 2;
                } else {
                  m_power += 1;
                }
                break;
            } // end :O
          }
        break;
        case 'M':
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        outputFile << "Mario found a MUSHROOM!" << endl;
        count -= 1;
          if (m_power == 2) {
            m_power = 2;
          } else {
            m_power += 1;
          }
          break;
      } // end of switch for DOWN
      outputFile << "Coins collected: " << m_coinsCollected << endl;
      outputFile << "Health: " << m_health << endl;
      outputFile << "Power: " << m_power << endl;
      outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
    } else {
      thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
      w.changeHeroRow(-(dimension - 1));
      char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
      switch(x) { //start
        case 'C':
          m_coinsCollected += 1;
          outputFile << "Mario collected a COIN!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          count -= 1;
          if (m_coinsCollected == 20) {
            outputFile << "+1 LIFE! ~20 coins~" << endl;
            m_health += 1;
            m_coinsCollected = 0;
          }
          break;
        case 'G':
        while (moveOn == false) {
          attack = (rand() % 10) + 1;
          prevPower = m_power;
          m_power = h.changePowerG(m_power, attack);
          m_health = h.findGoomba(m_health, prevPower, attack);
          if (attack != 1 && attack != 10) {
            outputFile << "Mario found a GOOMBA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
          break;
        case 'K':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerK(m_power, attack);
          m_health = h.findKoopa(m_health, prevPower, attack);
          if (attack <= 65) {
            outputFile << "Mario found a KOOPA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'B':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerB(m_power, attack);
          m_health = h.findBoss(m_health, prevPower, attack);
          if (attack >= 50) {
            outputFile << "Mario found THE BOSS and WON!" << endl;
            bossBeaten = true;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'X':
        outputFile << "Mario found an EMPTY SPACE!" << endl;
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          break;
        case 'W':
        outputFile << "Mario found the WARP PORTAL!" << endl;
        w.setHeroLevel(w.getHeroLevel() + 1);
          tempRowHero = (rand() % dimension);
          tempColumnHero = (rand() % dimension);
          if (1 == 1) {
            w.setHeroLevel(w.getHeroLevel());
            w.setHeroRow(rand() % dimension);
            w.setHeroColumn(rand() % dimension);
            char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
            bossBeaten = false;
            switch(temp) { //start
              case 'C':
                m_coinsCollected += 1;
                outputFile << "Mario collected a COIN!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                count -= 1;
                if (m_coinsCollected == 20) {
                  outputFile << "+1 LIFE! ~20 coins~" << endl;
                  m_health += 1;
                  m_coinsCollected = 0;
                }
                break;
              case 'G':
              while (moveOn == false) {
                attack = (rand() % 10) + 1;
                prevPower = m_power;
                m_power = h.changePowerG(m_power, attack);
                m_health = h.findGoomba(m_health, prevPower, attack);
                if (attack != 1 && attack != 10) {
                  outputFile << "Mario found a GOOMBA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
                break;
              case 'K':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerK(m_power, attack);
                m_health = h.findKoopa(m_health, prevPower, attack);
                if (attack <= 65) {
                  outputFile << "Mario found a KOOPA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'B':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerB(m_power, attack);
                m_health = h.findBoss(m_health, prevPower, attack);
                if (attack >= 50) {
                  outputFile << "Mario found THE BOSS and WON!" << endl;
                  bossBeaten = true;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'X':
              outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                break;
              case 'W':
              outputFile << "Mario spawned on the WARP PORTAL!" << endl;
              w.setHeroLevel(w.getHeroLevel() + 1);
              while (exists == false) {
                int tempRowHero = (rand() % dimension);
                int tempColumnHero = (rand() % dimension);
                if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                  thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                  w.setHeroLevel(w.getHeroLevel());
                  w.setHeroRow(w.getHeroRow());
                  w.setHeroColumn(w.getHeroColumn());
                  exists = true;
                } else {
                  exists = false;
                }
              }
              break;
              case 'M':
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              outputFile << "Mario spawned on a MUSHROOM!" << endl;
              count -= 1;
                if (m_power == 2) {
                  m_power = 2;
                } else {
                  m_power += 1;
                }
                break;
            } // end :O
          }
        break;
        case 'M':
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        outputFile << "Mario found a MUSHROOM!" << endl;
        count -= 1;
          if (m_power == 2) {
            m_power = 2;
          } else {
            m_power += 1;
          }
          break;
      } // end of switch for DOWN at the end of the grid
      outputFile << "Coins collected: " << m_coinsCollected << endl;
      outputFile << "Health: " << m_health << endl;
      outputFile << "Power: " << m_power << endl;
      outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
    }
  } else {
    outputFile << "Mario is on position: (" << w.getHeroRow() << ", " << w.getHeroColumn() << ")" << endl;
    outputFile << "Mario is moving LEFT!" << endl;
    if (w.getHeroColumn() != 0) {
      thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
      w.changeHeroColumn(-1);
      char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
      switch(x) { //start
        case 'C':
          m_coinsCollected += 1;
          outputFile << "Mario collected a COIN!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          count -= 1;
          if (m_coinsCollected == 20) {
            outputFile << "+1 LIFE! ~20 coins~" << endl;
            m_health += 1;
            m_coinsCollected = 0;
          }
          break;
        case 'G':
        while (moveOn == false) {
          attack = (rand() % 10) + 1;
          prevPower = m_power;
          m_power = h.changePowerG(m_power, attack);
          m_health = h.findGoomba(m_health, prevPower, attack);
          if (attack != 1 && attack != 10) {
            outputFile << "Mario found a GOOMBA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
          break;
        case 'K':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerK(m_power, attack);
          m_health = h.findKoopa(m_health, prevPower, attack);
          if (attack <= 65) {
            outputFile << "Mario found a KOOPA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'B':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerB(m_power, attack);
          m_health = h.findBoss(m_health, prevPower, attack);
          if (attack >= 50) {
            outputFile << "Mario found THE BOSS and WON!" << endl;
            bossBeaten = true;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'X':
        outputFile << "Mario found an EMPTY SPACE!" << endl;
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          break;
        case 'W':
        outputFile << "Mario found the WARP PORTAL!" << endl;
        w.setHeroLevel(w.getHeroLevel() + 1);
          tempRowHero = (rand() % dimension);
          tempColumnHero = (rand() % dimension);
          if (1 == 1) {
            w.setHeroLevel(w.getHeroLevel());
            w.setHeroRow(rand() % dimension);
            w.setHeroColumn(rand() % dimension);
            char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
            bossBeaten = false;
            switch(temp) { //start
              case 'C':
                m_coinsCollected += 1;
                outputFile << "Mario collected a COIN!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                count -= 1;
                if (m_coinsCollected == 20) {
                  outputFile << "+1 LIFE! ~20 coins~" << endl;
                  m_health += 1;
                  m_coinsCollected = 0;
                }
                break;
              case 'G':
              while (moveOn == false) {
                attack = (rand() % 10) + 1;
                prevPower = m_power;
                m_power = h.changePowerG(m_power, attack);
                m_health = h.findGoomba(m_health, prevPower, attack);
                if (attack != 1 && attack != 10) {
                  outputFile << "Mario found a GOOMBA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
                break;
              case 'K':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerK(m_power, attack);
                m_health = h.findKoopa(m_health, prevPower, attack);
                if (attack <= 65) {
                  outputFile << "Mario found a KOOPA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'B':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerB(m_power, attack);
                m_health = h.findBoss(m_health, prevPower, attack);
                if (attack >= 50) {
                  outputFile << "Mario found THE BOSS and WON!" << endl;
                  bossBeaten = true;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'X':
              outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                break;
              case 'W':
              outputFile << "Mario spawned on the WARP PORTAL!" << endl;
              w.setHeroLevel(w.getHeroLevel() + 1);
              while (exists == false) {
                int tempRowHero = (rand() % dimension);
                int tempColumnHero = (rand() % dimension);
                if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                  thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                  w.setHeroLevel(w.getHeroLevel());
                  w.setHeroRow(w.getHeroRow());
                  w.setHeroColumn(w.getHeroColumn());
                  exists = true;
                } else {
                  exists = false;
                }
              }
              break;
              case 'M':
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              outputFile << "Mario spawned on a MUSHROOM!" << endl;
              count -= 1;
                if (m_power == 2) {
                  m_power = 2;
                } else {
                  m_power += 1;
                }
                break;
            } // end :O
          }
        break;
        case 'M':
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        outputFile << "Mario found a MUSHROOM!" << endl;
        count -= 1;
          if (m_power == 2) {
            m_power = 2;
          } else {
            m_power += 1;
          }
          break;
      } // end of switch for LEFT
      outputFile << "Coins collected: " << m_coinsCollected << endl;
      outputFile << "Health: " << m_health << endl;
      outputFile << "Power: " << m_power << endl;
      outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
    } else {
      thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'X';
      w.changeHeroColumn(dimension - 1);
      char x = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
      switch(x) { //start
        case 'C':
          m_coinsCollected += 1;
          outputFile << "Mario collected a COIN!" << endl;
          thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          count -= 1;
          if (m_coinsCollected == 20) {
            outputFile << "+1 LIFE! ~20 coins~" << endl;
            m_health += 1;
            m_coinsCollected = 0;
          }
          break;
        case 'G':
        while (moveOn == false) {
          attack = (rand() % 10) + 1;
          prevPower = m_power;
          m_power = h.changePowerG(m_power, attack);
          m_health = h.findGoomba(m_health, prevPower, attack);
          if (attack != 1 && attack != 10) {
            outputFile << "Mario found a GOOMBA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a GOOMBA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
          break;
        case 'K':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerK(m_power, attack);
          m_health = h.findKoopa(m_health, prevPower, attack);
          if (attack <= 65) {
            outputFile << "Mario found a KOOPA and WON!" << endl;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'B':
        while (moveOn == false) {
          attack = (rand() % 100) + 1;
          prevPower = m_power;
          m_power = h.changePowerB(m_power, attack);
          m_health = h.findBoss(m_health, prevPower, attack);
          if (attack >= 50) {
            outputFile << "Mario found THE BOSS and WON!" << endl;
            bossBeaten = true;
            moveOn = true;
            count -= 1;
            m_enemiesDefeated += 1;
            if (m_enemiesDefeated == 7) {
              m_enemiesDefeated = 0;
              m_health += 1;
            }
          } else {
            outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
            m_enemiesDefeated = 0;
          }
        }
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        moveOn = false;
        break;
        case 'X':
        outputFile << "Mario found an EMPTY SPACE!" << endl;
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
          break;
        case 'W':
        outputFile << "Mario found the WARP PORTAL!" << endl;
        w.setHeroLevel(w.getHeroLevel() + 1);
          tempRowHero = (rand() % dimension);
          tempColumnHero = (rand() % dimension);
          if (1 == 1) {
            w.setHeroLevel(w.getHeroLevel());
            w.setHeroRow(rand() % dimension);
            w.setHeroColumn(rand() % dimension);
            char temp = thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()];
            bossBeaten = false;
            switch(temp) { //start
              case 'C':
                m_coinsCollected += 1;
                outputFile << "Mario collected a COIN!" << endl;
                thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                count -= 1;
                if (m_coinsCollected == 20) {
                  outputFile << "+1 LIFE! ~20 coins~" << endl;
                  m_health += 1;
                  m_coinsCollected = 0;
                }
                break;
              case 'G':
              while (moveOn == false) {
                attack = (rand() % 10) + 1;
                prevPower = m_power;
                m_power = h.changePowerG(m_power, attack);
                m_health = h.findGoomba(m_health, prevPower, attack);
                if (attack != 1 && attack != 10) {
                  outputFile << "Mario found a GOOMBA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a GOOMBA and LOST! << Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
                break;
              case 'K':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerK(m_power, attack);
                m_health = h.findKoopa(m_health, prevPower, attack);
                if (attack <= 65) {
                  outputFile << "Mario found a KOOPA and WON!" << endl;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found a KOOPA and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'B':
              while (moveOn == false) {
                attack = (rand() % 100) + 1;
                prevPower = m_power;
                m_power = h.changePowerB(m_power, attack);
                m_health = h.findBoss(m_health, prevPower, attack);
                if (attack >= 50) {
                  outputFile << "Mario found THE BOSS and WON!" << endl;
                  bossBeaten = true;
                  moveOn = true;
                  count -= 1;
                  m_enemiesDefeated += 1;
                  if (m_enemiesDefeated == 7) {
                    m_enemiesDefeated = 0;
                    m_health += 1;
                  }
                } else {
                  outputFile << "Mario found THE BOSS and LOST! Mario will attempt again!" << endl;
                  m_enemiesDefeated = 0;
                }
              }
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              moveOn = false;
              break;
              case 'X':
              outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
                break;
              case 'W':
              outputFile << "Mario spawned on the WARP PORTAL!" << endl;
              w.setHeroLevel(w.getHeroLevel() + 1);
              while (exists == false) {
                int tempRowHero = (rand() % dimension);
                int tempColumnHero = (rand() % dimension);
                if (thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'B' && thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] != 'W') {
                  thisArray[w.getHeroLevel()][tempRowHero][tempColumnHero] = 'X';
                  w.setHeroLevel(w.getHeroLevel());
                  w.setHeroRow(w.getHeroRow());
                  w.setHeroColumn(w.getHeroColumn());
                  exists = true;
                } else {
                  exists = false;
                }
              }
              break;
              case 'M':
              thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
              outputFile << "Mario spawned on a MUSHROOM!" << endl;
              count -= 1;
                if (m_power == 2) {
                  m_power = 2;
                } else {
                  m_power += 1;
                }
                break;
            } // end :O
          }
        break;
        case 'M':
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        outputFile << "Mario found a MUSHROOM!" << endl;
        count -= 1;
          if (m_power == 2) {
            m_power = 2;
          } else {
            m_power += 1;
          }
          break;
      } // end pf switch for LEFT at the end of the grid
      outputFile << "Coins collected: " << m_coinsCollected << endl;
      outputFile << "Health: " << m_health << endl;
      outputFile << "Power: " << m_power << endl;
      outputFile << "Enemies defeated in a row: " << m_enemiesDefeated << endl;
    }
  }
  totalMoves += 1;
  thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
  for (int i = w.getHeroLevel(); i < w.getHeroLevel() + 1; ++i) {
    for (int j = 0; j < dimension; ++j) {
      for (int k = 0; k < dimension; ++k) {
        outputFile << thisArray[i][j][k] << " ";
      }
      outputFile << endl;
    }
    outputFile << endl;
  }
  outputFile << "-------------------------" << endl;


  if (bossBeaten == true && w.getHeroLevel() != levels - 1 && m_health != 0) { // if the boss is beaten and mario isn't on the final level, mario moves to the next level
    outputFile << "Boss Beaten! Moving to next level" << endl;
    w.setHeroLevel(w.getHeroLevel() + 1);
    bool nextHero = false;
    while (nextHero == false) {
      int nextSpawnR = rand() % dimension;
      int nextSpawnC = rand() % dimension;
      char nextChar = thisArray[w.getHeroLevel()][nextSpawnR][nextSpawnC];
      if (nextChar == 'X') {
        w.setHeroRow(nextSpawnR);
        w.setHeroColumn(nextSpawnC);
        outputFile << "Mario spawned on an EMPTY SPACE!" << endl;
        thisArray[w.getHeroLevel()][w.getHeroRow()][w.getHeroColumn()] = 'H';
        nextHero = true;
      } else if (nextChar == 'C') {
        outputFile << "Mario spawned on a COIN!" << endl;
        m_coinsCollected += 1;
        nextHero = true;
      }
    }
    bossBeaten = false;
  }

  if (bossBeaten == true && w.getHeroLevel() == levels - 1) { // beat final boss on lasta level, end game
    int leave = 0;
    outputFile << "Level: " << w.getHeroLevel() << endl;
    outputFile << "FINAL BOSS BEATEN!" << endl << "YOU WIN" << endl;
    outputFile << "Took " << totalMoves << " moves" << endl;
    outputFile.close();
    exit(leave);
  }

  if (m_health <= 0) { // ran out of health, end game
    int leave = 0;
    outputFile << "You ran out of health!!!" << endl << "YOU LOSE" << endl;
    outputFile << "Took " << totalMoves << " moves" << endl;
    outputFile.close();
    exit(leave);
  }

  }
}



  int Hero::findCoin(int coin, int health) {
    // cout << "Mario found a COIN!" << endl;
    return coin + 1;
  }

  int Hero::changePowerG(int power, int attack) {
    if (attack == 10 || attack == 1) {
      if (power > 0) {
        power -= 1;
      } else {
        power = 0;
      }
      return power;
    }
    return power;
  }

  int Hero::findGoomba(int health, int power, int attack) {
    if (attack == 10 || attack == 1) {
      if (power > 0) {
        // cout << "Mario found a GOOMBA and LOST! let's try again!" << endl;
        return health;
      } else {
        // cout << "Mario found a GOOMBA and LOST! let's try again!" << endl;
        return health - 1;
      }
    }
    // cout << "Mario found a GOOMBA and WON!" << endl;
    return health;
  }

  int Hero::changePowerK(int power, int attack) {
    if (attack > 65) {
      if (power > 0) {
        power -= 1;
      } else {
        power = 0;
      }
      return power;
    }
    return power;
  }

  int Hero::findKoopa(int health, int power, int attack) {
    if (attack > 65) {
      if (power > 0) {
        // cout << "Mario found a KOOPA and LOST! let's try again!" << endl;
        return health;
      } else {
        // cout << "Mario found a KOOPA and LOST! let's try again!" << endl;
        return health - 1;
      }
    }
    // cout << "Mario found a KOOPA and WON!" << endl;
    return health;
  }

  int Hero::changePowerB(int power, int attack) {
    if (attack < 50) {
      if (power == 2) {
        power -= 2;
      } else {
        power = 0;
      }
      return power;
    }
    return power;
  }

  int Hero::findBoss(int health, int power, int attack) {
    if (attack < 50) {
      if (power >= 2) {
        // cout << "Mario found the BOSS and WON!" << endl;
        return health;
      } else {
        // cout << "Mario found the BOSS and WON!" << endl;
        return health - 1;
      }
    } else {
    // cout << "Mario found the BOSS and LOST! let's try again!" << endl;
    return health;
  }
  }
