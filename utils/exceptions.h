#ifndef EXCEPTIONS_HEADER
#define EXCEPTIONS_HEADER
#include <exception>
#include <iostream>

using namespace std;

class GameNameAbsence : public exception {
public:
  const char *what();
};

class FileFormatFail : public exception {
public:
  const char *what();
};

class GameRuleAbsence : public exception {
public:
  const char *what();
};

class GameRuleFormatFail : public exception {
public:
  const char *what();
};

class IncorrectFilePath : public exception {
public:
  const char *what();
};

class IncorrectCommand : public exception {
public:
  const char *what();
};

class FileExtensionFail : public exception {
public:
  const char *what();
};

class IntArgumentAbsence : public exception {
public:
  const char *what();
};

class TooManyArguments : public exception {
public:
  const char *what();
};

class TooShortFileLength : public exception {
public:
  const char *what();
};

class SameAliveCells : public exception {
public:
  const char *what();
};

#endif