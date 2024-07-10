#include <stack>

#include "s21_gtests.h"

TEST(Stack, Construc1tor_Default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Constructor_Initializer) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  EXPECT_EQ(s21_stack.top(), 4);
  EXPECT_EQ(s21_stack.size(), size_t(4));
  EXPECT_EQ(s21_stack.empty(), false);
}

TEST(Stack, Construc2tor_Copy) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = s21_stack_1;

  EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());
    s21_stack_1.pop(), s21_stack_2.pop();
  }
}

TEST(Stack, Constructor_Move) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = std::move(s21_stack_1);
  s21::stack<char> s21_stack_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  EXPECT_EQ(s21_stack_1.size(), size_t(0));
  EXPECT_EQ(s21_stack_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
}

TEST(Stack, Modifier_Swap) {
  s21::stack<std::string> s21_stack_1 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::stack<std::string> s21_stack_2 = {"shtirlits", "vovochka", "poruchik"};
  s21::stack<std::string> s21_stack_3 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::stack<std::string> s21_stack_4 = {"shtirlits", "vovochka", "poruchik"};

  s21_stack_1.swap(s21_stack_2);

  EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_4.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
    s21_stack_1.pop(), s21_stack_4.pop();
  }
}

TEST(Stack, Operator_Move) {
  s21::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = std::move(our_stack_int);
  std_stack_empty = std::move(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Top) {
  s21::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<double> our_stack_double = {1.1f, 2.1f, 3.1f};
  std::stack<double> std_stack_double;
  std_stack_double.push(1.1f);
  std_stack_double.push(2.1f);
  std_stack_double.push(3.1f);
  s21::stack<std::string> our_stack_string = {"abc", "def", "ghf"};
  std::stack<std::string> std_stack_string;
  std_stack_string.push("abc");
  std_stack_string.push("def");
  std_stack_string.push("ghf");
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  EXPECT_EQ(our_stack_double.top(), std_stack_double.top());
  EXPECT_EQ(our_stack_string.top(), std_stack_string.top());
}

TEST(Stack, Empty) {
  s21::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.empty(), std_stack_empty.empty());
}

TEST(Stack, Size) {
  s21::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.size(), std_stack_empty.size());
}

TEST(Stack, Push) {
  s21::stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(Stack, Pop) {
  s21::stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  our_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  our_stack_int.pop();
  our_stack_int.pop();
  std_stack_int.pop();
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Swap) {
  s21::stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty.swap(our_stack_int);
  std_stack_empty.swap(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Insert_many) {
  s21::stack<int> st;
  st.insert_many_front(1, 2, 3);
  EXPECT_EQ(st.top(), 3);
  st.insert_many_front(4);
  EXPECT_EQ(st.top(), 3);
  st.pop();
  EXPECT_EQ(st.top(), 2);
  st.pop();
  EXPECT_EQ(st.top(), 1);
  st.pop();
  EXPECT_EQ(st.top(), 4);
}