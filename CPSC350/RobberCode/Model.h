#ifndef MODEL_H
#define MODEL_H

#include <string>
using namespace std;

class Model {

public:
  Model(); // default constructor
  virtual ~Model(); // default destructor
  string translateSingleConsonant(char consonant); // returns robber form of consonant
  string translateSingleVowel(char vowel); // translates char into string and returns it

private:
  string m_conString;
  string m_vowString;
};

#endif
