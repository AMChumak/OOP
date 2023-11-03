#include "console_output_compiler.h"
#include <exception>
#include <iostream>

void ConsoleCompiler::printInfo(string gameName, char **field, int height,
                                int width, set<int> birthRule,
                                set<int> surviveRule) {
  cout << "Universe: " << gameName << endl;
  cout << "Birth rule: ";
  for (set<int>::iterator it = birthRule.begin(); it != birthRule.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
  cout << "Survival rule: ";
  for (set<int>::iterator it = surviveRule.begin(); it != surviveRule.end();
       it++) {
    cout << *it << " ";
  }
  cout << endl;
  cout << "Current state: " << endl;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cout << (int)field[i][j] << " ";
    }
    cout << endl;
  }
}

void ConsoleCompiler::printRequest() {
  cout << "Please, print next command" << endl;
}

void ConsoleCompiler::printError(exception &gameException) {
  cout << gameException.what() << endl;
}

void ConsoleCompiler::printHelp(ICommandSuggestion &hint) {
  cout << hint.what() << endl;
}