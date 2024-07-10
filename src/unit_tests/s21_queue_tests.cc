#include <queue>

#include "s21_gtests.h"

TEST(Queue, Constructor_Default) {
  s21::queue<int> q1;
  std::queue<int> q2;
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
}

TEST(Queue, Constructor_Initialized) {
  s21::queue<int> q1{1, 2, 3, 4};
  std::queue<int> q2;
  q2.push(1);
  q2.push(2);
  q2.push(3);
  q2.push(4);
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.front(), q2.front());
    q1.pop();
    q2.pop();
  }
}

TEST(Queue, Constructor_Copy) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2 = s21_queue_1;

  EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());
    s21_queue_1.pop(), s21_queue_2.pop();
  }
}

TEST(Queue, Constructor_Move) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2 = std::move(s21_queue_1);
  s21::queue<char> s21_queue_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  EXPECT_EQ(s21_queue_1.size(), size_t(0));
  EXPECT_EQ(s21_queue_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
}

TEST(Queue, Push) {
  s21::queue<int> q;
  std::queue<int> std_q;

  q.push(1);
  std_q.push(1);
  EXPECT_EQ(q.front(), std_q.front());
  EXPECT_EQ(q.back(), std_q.back());

  q.push(2);
  std_q.push(2);
  EXPECT_EQ(q.front(), std_q.front());
  EXPECT_EQ(q.back(), std_q.back());

  q.push(3);
  std_q.push(3);
  EXPECT_EQ(q.front(), std_q.front());
  EXPECT_EQ(q.back(), std_q.back());
}

TEST(Queue, Pop) {
  s21::queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  our_queue_int.pop();
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  our_queue_int.pop();
  our_queue_int.pop();
  std_queue_int.pop();
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Assignment) {
  s21::queue<int> q1{1, 2, 3, 4};
  s21::queue<int> q2;
  q2 = std::move(q1);
  std::queue<int> q3;
  q3.push(1);
  q3.push(2);
  q3.push(3);
  q3.push(4);
  std::queue<int> q4;
  q4 = std::move(q3);
  EXPECT_EQ(q2.empty(), q4.empty());
  EXPECT_EQ(q2.size(), q4.size());
  while (!q2.empty()) {
    EXPECT_EQ(q2.front(), q4.front());
    q2.pop();
    q4.pop();
  }
}

TEST(Queue, FrontAndBack) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<double> our_queue_double = {1.1f, 2.1f, 3.1f};
  std::queue<double> std_queue_double;
  std_queue_double.push(1.1f);
  std_queue_double.push(2.1f);
  std_queue_double.push(3.1f);
  s21::queue<std::string> our_queue_string = {"abc", "def", "ghf"};
  std::queue<std::string> std_queue_string;
  std_queue_string.push("abc");
  std_queue_string.push("def");
  std_queue_string.push("ghf");
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_double.front(), std_queue_double.front());
  EXPECT_EQ(our_queue_string.front(), std_queue_string.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  EXPECT_EQ(our_queue_double.back(), std_queue_double.back());
  EXPECT_EQ(our_queue_string.back(), std_queue_string.back());
}

TEST(Queue, Empty) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.empty(), std_queue_empty.empty());
}

TEST(Queue, Size) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.size(), std_queue_int.size());
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.size(), std_queue_empty.size());
}

TEST(Queue, Swap) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty.swap(our_queue_int);
  std_queue_empty.swap(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Modifier_Swap) {
  s21::queue<std::string> s21_queue_1 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::queue<std::string> s21_queue_2 = {"shtirlits", "vovochka", "poruchik"};
  s21::queue<std::string> s21_queue_3 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::queue<std::string> s21_queue_4 = {"shtirlits", "vovochka", "poruchik"};

  s21_queue_1.swap(s21_queue_2);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_4.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
    s21_queue_1.pop(), s21_queue_4.pop();
  }
}

TEST(Queue, Insert_many_back) {
  s21::queue<int> qu1;
  qu1.insert_many_back();
  EXPECT_TRUE(qu1.empty());

  qu1.insert_many_back(1, 2, 3);
  for (int i = 1; i < 4; ++i, qu1.pop()) {
    EXPECT_EQ(i, qu1.front());
  }

  s21::queue<int> qu2 = {1, 2, 3};
  qu2.insert_many_back(4);
  for (int i = 1; i < 5; ++i, qu2.pop()) {
    EXPECT_EQ(i, qu2.front());
  }

  s21::queue<int> qu3 = {1, 2, 3};
  qu3.insert_many_back(4, 5, 6, 7, 8, 9, 10);
  for (int i = 1; i < 11; ++i, qu3.pop()) {
    EXPECT_EQ(i, qu3.front());
  }
}