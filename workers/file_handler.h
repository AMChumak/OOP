#ifndef FILE_HANDLER_HEADER
#define FILE_HANDLER_HEADER
#include "../game_space_classes/field.h"
#include "../game_space_classes/universe.h"
#include "i_initialize_info.h"
#include "i_save_info.h"
#include <fstream>

using namespace std;

class FileHandler : public IInitializeInfo, public ISaveInfo {
private:
  Field *gameField_;
  Universe *gameUniverse_;

public:
  FileHandler(Field *gameField, Universe *gameUniverse);
  void saveStateAndRules(string outputFile, IOutputCompiler *outputCompiler);
  void initializeStateAndRules(string inputFile,
                               IOutputCompiler *outputCompiler);
};

#endif