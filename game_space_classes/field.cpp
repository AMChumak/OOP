#include "field.h"
#include <iostream>
#include <stdexcept>

Field::Field() {
  int standartSize = 100;
  cells_ = new char *[standartSize];
  for (int i = 0; i < standartSize; i++) {
    cells_[i] = new char[standartSize];
    for (int j = 0; j < standartSize; j++) {
      cells_[i][j] = 0;
    }
  }
}

Field::Field(int height, int width, int **data) {
  cells_ = new char *[height];
  for (int i = 0; i < height; i++) {
    cells_[i] = new char[width];
    for (int j = 0; j < width; j++) {
      cells_[i][j] = data[i][j];
    }
  }
  height_ = height;
  width_ = width;
}

Field::Field(const Field &sample) {
  height_ = sample.height_;
  width_ = sample.width_;
  cells_ = new char *[height_];
  for (int i = 0; i < height_; i++) {
    cells_[i] = new char[width_];
    for (int j = 0; j < width_; j++) {
      cells_[i][j] = sample.cells_[1][1];
    }
  }
}

Field::~Field() {
  for (int i = 0; i < height_; i++) {
    delete[] cells_[i];
  }
  delete[] cells_;
}

Field &Field::operator=(const Field &source) {
  for (int i = 0; i < height_; i++) {
    delete[] cells_[i];
  }
  delete[] cells_;
  height_ = source.height_;
  width_ = source.width_;
  cells_ = new char *[height_];
  for (int i = 0; i < height_; i++) {
    cells_[i] = new char[width_];
    for (int j = 0; j < width_; j++) {
      cells_[i][j] = source.cells_[i][j];
    }
  }
  return *this;
}

char &Field::at(int firstIndex, int secondIndex) {
  if (firstIndex >= height_ || firstIndex < 0 || secondIndex >= width_ ||
      secondIndex < 0) {
    throw std::out_of_range("going out of field bounds");
  }
  return cells_[firstIndex][secondIndex];
}

int Field::getHeight() { return height_; }

int Field::getWidth() { return width_; }