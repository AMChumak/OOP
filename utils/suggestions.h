#ifndef SUGGESTIONS_HEADER
#define SUGGESTIONS_HEADER
#include "i_suggestion.h"
#include <iostream>

using namespace std;

class CommandListSuggestion : public ICommandSuggestion {
public:
  const char *what() override;
};

class TickCommandSuggestion : public ICommandSuggestion {
public:
  const char *what() override;
};

class DumpCommandSuggestion : public ICommandSuggestion {
public:
  const char *what() override;
};

class ExitCommandSuggestion : public ICommandSuggestion {
public:
  const char *what() override;
};

class HelpCommandSuggestion : public ICommandSuggestion {
public:
  const char *what() override;
};

class InitializeCommandSuggestion : public ICommandSuggestion {
public:
  const char *what() override;
};

#endif