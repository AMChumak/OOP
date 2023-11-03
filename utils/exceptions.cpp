#include "exceptions.h"

const char *GameNameAbsence::what() {
  return "The name of universe absents in configuration";
}

const char *FileFormatFail::what() {
  return "Configuration file has no format #Life 1.06";
}

const char *GameRuleAbsence::what() {
  return "The rules of universe absent in configuration";
}

const char *GameRuleFormatFail::what() {
  return "The rules of universe has no format #R B{x}/S{y}, where {x} and {y} "
         "are sequences of nambers in limits 0..8";
}

const char *IncorrectFilePath::what() {
  return "Could not open a file with this path";
}