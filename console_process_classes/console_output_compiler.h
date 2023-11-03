#ifndef CONSOLE_OUTPUT_COMPILER_HEADER
#define CONSOLE_OUTPUT_COMPILER_HEADER
#include "i_output_compiler.h"
#include <set>
using namespace std;

class ConsoleCompiler : public IOutputCompiler {
public:
  void printInfo(string gameName, char **field, int height, int width,
                 set<int> birthRule, set<int> surviveRule);
  void printRequest();
  void printError(exception &gameException);
  void printHelp(ICommandSuggestion &hint);
};

#endif