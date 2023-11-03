#ifndef OUTPUT_COMPILER_INTERFACE_HEADER
#define OUTPUT_COMPILER_INTERFACE_HEADER
#include "../utils/exceptions.h"
#include "../utils/suggestions.h"
#include <exception>
#include <iostream>
#include <set>
using namespace std;

class IOutputCompiler {
public:
  virtual void printInfo(string gameName, char **field, int height, int width,
                         set<int> birthRule, set<int> surviveRule) = 0;
  virtual void printRequest() = 0;
  virtual void printError(exception gameException) = 0;
  virtual void printHelp(ICommandSuggestion &hint) = 0;
};

#endif