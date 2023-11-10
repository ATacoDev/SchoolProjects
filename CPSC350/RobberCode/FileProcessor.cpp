#include "FileProcessor.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

FileProcessor::FileProcessor() { // default constructor
  m_in = "Unknown";
  m_out = "Unknown";
}

FileProcessor::~FileProcessor() { // default destructor
}

void FileProcessor::processFile(string in, string out) { // Takes english sentence as input, outputs html file
  Translator t;


  string tempBold = ""; // Need 2 different temporary strings to use for getLine()
  string tempItalic = "";
  fstream inFile;
  ofstream outFile; // using ofstream to create the outFile, assuming that inFile has already been created
  inFile.open(in);
  outFile.open(out);
  outFile << "<!DOCTYPE html><html><head><body><b>"; // bolds english sentnce
  while (getline(inFile, tempBold)) { // https://www.tutorialspoint.com/how-to-read-a-text-file-with-cplusplus helped me figure this out
    outFile << tempBold << "<br>";
  }

  outFile << "</b><i><br><br>"; // italic translated sentence
  inFile.close(); // closing inFile twice, allows use of geline() to keep spacing from inFile.txt -> outFile.html constant
  inFile.open(in);

  while(getline(inFile, tempItalic)) {
    outFile << t.translateEnglishSentence(tempItalic) << "<br>";
  }
  outFile << "</i></body></head></html>"; // end html file
  inFile.close();
  outFile.close();

}
