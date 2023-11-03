#ifndef CLIENT_HEADER
#define CLIENT_HEADER
#include "../console_process_classes/console_output_compiler.h"
#include "../utils/game_commands.h"
#include "i_execute.h"
#include "i_request.h"
#include <iostream>

using namespace std;

class Client : public IRequest, public IExecute {
private:
  IOutputCompiler *outputComipler;

public:
  void request();
  void execute();
}; // написать реализацию

#endif