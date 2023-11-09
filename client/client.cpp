#include "client.h"
#include <iostream>

Client::Client(IOutputCompiler *initOutputCompiler,
               IInputProcessor *initInputProcessor,
               IInitializeInfo *initInitializer, ISaveInfo *initSaveInterface,
               Iterator *initIterator, Statistics *initStatisticsService,
               Helper *initHelper) {
  outputComipler_ = initOutputCompiler;
  inputProcessor_ = initInputProcessor;
  initializer_ = initInitializer;
  saveInterface_ = initSaveInterface;
  fieldIterator_ = initIterator;
  statisticsService_ = initStatisticsService;
  helper_ = initHelper;
  currentCommand_ = {GameCommand::HELP_COMMAND, GameCommand::HELP_LIST, 0, ""};
}

void Client::request() {
  outputComipler_->printRequest();
  currentCommand_ = inputProcessor_->parseCommand();
} // здесь исключения не нужны

void Client::execute() {
  switch (currentCommand_.commandType) {
  case GameCommand::HELP_COMMAND: {
    try {
      helper_->getInfoAboutCommand(outputComipler_,
                                   currentCommand_.helpCommandArgument);
    } catch (IncorrectCommand &exception) {
      outputComipler_->printError(exception);
    }
  }
  case GameCommand::HELP_LIST: {
    try {
      helper_->getInfoAboutCommand(outputComipler_, HELP_LIST);
    } catch (IncorrectCommand &exception) {
      outputComipler_->printError(exception);
    }
  }
  case GameCommand::DUMP: {
    try {
      saveInterface_->saveStateAndRules(currentCommand_.filename,
                                        outputComipler_);
    } catch (IncorrectFilePath &exception) {
      outputComipler_->printError(exception);
    }
  }
  case GameCommand::EXIT: {
    exit(0);
  }
  case GameCommand::INITIALIZE: {
    try {
      initializer_->initializeStateAndRules(currentCommand_.filename,
                                            outputComipler_);
      statisticsService_->putInfo(outputComipler_);
    } catch (exception &gameException) {
      outputComipler_->printError(gameException);
    }
  }
  case GameCommand::STATISTICS: {
    statisticsService_->putInfo(outputComipler_);
  }
  case GameCommand::TICK: {
    fieldIterator_->goOnNTicks(currentCommand_.ticks);
    statisticsService_->putInfo(outputComipler_);
  }
  }
}

void Client::setCommandState(parseAnswerStruct initCommandStruct) {
  currentCommand_ = initCommandStruct;
}