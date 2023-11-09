#ifndef CLIENT_HEADER
#define CLIENT_HEADER
#include "../console_process_classes/i_input_processor.h"
#include "../console_process_classes/i_output_compiler.h"
#include "../utils/game_commands.h"
#include "../utils/parse_answer_struct.h"
#include "../workers/helper.h"
#include "../workers/i_initialize_info.h"
#include "../workers/i_save_info.h"
#include "../workers/iterator.h"
#include "../workers/statistics.h"
#include "i_execute.h"
#include "i_request.h"
#include <iostream>

using namespace std;

class Client : public IRequest, public IExecute {
private:
  IOutputCompiler *outputComipler_;
  IInputProcessor *inputProcessor_;
  IInitializeInfo *initializer_;
  ISaveInfo *saveInterface_;
  Iterator *fieldIterator_;
  Statistics *statisticsService_;
  Helper *helper_;
  parseAnswerStruct currentCommand_;

public:
  Client(IOutputCompiler *initOutputCompiler,
         IInputProcessor *initInputProcessor, IInitializeInfo *initInitializer,
         ISaveInfo *initSaveInterface, Iterator *initIterator,
         Statistics *initStatisticsService, Helper *initHelper);
  void request();
  void execute();
  void setCommandState(parseAnswerStruct initCommandStruct);
};

#endif