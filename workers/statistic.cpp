#include "statistic.h"

Statistics::Statistics(Field *newField, Universe *newUniverse) {
  gameField_ = newField;
  gameUniverse_ = newUniverse;
}

void Statistics::putInfo(IOutputCompiler *outputCompiler) {
  int fieldHeight = gameField_->getHeight();
  int fieldWidth = gameField_->getWidth();
  char **lifeField = new char *[fieldHeight];
  for (int i = 0; i < fieldHeight; i++) {
    lifeField[i] = new char[fieldWidth];
    for (int j = 0; j < fieldWidth; j++) {
      lifeField[i][j] = gameField_->at(i, j);
    }
  }
  outputCompiler->printInfo(gameUniverse_->getName(), lifeField, fieldHeight,
                            fieldWidth, gameUniverse_->getBirthRule(),
                            gameUniverse_->getSurviveRule());
}