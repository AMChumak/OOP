#include "build/_deps/googletest-src/googletest/include/gtest/gtest.h"
#include "circular_buffer.h"


// Demonstrate some basic assertions.
TEST(BufferTests, DefinitionTest) {
  CircularBuffer<int> *firstBuffer = new CircularBuffer<int>(10, 1);
  CircularBuffer<int> *secondBuffer = new CircularBuffer<int>(10, 1);
  EXPECT_EQ(firstBuffer, secondBuffer);
  firstBuffer->at(1) = 5;
  EXPECT_EQ(firstBuffer, secondBuffer);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}