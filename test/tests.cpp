#include <gtest/gtest.h>
// #include <iostream>
#include <ranges>

#include <DoublyLinkedSortedList.hpp>


TEST(DoublyLinkedSortedList, NullSharedPtrsTest) {
  std::shared_ptr<Node> nullSharedPtr1{ nullptr };
  EXPECT_FALSE(bool(nullSharedPtr1));
}

TEST(DoublyLinkedSortedList, WeakPtrPointsAtSharedPtr) {
  // I try to recreate list constructor problems
  std::shared_ptr<Node> nullShPtr{ nullptr };
  std::weak_ptr<Node> weakPtr{ nullShPtr };
}

TEST(DoublyLinkedSortedList, WeakPtrPointsAtSharedPtrEmptyTest) {
  // I try to recreate list constructor problems
  std::shared_ptr<Node> nullShPtr{ nullptr };
  std::weak_ptr<Node> weakPtr{ nullShPtr };
  EXPECT_FALSE(bool(nullShPtr));
}

TEST(DoublyLinkedSortedList, EmptyList) { DoublyLinkedSortedList list; }

TEST(DoublyLinkedSortedList, AddingValueToEmptyList) {
  const int val{ 42 };
  DoublyLinkedSortedList list;
  list.addValue(val);
}

TEST(DoublyLinkedSortedList, emptyOnEmptyList) {
  DoublyLinkedSortedList list;
  EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedSortedList, emptyOnListWithOneElem) {
  const int val{ 42 };
  DoublyLinkedSortedList list;
  EXPECT_TRUE(list.empty());
  list.addValue(val);
  EXPECT_FALSE(list.empty());
}

TEST(DoublyLinkedSortedList, InsertionInEmptyList) {
  const int val{ 42 };
  DoublyLinkedSortedList list;
  EXPECT_TRUE(list.empty());
  list.addValue(val);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.back(), val);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), val);
}

TEST(DoublyLinkedSortedList, ThreeTheSameVals) {
  const int val{ 42 };
  const int count{ 3 };
  DoublyLinkedSortedList list;
  for ([[maybe_unused]] auto _ : std::views::iota(0, count)) {
    list.addValue(val);
  }

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.back(), val);
  EXPECT_EQ(list.size(), count);
  EXPECT_EQ(list.front(), val);
}

TEST(DoublyLinkedSortedList, Add1234) {
  const std::array vals{ 1, 2, 3, 4 };
  DoublyLinkedSortedList list;
  for (auto val : vals) { //
    list.addValue(val);
  }

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.back(), 4);
  EXPECT_EQ(list.size(), vals.size());
  EXPECT_EQ(list.front(), 1);
}

TEST(DoublyLinkedSortedList, Add4321) {
  const std::array vals{ 4, 3, 2, 1 };
  DoublyLinkedSortedList list;
  for (auto val : vals) { //
    list.addValue(val);
  }

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.back(), 4);
  EXPECT_EQ(list.size(), vals.size());
  EXPECT_EQ(list.front(), 1);
}

TEST(DoublyLinkedSortedList, RemoveList) {
  const std::array vals{ 4, 3, 2, 1 };
  DoublyLinkedSortedList list;
  for (auto val : vals) { //
    list.addValue(val);
  }

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), vals.size());

  list.removeList();

  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(DoublyLinkedSortedList, showLeftToRight) {
  DoublyLinkedSortedList list;

  testing::internal::CaptureStdout();
  list.showLeftToRight();
  std::string stdOutput = testing::internal::GetCapturedStdout();
  EXPECT_EQ(stdOutput, "H{  }T\n");

  const std::array vals{ 1, 2, 3, 4 };
  for (auto val : vals) { //
    list.addValue(val);
  }

  testing::internal::CaptureStdout();
  list.showLeftToRight();
  stdOutput = testing::internal::GetCapturedStdout();
  EXPECT_EQ(stdOutput, "H{ 1, 2, 3, 4 }T\n");
}


TEST(DoublyLinkedSortedList, showRightToLeft) {
  DoublyLinkedSortedList list;

  testing::internal::CaptureStdout();
  list.showRightToLeft();
  std::string stdOutput = testing::internal::GetCapturedStdout();
  EXPECT_EQ(stdOutput, "T{  }H\n");

  const std::array vals{ 1, 2, 3, 4 };
  for (auto val : vals) { //
    list.addValue(val);
  }

  testing::internal::CaptureStdout();
  list.showRightToLeft();
  stdOutput = testing::internal::GetCapturedStdout();
  EXPECT_EQ(stdOutput, "T{ 4, 3, 2, 1 }H\n");
}

TEST(DoublyLinkedSortedList, longerList) {
  const std::array vals{ 1, 3, 2024, 2, 4, 1000, 500, 100, 900 };
  DoublyLinkedSortedList list;
  for (auto val : vals) { //
    list.addValue(val);
  }

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), vals.size());
}