#ifndef UNIVERSE_HEADER
#define UNIVERSE_HEADER
#include <iostream>
#include <set>

using namespace std;

class Universe {
private:
  string name_;
  set<int> birthRule_;
  set<int> surviveRule_;

public:
  void setName(string universeName);
  string getName() const;
  void setBirthRule(set<int> newBirthRule);
  set<int> getBirthRule() const;
  void setSurviveRule(set<int> newSurviveRule);
  set<int> getSurviveRule() const;
};

#endif