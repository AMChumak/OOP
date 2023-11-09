#ifndef SAVE_INFO_INTERFACE_HEADER
#define SAVE_INFO_INTERFACE_HEADER
#include "../console_process_classes/i_output_compiler.h"
#include <iostream>
using namespace std;

class ISaveInfo {
public:
  virtual void saveStateAndRules(string fileName,
                                 IOutputCompiler *outputCompiler) = 0;
};

#endif