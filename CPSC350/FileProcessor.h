#include "Translator.h"

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

using namespace std;

class FileProcessor {

public:
  FileProcessor(); // default constructor
  virtual ~FileProcessor(); // default destructor
  void processFile(string inputFile, string outputFile); // takes txt file with english sentence("inputFile"), and returns html file with translation ("outputFile")

private:
  string m_in;
  string m_out;

};

#endif
