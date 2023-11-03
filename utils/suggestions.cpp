#include "suggestions.h"

const char *CommandListSuggestion::what() {
  return "There is list of game commands:\n * dump <filename> - saves universe "
         "inf file with name = filename\n * tick <n> - Moves the universe n "
         "steps forward.By default, n = 1\n * exit - exits from game (without "
         "saving still)\n * help <command> - prints information about command";
}

const char *TickCommandSuggestion::what() {
  return "Use command \"tick <n>\" where n - count of life ticks, n = 1 by "
         "default ";
}

const char *DumpCommandSuggestion::what() {
  return "Use command \"dump <filename>\" where filename - name of file, which "
         "will be used for universe saving.\nIf file with this name doesn't "
         "exist, universe will be saved in file outputUniverse.life";
}

const char *ExitCommandSuggestion::what() {
  return "Use command \"exit\" to exit the game";
}

const char *HelpCommandSuggestion::what() {
  return "Use command \"help <command>\" where command - one of game "
         "commands.\nSet this field empty if you want see whole list";
}

const char *InitializeCommandSuggestion::what() {
  return "Use file format Life 1.06:\nIn the first string write #Life 1.06\nIn "
         "the second string write #B<n>/S<m> where n,m - count of neighbours "
         "neccessaries for birth and survival\nIn the next string whrite x y "
         "where (x,y) - coordinates of alive cells";
}
