#ifndef EXCEPTIONS_HEADER
#define EXCEPTIONS_HEADER
#include <exception>
#include <iostream>

using namespace std;

class GameNameAbsence : exception {
public:
  const char *what();
};

class FileFormatFail : exception {
public:
  const char *what();
};

class GameRuleAbsence : exception {
public:
  const char *what();
};

class GameRuleFormatFail : exception {
public:
  const char *what();
};

class IncorrectFilePath : exception {
public:
  const char *what();
};

#endif