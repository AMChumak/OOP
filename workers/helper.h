#ifndef HELPER_HEADER
#define HELPER_HEADER
#include "../console_process_classes/i_output_compiler.h"
#include "../utils/game_commands.h"
#include <iostream>
using namespace std;

class Helper {
public:
  void getInfoAboutCommand(IOutputCompiler *compiler,
                           GameCommand difficultCommand);
  void getAllCommands(IOutputCompiler *compiler);
}; // написать реализацию

#endif