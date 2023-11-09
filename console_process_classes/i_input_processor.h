#ifndef INPUT_PROCESSOR_INTERFACE_HEADER
#define INPUT_PROCESSOR_INTERFACE_HEADER
#include "../utils/parse_answer_struct.h"

class IInputProcessor {
public:
  virtual parseAnswerStruct parseCommand() = 0;
};
#endif