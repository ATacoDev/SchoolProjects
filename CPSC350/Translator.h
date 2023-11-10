#include "Model.h"

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
using namespace std;

class Translator {

public:
  Translator(); // default constructor
  virtual ~Translator(); // default destructor
  string translateEnglishWord(string word); // translates english word to robber form
  string translateEnglishSentence(string sentence); // translates entire string to robber form, also checking for spaces and punctuation

private:
  string m_tWord;
  string m_tSentence;
};

#endif
