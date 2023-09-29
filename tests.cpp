#include <iostream>
#include "gtest/gtest.h"
#include "circular_buffer/circular_buffer.h"



// Empty constructor test
TEST(BufferTests, EmptyConstructorTest) {
  CircularBuffer<int> firstBuffer = CircularBuffer<int>();
  EXPECT_EQ(firstBuffer.size(), 0);
}

// constructor test
TEST(BufferTests, ConstructorTest) {
  CircularBuffer<int> firstBuffer = CircularBuffer<int>(10, 5);
  EXPECT_EQ(firstBuffer.size(), 10);
  EXPECT_EQ(firstBuffer[0], 5);
}

TEST(BufferTests, MethodAtTest) {
  CircularBuffer<char> firstBuffer = CircularBuffer<char>(3, 'd');

  EXPECT_EQ(firstBuffer[0], 'a');
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}