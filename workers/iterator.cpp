#include "iterator.h"
#include <exception>
#include <iostream>
#include <stdexcept>

Iterator::Iterator(Field *currentState, Field *nextState,
                   Universe *gameUniverse) {
  currentState_ = currentState;
  nextState_ = nextState;
  gameUniverse_ = gameUniverse;
}

void Iterator::getNextIteration() {
  int fieldHeight = currentState_->getHeight();
  int fieldWidth = currentState_->getWidth();
  set<int> birthRule = gameUniverse_->getBirthRule();
  set<int> surviveRule = gameUniverse_->getSurviveRule();
  try {
    for (int i = 0; i < fieldHeight; i++) {
      for (int j = 0; j < fieldWidth; j++) {
        int countNeighbours = 0;
        for (int k = -1; k < 2; k++) {
          for (int l = -1; l < 2; l++) {
            countNeighbours +=
                currentState_->at((fieldHeight + i + k) % fieldHeight,
                                  (fieldWidth + j + l) % fieldWidth);
          }
        }
        if (currentState_->at(i, j) == 1) {
          if (surviveRule.find(countNeighbours) == surviveRule.end()) {
            nextState_->at(i, j) = 0;
          } else {
            nextState_->at(i, j) = 1;
          }
        } else {
          if (birthRule.find(countNeighbours) == birthRule.end()) {
            nextState_->at(i, j) = 0;
          } else {
            nextState_->at(i, j) = 1;
          }
        }
      }
    }

    (*currentState_) = (*nextState_);

  } catch (exception &out_of_range) {
    // Сделать вывод ошибки
  }
}

void Iterator::goOnNTicks(int countTicks) {
  for (int i = 0; i < countTicks; i++) {
    getNextIteration();
  }
}