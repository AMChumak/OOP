#ifndef FIELD_HEADER
#define FIELD_HEADER
#include <iostream>

class Field {
private:
  char **cells_;
  int height_, width_;

public:
  Field();
  Field(int height, int width, int **data);
  Field(const Field &sample);
  ~Field();
  char &at(int firstIndex, int secondIndex);
  int getHeight();
  int getWidth();
  Field &operator=(const Field &source);
};

#endif