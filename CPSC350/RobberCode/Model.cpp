#include "Model.h"
#include <iostream>
using namespace std;

Model::Model() { // default constructor
  m_conString = "Unknown";
  m_vowString = "Unknown";
}

Model::~Model() { // default destructor
}

string Model::translateSingleConsonant(char consonant) { // assuming letter is a consonant, translate it to robber form. Ex: s = sos
  m_conString = "";
  m_conString += consonant;
  m_conString += 'o';
  m_conString += consonant;
  return m_conString;
}

string Model::translateSingleVowel(char vowel) { // turn character into a string, and return it to user. (vowels & punctuation do not need to be changed into robber form)
  m_vowString = "";
  m_vowString += vowel;
  return m_vowString;
}
