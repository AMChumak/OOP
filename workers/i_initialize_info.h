#ifndef INITIALIZE_INFO_INTERFACE_HEADER
#define INITIALIZE_INFO_INTERFACE_HEADER
#include <iostream>
using namespace std;

class IInitializeInfo {
public:
  virtual void initializeStateAndRules(string fileName) = 0;
};

#endif