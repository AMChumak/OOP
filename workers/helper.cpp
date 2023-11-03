#include "helper.h"
#include "../utils/suggestions.h"
#include <iostream>

using namespace std;

void Helper::getAllCommands(IOutputCompiler *compiler) {
  CommandListSuggestion listOfCommands;
  compiler->printHelp(listOfCommands);
}

void Helper::getInfoAboutCommand(IOutputCompiler *compiler,
                                 GameCommand difficultCommand) {
  switch (difficultCommand) {
  case GameCommand::TICK: {
    TickCommandSuggestion tickSuggestion;
    compiler->printHelp(tickSuggestion);
    break;
  }
  case GameCommand::INITIALIZE: {
    InitializeCommandSuggestion initSuggestion;
    compiler->printHelp(initSuggestion);
    break;
  }
    // дописать switch
  }
}