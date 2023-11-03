#ifndef SUGGESTION_INTERFACE_HEADER
#define SUGGESTION_INTERFACE_HEADER
#include <iostream>
using namespace std;

class ICommandSuggestion {
public:
  virtual const char *what() = 0;
};

#endif