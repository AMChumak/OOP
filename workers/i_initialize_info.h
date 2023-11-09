#ifndef INITIALIZE_INFO_INTERFACE_HEADER
#define INITIALIZE_INFO_INTERFACE_HEADER
#include "../console_process_classes/i_output_compiler.h"
#include <iostream>
using namespace std;

class IInitializeInfo {
public:
  virtual void initializeStateAndRules(string fileName,
                                       IOutputCompiler *outputCompiler) = 0;
};

#endif