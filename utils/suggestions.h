#ifndef SUGGESTIONS_HEADER
#define SUGGESTIONS_HEADER
#include "i_suggestion.h"
#include <iostream>

using namespace std;

class CommandListSuggestion : public ICommandSuggestion {
public:
  CommandListSuggestion() {}
  const char *what();
};
class TickCommandSuggestion : public ICommandSuggestion {
public:
  TickCommandSuggestion() {}
  const char *what();
};

class DumpCommandSuggestion : public ICommandSuggestion {
public:
  DumpCommandSuggestion() {}
  const char *what();
};

class ExitCommandSuggestion : public ICommandSuggestion {
public:
  ExitCommandSuggestion() {}
  const char *what();
};

class HelpCommandSuggestion : public ICommandSuggestion {
public:
  HelpCommandSuggestion() {}
  const char *what();
};

class InitializeCommandSuggestion : public ICommandSuggestion {
public:
  InitializeCommandSuggestion() {}
  const char *what();
};

#endif