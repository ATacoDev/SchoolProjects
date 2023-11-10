#include "Translator.h"

#include <iostream>
#include <cctype>
using namespace std;

Translator::Translator() { // default constructor
  m_tWord = "Unknown";
  m_tSentence = "Unknown";
}

Translator::~Translator() { // default destructor
}

string Translator::translateEnglishWord(string word) { // translateEnglishWord iterates through english word to translate it to robber form
  Model m;
  m_tWord = "";
  for (int i = 0; i < word.size(); ++i) { // iterate through word, if not a vowel or punctuation, translate to robber form
    if (tolower(word.at(i)) == 'a' || tolower(word.at(i)) == 'e' || tolower(word.at(i)) == 'i' || tolower(word.at(i)) == 'o' || tolower(word.at(i)) == 'u') { // check if vowel
      m_tWord += m.translateSingleVowel(word.at(i));
    } else if (ispunct(word.at(i)) || isspace(word.at(i)) || isdigit(word.at(i))) { // check to see if character is punctuation or a space
      m_tWord += word.at(i);
    } else {
      m_tWord += m.translateSingleConsonant(word.at(i)); // if not vowel/punctuation/space then translate the character and add it to return string
    }
  }
  return m_tWord;
}

string Translator::translateEnglishSentence(string sentence) { // utilize translateEnglishWord to translate a full sentence including spaces and punctuation
  Translator t;
  m_tSentence = ""; // return string
  string temp = ""; // holds english characters which are then translated whenever sentence.at(i) == " " or end of string
  for (int i = 0; i < sentence.size(); ++i) {
    if (i == sentence.size() - 1) {
      temp += sentence.at(i);
      m_tSentence += t.translateEnglishWord(temp);
      break;
    } else if (isspace(sentence.at(i))) {
      m_tSentence += t.translateEnglishWord(temp);
      m_tSentence += " ";
      temp = "";
      continue;
    } else {
      temp += sentence.at(i);
    }
  }
  return m_tSentence;
}
