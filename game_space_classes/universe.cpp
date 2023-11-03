#include "universe.h"
#include <iostream>
#include <string>

using namespace std;

void Universe::setName(string universeName) { name_ = universeName; }

string Universe::getName() const { return name_; }

void Universe::setBirthRule(set<int> newBirthRule) {
  birthRule_ = newBirthRule;
}

set<int> Universe::getBirthRule() const { return birthRule_; }

void Universe::setSurviveRule(set<int> newSurviveRule) {
  surviveRule_ = newSurviveRule;
}

set<int> Universe::getSurviveRule() const { return surviveRule_; }
