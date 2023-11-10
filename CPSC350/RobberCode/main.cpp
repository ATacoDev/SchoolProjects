#include "FileProcessor.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {

  FileProcessor f;
  f.processFile(argv[1], argv[2]); // processFile() method with argv[1] as input.txt and argv[2] to the html output file


  return 0;
}
