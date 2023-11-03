#include "file_handler.h"
#include "../utils/exceptions.h"
#include <bits/types/FILE.h>
#include <cctype>
#include <exception>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

// Help functions

void checkTitle(ifstream *inputStream) {
  string title;
  getline(*inputStream, title);
  if (title != "#Life 1.06") {
    throw FileFormatFail();
  }
}

string getName(ifstream *inputStream) {
  string tag, gameName;
  (*inputStream) >> tag;
  if (tag != "#N") {
    throw GameNameAbsence();
  }
  (*inputStream) >> gameName;
  return gameName;
}

void getRules(ifstream *inputStream, set<int> *birthRule,
              set<int> *surviveRule) {
  string tag, rule;
  (*inputStream) >> tag;
  if (tag != "#R") {
    throw GameRuleAbsence();
  }

  (*inputStream) >> rule;
  int i = 0;
  if (rule[i] != 'B') {
    throw GameRuleFormatFail();
  }
  i++;
  while (i < rule.length() && rule[i] != 'S') {
    if (isdigit(rule[i]) && rule[i] - '0' != 9) {
      birthRule->insert((int)(rule[i] - '0'));
    } else {
      throw GameRuleFormatFail();
    }
  }
  if (i == rule.length()) {
    throw GameRuleFormatFail();
  }
  i++;
  while (i < rule.length()) {
    if (isdigit(rule[i]) && rule[i] - '0' != 9) {
      surviveRule->insert((int)(rule[i] - '0'));
    } else {
      throw GameRuleFormatFail();
    }
  }
}

int isNumber(string number) {
  if (number.length() == 0)
    return 0;
  if (number[0] != '-' && !isdigit(number[0]))
    return 0;
  if (number[0] == '-' && number.length() == 1)
    return 0;
  for (int i = 1; i < number.length(); i++) {
    if (!isdigit(number[i]))
      return 0;
  }
  return 1;
}

void getAliveCellCoordinates(ifstream *inputStream, int *resultPointer) {
  string firstIndex, secondIndex;
  (*inputStream) >> firstIndex >> secondIndex;
  if (isNumber(firstIndex) && isNumber(secondIndex)) {
    resultPointer[0] = stoi(firstIndex);
    resultPointer[1] = stoi(secondIndex);
  } else {
    throw FileFormatFail();
  }
}

// FileHandler class methods

FileHandler::FileHandler(Field *gameField, Universe *gameUniverse) {
  gameField_ = gameField;
  gameUniverse_ = gameUniverse;
}

void FileHandler::initializeStateAndRules(string inputFile) {
  ifstream inputFileStream;
  int minimalFirstIndex;
  int minimalSecondIndex;

  string gameName;
  set<int> birthRule = {};
  set<int> surviveRule = {};

  vector<int[2]> aliveCells;
  int currentPair[2] = {0, 0};
  inputFileStream.open(inputFile, fstream::in);
  if (!inputFileStream) {
    inputFileStream.close();
    // вывод ошибки отсутствия файла
    return;
  }

  try {
    checkTitle(&inputFileStream);
  } catch (FileFormatFail &exception) {
    inputFileStream.close();
    // вывод текста ошибки
    return;
  }

  try {
    getName(&inputFileStream);
  } catch (GameNameAbsence &exception) {
    // вывод ошибки
    gameUniverse_->setName("GameLife");
  }

  if (!inputFileStream) {
    inputFileStream.close();
    // вывод ошибки длины файла
    return;
  }

  try {
    getRules(&inputFileStream, &birthRule, &surviveRule);
    gameUniverse_->setBirthRule(birthRule);
    gameUniverse_->setSurviveRule(surviveRule);
  } catch (GameRuleAbsence &exception) {
    inputFileStream.close();
    // вывод ошибки
    return;
  } catch (GameRuleFormatFail &exception) {
    inputFileStream.close();
    // вывод ошибки
    return;
  }

  while (inputFileStream) {
    try {
      getAliveCellCoordinates(&inputFileStream, currentPair);
      if (minimalFirstIndex > currentPair[0]) {
        minimalFirstIndex = currentPair[0];
      }
      if (minimalSecondIndex > currentPair[1]) {
        minimalSecondIndex = currentPair[1];
      }
      int samePairsCounter = 0;
      for (vector<int[2]>::iterator it = aliveCells.begin();
           it != aliveCells.end(); it++) {
        if ((*it)[0] == currentPair[0] && (*it)[1] == currentPair[1]) {
          // выводим ошибку о совпадениях
          samePairsCounter++;
        }
      }
      if (samePairsCounter == 0) {
        aliveCells.push_back({currentPair[0], currentPair[1]});
      }

      for (vector<int[2]>::iterator it = aliveCells.begin();
           it != aliveCells.end(); it++) {
        gameField_->at((*it)[0] + minimalFirstIndex,
                       (*it)[1] + minimalSecondIndex) = 1;
      }
    } catch (FileFormatFail &exception) {
      inputFileStream.close();
      // вывод ошибки
      return;
    }
  }

  inputFileStream.close();
}

void FileHandler::saveStateAndRules(string outputFile) {
  ofstream outputFileStream;
  outputFileStream.open(outputFile, fstream::out);
  if (!outputFileStream) {
    outputFileStream.close();
    // вывод ошибки отсутствия файла
    return;
  }
  outputFileStream << "#Life 1.06\n";

  outputFileStream << "#N " << gameUniverse_->getName() << "\n";

  outputFileStream << "#R B";
  set<int> rule = gameUniverse_->getBirthRule();
  for (set<int>::iterator it = rule.begin(); it != rule.end(); it++) {
    outputFileStream << *it;
  }
  outputFileStream << "/S";
  rule = gameUniverse_->getSurviveRule();
  for (set<int>::iterator it = rule.begin(); it != rule.end(); it++) {
    outputFileStream << *it;
  }
  outputFileStream << "\n";

  int fieldHeight = gameField_->getHeight();
  int fieldWidth = gameField_->getWidth();
  for (int i = 0; i < fieldHeight; i++) {
    for (int j = 0; j < fieldWidth; j++) {
      if (gameField_->at(i, j) == 1) {
        outputFileStream << i << " " << j << "\n";
      }
    }
  }

  outputFileStream.close();
}
