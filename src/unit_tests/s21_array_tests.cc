#include <array>

#include "s21_gtests.h"

//////////////////////////////// member functions

TEST(TestArray, DefaultConstructor) {
  s21::array<int, 10> arr;

  // Size check
  EXPECT_EQ(arr.size(), 10);

  // Zero initialization check
  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(TestArray, InitListConstructor) {
  s21::array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Size check
  EXPECT_EQ(arr.size(), 10);

  // Initialization check
  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(arr[i], (int)i);
  }
}

TEST(TestArray, CopyConstructor) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};
  s21::array<int, 5> arrCopy(arr);

  // Size check
  EXPECT_EQ(arrCopy.size(), 5);

  // Copy check
  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(TestArray, MoveConstructor) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};
  s21::array<int, 5> arrMoved(std::move(arr));

  // Size check
  EXPECT_EQ(arrMoved.size(), 5);

  // Move check
  for (size_t i = 0; i < arrMoved.size(); i++) {
    EXPECT_EQ(arrMoved[i], (int)i);
  }
}

TEST(TestArray, CopyOperator) {
  s21::array<int, 5> arr1 = {0, 1, 2, 3, 4};
  s21::array<int, 5> arr2 = {5, 6, 7, 8, 9};

  arr1 = arr2;

  for (size_t i = 0; i < arr1.size(); i++) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(TestArray, MoveOperator) {
  s21::array<int, 5> arr1 = {0, 1, 2, 3, 4};
  s21::array<int, 5> arr2 = {5, 6, 7, 8, 9};

  arr1 = std::move(arr2);

  for (size_t i = 0; i < arr1.size(); i++) {
    EXPECT_EQ(arr1[i], (int)i + 5);
  }
}

//////////////////////////////// element access

TEST(TestArray, AtCorrect) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_EQ(arr.at(2), 2);
}

TEST(TestArray, AtError) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(TestArray, cAtCorrect) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_EQ(arr.at(2), 2);
}

TEST(TestArray, cAtError) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(TestArray, BracketOperator) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(arr[i], (int)i);
  }

  arr[3] = 5;
  EXPECT_EQ(arr[3], 5);
}

TEST(TestArray, cBracketOperator) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(arr[i], (int)i);
  }
}

TEST(TestArray, Front) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_EQ(arr.front(), 0);
}

TEST(TestArray, Back) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_EQ(arr.back(), 4);
}

TEST(TestArray, cFront) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_EQ(arr.front(), 0);
}

TEST(TestArray, cBack) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_EQ(arr.back(), 4);
}

TEST(TestArray, Data) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  auto it = arr.data();
  EXPECT_EQ(*it, 0);

  // Element access check
  it++;
  *it = 5;
  EXPECT_EQ(arr[1], 5);
}

TEST(TestArray, cData) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  auto it = arr.data();
  it++;
  EXPECT_EQ(*it, 1);
}

//////////////////////////////// iterators

TEST(TestArray, Begin) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  auto it = arr.begin();
  EXPECT_EQ(*it, 0);

  // Element access check
  *it = 5;
  EXPECT_EQ(arr[0], 5);
}

TEST(TestArray, End) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  auto it = arr.end();

  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(TestArray, cBegin) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  auto it = arr.begin();
  EXPECT_EQ(*it, 0);
}

TEST(TestArray, cEnd) {
  const s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  auto it = arr.end();

  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

//////////////////////////////// capacity

TEST(TestArray, Empty1) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_FALSE(arr.empty());
}

TEST(TestArray, Empty2) {
  s21::array<int, 0> arr;

  EXPECT_TRUE(arr.empty());
}

TEST(TestArray, Size) {
  s21::array<int, 5> arr = {0, 1, 2, 3, 4};

  EXPECT_EQ(arr.size(), 5);
}

TEST(TestArray, SizeEmpty) {
  s21::array<int, 0> arr;

  EXPECT_EQ(arr.size(), 0);
}

TEST(TestArray, MaxSize) {
  s21::array<int, 5> arr;

  EXPECT_EQ(arr.max_size(), 5);
}

//////////////////////////////// operations

TEST(TestArray, Fill) {
  s21::array<int, 5> arr;
  arr.fill(5);

  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(arr[i], 5);
  }
}

TEST(TestArray, Swap) {
  s21::array<int, 5> arr1 = {0, 1, 2, 3, 4};
  s21::array<int, 5> arr2 = {5, 6, 7, 8, 9};

  arr1.swap(arr2);

  for (size_t i = 0; i < arr1.size(); i++) {
    EXPECT_EQ(arr1[i], (int)i + 5);
  }

  for (size_t i = 0; i < arr2.size(); i++) {
    EXPECT_EQ(arr2[i], (int)i);
  }
}