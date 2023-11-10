#include <iostream>
#include <fstream>
#include "World.h"
#include "Hero.h"
using namespace std;

int main(int argc, char** argv) {

  Hero h;
  h.playGame(argv[1], argv[2]); // argv[1] is the input file, argv[2] is the output file


  return 0;
}
