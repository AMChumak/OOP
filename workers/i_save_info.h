#ifndef SAVE_INFO_INTERFACE_HEADER
#define SAVE_INFO_INTERFACE_HEADER
#include <iostream>
using namespace std;

class ISaveInfo {
public:
  virtual void saveStateAndRules(string fileName) = 0;
};

#endif