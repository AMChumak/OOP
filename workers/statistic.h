#ifndef STATISTIC_HEADER
#define STATISTIC_HEADER
#include "../console_process_classes/i_output_compiler.h"
#include "../game_space_classes/field.h"
#include "../game_space_classes/universe.h"
#include <iostream>

using namespace std;

class Statistics {
private:
  Field *gameField_;
  Universe *gameUniverse_;

public:
  Statistics(Field *newField, Universe *newUniverse);
  void putInfo(IOutputCompiler *outputCompiler);
};

#endif