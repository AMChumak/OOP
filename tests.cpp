#include <iostream>
#include "gtest/gtest.h"
#include "circular_buffer/circular_buffer.h"


namespace {
class CircularBufferTest : public testing::Test {
public:
  CircularBuffer<int> *firstIntBuffer;
  CircularBuffer<int> *secondIntBuffer;
  CircularBuffer<int> *thirdIntBuffer;
  CircularBuffer<double> *firstDoubleBuffer;
  CircularBuffer<double> *secondDoubleBuffer;
  CircularBuffer<double> *thirdDoubleBuffer;

protected:
  void SetUp() override {
    firstIntBuffer = new CircularBuffer<int>();
    secondIntBuffer = new CircularBuffer<int>(10);
    thirdIntBuffer = new CircularBuffer<int>(10, 5);

    firstDoubleBuffer = new CircularBuffer<double>();
    secondDoubleBuffer = new CircularBuffer<double>(7);
    thirdDoubleBuffer = new CircularBuffer<double>(7, 3.14);
    }

    void TearDown() override {
    delete firstIntBuffer;
    delete secondIntBuffer;
    delete thirdIntBuffer;

    firstIntBuffer = nullptr;
    secondIntBuffer = nullptr;
    thirdIntBuffer = nullptr;

    delete firstDoubleBuffer;
    delete secondDoubleBuffer;
    delete thirdDoubleBuffer;

    firstDoubleBuffer = nullptr;
    secondDoubleBuffer = nullptr;
    thirdDoubleBuffer = nullptr;
    }
};
} // namespace

TEST_F(CircularBufferTest, MethodAtTestInt) {
  EXPECT_EQ(thirdIntBuffer->at(2), 5);
}

TEST_F(CircularBufferTest, MethodAtTestDouble) {
  EXPECT_EQ(thirdDoubleBuffer->at(2), 3.14);
}

TEST_F(CircularBufferTest, OperatorSquareBracketsInt) {
  EXPECT_EQ((*thirdIntBuffer)[5], 5);
}

TEST_F(CircularBufferTest, OperatorSquareBracketsDouble) {
  EXPECT_EQ((*thirdDoubleBuffer)[5], 3.14);
}

TEST_F(CircularBufferTest, MethodFrontInt) {
  thirdIntBuffer->front() = 1;
  EXPECT_EQ((*thirdIntBuffer)[0], 1);
}

TEST_F(CircularBufferTest, MethodBackDouble) {
  thirdDoubleBuffer->back() = 2.7;
  EXPECT_EQ(thirdDoubleBuffer->at(6), 2.7);
}

TEST_F(CircularBufferTest, MethodPushBackInt) {
  secondIntBuffer->push_back(3);
  secondIntBuffer->push_back(7);
  secondIntBuffer->push_back(8);
  EXPECT_EQ(secondIntBuffer->at(0), 3);
  EXPECT_EQ(secondIntBuffer->at(1), 7);
  EXPECT_EQ(secondIntBuffer->at(2), 8);
}

TEST_F(CircularBufferTest, MethodPushFrontDouble) {
  secondDoubleBuffer->push_front(2.7);
  secondDoubleBuffer->push_front(2.6);
  secondDoubleBuffer->push_front(2.5);
  EXPECT_EQ(secondDoubleBuffer->at(2), 2.7);
  EXPECT_EQ(secondDoubleBuffer->at(1), 2.6);
  EXPECT_EQ(secondDoubleBuffer->at(0), 2.5);
}

TEST_F(CircularBufferTest, MethodIsLinearizeInt) {
  firstIntBuffer->push_back(1);
  firstIntBuffer->push_back(2);
  firstIntBuffer->push_back(3);
  EXPECT_EQ(firstIntBuffer->is_linearized(), false);
}

TEST_F(CircularBufferTest, MethodlinearizeDouble) {
  firstDoubleBuffer->push_back(1.1);
  firstDoubleBuffer->push_back(2.2);
  firstDoubleBuffer->push_back(3.3);
  firstDoubleBuffer->linearize();
  EXPECT_EQ(firstIntBuffer->is_linearized(), true);
}

TEST_F(CircularBufferTest, MethodRotateInt) {
  secondIntBuffer->push_back(1);
  secondIntBuffer->push_back(2);
  secondIntBuffer->push_front(3);
  secondIntBuffer->rotate(2);
  EXPECT_EQ(secondIntBuffer->is_linearized(), false);
  EXPECT_EQ(secondIntBuffer->at(0), 2);
  EXPECT_EQ(secondIntBuffer->at(1), 3);
  EXPECT_EQ(secondIntBuffer->at(2), 1);
}

TEST_F(CircularBufferTest, MethodSizeDouble) {
  secondDoubleBuffer->push_back(1);
  secondDoubleBuffer->push_back(2);
  secondDoubleBuffer->push_front(3);
  EXPECT_EQ(secondDoubleBuffer->size(), 3);
}

TEST_F(CircularBufferTest, MethodEmptyInt) {
  secondIntBuffer->push_back(1);
  secondIntBuffer->push_back(2);
  secondIntBuffer->push_front(3);
  EXPECT_EQ(secondIntBuffer->empty(), false);
  EXPECT_EQ(firstIntBuffer->empty(), true);
}

TEST_F(CircularBufferTest, MethodReserveDouble) {
  secondDoubleBuffer->push_back(1);
  secondDoubleBuffer->push_back(2);
  secondDoubleBuffer->push_front(3);
  EXPECT_EQ(secondDoubleBuffer->reserve(), 4);
}

TEST_F(CircularBufferTest, MethodfullInt) {
  secondIntBuffer->push_back(1);
  secondIntBuffer->push_back(2);
  secondIntBuffer->push_front(3);
  EXPECT_EQ(secondIntBuffer->full(), false);
  EXPECT_EQ(thirdIntBuffer->full(), true);
}

TEST_F(CircularBufferTest, MethodCapacityDouble) {
    EXPECT_EQ(secondDoubleBuffer->capacity(), 7);
}

TEST_F(CircularBufferTest, MethodSetCapacityInt) {
    secondIntBuffer->set_capacity(7);
    EXPECT_EQ(secondIntBuffer->capacity(), 7);
}

TEST_F(CircularBufferTest, MethodResizeDouble) {
    thirdDoubleBuffer->resize(12, 4.04);
    EXPECT_EQ(thirdDoubleBuffer->at(11),4.04);
}

TEST_F(CircularBufferTest, OperatorAssignmentInt) {
    //secondIntBuffer->set_capacity(7);
    (*secondIntBuffer) = (*thirdIntBuffer);
    EXPECT_EQ(secondIntBuffer->capacity(), 10);
    EXPECT_EQ(secondIntBuffer->at(3), 5);
    EXPECT_EQ(secondIntBuffer->full(), true);
}

TEST_F(CircularBufferTest, MethodSwapDouble) {
    secondDoubleBuffer->swap(*thirdDoubleBuffer);
    EXPECT_EQ(secondDoubleBuffer->capacity(), 7);
    EXPECT_EQ(secondDoubleBuffer->at(3), 3.14);
    EXPECT_EQ(thirdDoubleBuffer->capacity(), 7);
    EXPECT_EQ(thirdDoubleBuffer->size(), 0);
}

TEST_F(CircularBufferTest, MethodPopBackInt) {
    thirdIntBuffer->pop_back();
    thirdIntBuffer->pop_back();
    EXPECT_EQ(thirdIntBuffer->size(), 8);
}

TEST_F(CircularBufferTest, MethodPopfrontDouble) {
    thirdDoubleBuffer->pop_front();
    thirdDoubleBuffer->pop_front();
    EXPECT_EQ(thirdDoubleBuffer->size(), 5);
    EXPECT_EQ(thirdDoubleBuffer->is_linearized(), false);
}

TEST_F(CircularBufferTest, MethodInsertInt) {
    thirdIntBuffer->insert(4,28);
    EXPECT_EQ(thirdIntBuffer->at(4), 28);
    EXPECT_EQ(thirdIntBuffer->capacity(), 10);
    EXPECT_EQ(thirdIntBuffer->size(), 10);
}

TEST_F(CircularBufferTest, MethodEraseDouble) {
    thirdDoubleBuffer->at(6) = 1.678;
    thirdDoubleBuffer->erase(2,6);
    EXPECT_EQ(thirdDoubleBuffer->size(), 3);
    EXPECT_EQ(thirdDoubleBuffer->at(2), 1.678);
}

TEST_F(CircularBufferTest, MethodClearInt) {
    thirdIntBuffer->clear();
    EXPECT_EQ(thirdIntBuffer->size(), 0);
    EXPECT_EQ(thirdIntBuffer->capacity(), 10);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}