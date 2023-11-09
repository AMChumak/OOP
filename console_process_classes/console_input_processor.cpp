#include "console_input_processor.h"
#include "../utils/exceptions.h"
#include <cctype>
#include <iostream>
#include <string>

ConsoleInputProcessor::ConsoleInputProcessor(
    IOutputCompiler *initOutputCompiler) {
  outputCompiler_ = initOutputCompiler;
}

parseAnswerStruct ConsoleInputProcessor::parseCommand() {
  string commandKind;
  getline(cin, commandKind);

  if (commandKind == "dump") {
    string fileName = "";
    FileExtensionFail exceptionFileExtenmsion = FileExtensionFail();
    if (cin) {
      getline(cin, fileName);
      string fileFormatLife, fileFormatLif;
      if (fileName.length() < 5) {
        outputCompiler_->printError(exceptionFileExtenmsion);
        parseAnswerStruct errorResponse = {GameCommand::HELP_COMMAND,
                                           GameCommand::DUMP, 0, ""};
        return errorResponse;
      }
      fileFormatLif = fileName.substr(fileName.length() - 4, 4);
      if (fileName.length() >= 6) {
        fileFormatLife = fileName.substr(fileName.length() - 5, 5);
      }
      if (fileFormatLif != ".lif" ||
          (fileName.length() >= 6 && fileFormatLife != ".life")) {
        outputCompiler_->printError(exceptionFileExtenmsion);
        parseAnswerStruct errorResponse = {GameCommand::HELP_COMMAND,
                                           GameCommand::DUMP, 0, ""};
        return errorResponse;
      }
    }
    parseAnswerStruct response = {GameCommand::DUMP, GameCommand::INITIALIZE, 0,
                                  fileName};
    return response;

  } else if (commandKind == "tick") {
    int ticks = 1;
    IntArgumentAbsence exceptionIntArgument = IntArgumentAbsence();
    if (cin) {
      string ticksCountString;
      int ticksCountNumber = 0;
      getline(cin, ticksCountString);
      int dataLength = ticksCountString.length();
      for (int i = 0; i < dataLength; i++) {
        if (!isdigit(ticksCountString[i])) {
          outputCompiler_->printError(exceptionIntArgument);
          parseAnswerStruct errorResponse = {GameCommand::HELP_COMMAND,
                                             GameCommand::TICK, 0, ""};
          return errorResponse;
        } else {
          ticksCountNumber = ticksCountNumber * 10 + (int)ticksCountString[i];
        }
      }
      ticks = ticksCountNumber;
    }
    parseAnswerStruct response = {GameCommand::TICK, GameCommand::INITIALIZE,
                                  ticks, ""};
    return response;

  } else if (commandKind == "exit") {
    parseAnswerStruct response = {GameCommand::EXIT, GameCommand::INITIALIZE, 0,
                                  ""};
    return response;

  } else if (commandKind == "help") {
    GameCommand commandArgument = GameCommand::HELP_LIST;
    IncorrectCommand exceptionIncorrectCommand = IncorrectCommand();
    if (cin) {
      string argumentString;
      getline(cin, argumentString);
      if (argumentString == "dump") {
        commandArgument = GameCommand::DUMP;
      } else if (argumentString == "init") {
        commandArgument = GameCommand::INITIALIZE;
      } else if (argumentString == "tick") {
        commandArgument = GameCommand::TICK;
      } else if (argumentString == "exit") {
        commandArgument = GameCommand::EXIT;
      } else if (argumentString == "help") {
        commandArgument = GameCommand::HELP_COMMAND;
      } else {
        outputCompiler_->printError(exceptionIncorrectCommand);
        parseAnswerStruct errorResponse = {GameCommand::HELP_COMMAND,
                                           GameCommand::HELP_LIST, 0, ""};
        return errorResponse;
      }
    }
    parseAnswerStruct response = {GameCommand::HELP_COMMAND,
                                  GameCommand::HELP_LIST, 0, ""};
    return response;

  } else {
    IncorrectCommand exceptionIncorrectCommand = IncorrectCommand();
    outputCompiler_->printError(exceptionIncorrectCommand);
    parseAnswerStruct errorResponse = {GameCommand::HELP_COMMAND,
                                       GameCommand::HELP_LIST, 0, ""};
    return errorResponse;
  }
}
