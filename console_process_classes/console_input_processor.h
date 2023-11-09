#ifndef CONSOLE_INPUT_PROCESSOR_HEADER
#define CONSOLE_INPUT_PROCESSOR_HEADER
#include "i_input_processor.h"
#include "i_output_compiler.h"

class ConsoleInputProcessor : public IInputProcessor {
private:
  IOutputCompiler *outputCompiler_;

public:
  ConsoleInputProcessor(IOutputCompiler *initOutputCompiler);
  parseAnswerStruct parseCommand();
};

#endif