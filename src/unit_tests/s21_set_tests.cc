#include <set>

#include "s21_gtests.h"

template <typename value_type>
void print_set(s21::set<value_type> &myset, std::set<value_type> &stdset) {
  std::cout << "\n\tTEST_set:PRINT\n\n";
  std::cout << "std::set : " << std::endl;
  for (const auto &kv : stdset) {
    std::cout << kv << " ";
  }
  std::cout << '\n';
  std::cout << "s21::set :" << std::endl;
  for (const auto &kv : myset) {
    std::cout << kv << " ";
  }
  std::cout << '\n';
  std::cout << '\n';
}

template <typename value_type>
bool is_equal_sets(s21::set<value_type> &s1, std::set<value_type> &s2) {
  bool success = true;
  if (s1.size() != s2.size()) success = false;
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  for (; it1 != s1.end(); ++it1, ++it2) {
    if (*it1 != *it2) success = false;
  }
  if (!success) print_set(s1, s2);
  return success;
}

//**********************CONSTRUCTORS**********************
TEST(Set, Default_Constructor) {
  s21::set<int> s21_s;
  std::set<int> std_s;
  EXPECT_EQ(s21_s.empty(), std_s.empty());

  s21::set<std::string> s21_ss;
  std::set<std::string> std_ss;
  EXPECT_EQ(s21_ss.empty(), std_ss.empty());

  s21::set<double> s21_sd;
  std::set<double> std_sd;
  EXPECT_EQ(s21_sd.empty(), std_sd.empty());
}

TEST(Set, Initial_Constructor) {
  s21::set<int> my1{8, 5, 3, 2};
  std::set<int> std1{8, 5, 3, 2};
  EXPECT_TRUE(is_equal_sets(my1, std1));

  s21::set<int> my2 = {1, 2, 3, 4, 5, 2, 3, 6, 1};
  std::set<int> std2 = {1, 2, 3, 4, 5, 2, 3, 6, 1};
  EXPECT_TRUE(is_equal_sets(my2, std2));

  s21::set<int> my3{};
  std::set<int> std3{};
  EXPECT_TRUE(is_equal_sets(my2, std2));
}

TEST(Set, Copy_Constructor) {
  s21::set<int> src1{8, 5, 3, 2};
  s21::set<int> res1(src1);
  std::set<int> src2{8, 5, 3, 2};
  std::set<int> res2(src2);
  EXPECT_TRUE(is_equal_sets(res1, res2));

  s21::set<int> src3{};
  s21::set<int> res3(src3);
  std::set<int> src4{};
  std::set<int> res4(src4);
  EXPECT_TRUE(is_equal_sets(res3, res4));

  s21::set<int> src5{1, 2, 3, 4, 5, 2, 3, 6, 1};
  s21::set<int> res5(src5);
  std::set<int> src6{1, 2, 3, 4, 5, 2, 3, 6, 1};
  std::set<int> res6(src6);
  EXPECT_TRUE(is_equal_sets(res5, res6));
}

TEST(Set, Move_Constructor) {
  s21::set<char> s3{'a', 'b', 'c', 'd', 'e'};
  s21::set<char> s1(std::move(s3));
  std::set<char> s4{'a', 'b', 'c', 'd', 'e'};
  std::set<char> s2(std::move(s4));
  EXPECT_TRUE(is_equal_sets(s1, s2));
  EXPECT_EQ(s3.empty(), true);
  EXPECT_EQ(s4.empty(), true);
}

//**********************CAPACITY**********************

TEST(Set, Empty) {
  s21::set<char> s21_s;
  std::set<char> std_s;

  EXPECT_EQ(s21_s.empty(), std_s.empty());
  EXPECT_EQ(s21_s.size(), 0);

  s21_s = {'a', 'b', 'c', 'd', 'e'};
  std_s = {'a', 'b', 'c', 'd', 'e'};

  EXPECT_EQ(s21_s.empty(), std_s.empty());
  EXPECT_EQ(s21_s.size(), 5);
}

TEST(Set, Max_size) {
  // s21::set<int> s21_s;
  // std::set<int> std_s;
  // EXPECT_EQ(s21_s.max_size(), std_s.max_size());

  // s21::set<std::string> s21_ss;
  // std::set<std::string> std_ss;
  // EXPECT_EQ(s21_ss.max_size(), std_ss.max_size());

  // s21::set<char> s21_sc;
  // std::set<char> std_sc;
  // EXPECT_EQ(s21_sc.max_size(), std_sc.max_size());
}

//**********************Iterator**********************
TEST(Set, Iterators) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6};

  auto it1 = s1.begin();
  auto it2 = s2.begin();
  EXPECT_EQ(*it1, 1);
  EXPECT_EQ(*it1, *it2);

  ++it1;
  ++it2;
  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it1, *it2);
}

//**********************MODIFIERS**********************
TEST(Set, Insert) {
  std::set<int> std1;
  s21::set<int> my1;

  EXPECT_EQ(std1.empty(), my1.empty());
  std1.insert(5);
  my1.insert(5);
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_TRUE(is_equal_sets(my1, std1));
  std1.insert(3);
  my1.insert(3);
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_TRUE(is_equal_sets(my1, std1));
  std1.insert(3);
  my1.insert(3);
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_EQ(std1.empty(), my1.empty());
  EXPECT_TRUE(is_equal_sets(my1, std1));
}

TEST(Set, Insert_detailed) {
  std::set<int> std1 = {1, 2, 3, 6, 8};
  s21::set<int> my1 = {1, 2, 3, 6, 8};

  std::pair<s21::set<int>::iterator, bool> insert1 = my1.insert(5);
  std::pair<std::set<int>::iterator, bool> insert2 = std1.insert(5);

  EXPECT_EQ(*insert1.first, *insert2.first);
  EXPECT_EQ(insert1.second, insert2.second);
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_EQ(std1.empty(), my1.empty());
  EXPECT_TRUE(is_equal_sets(my1, std1));

  std::pair<s21::set<int>::iterator, bool> insert3 = my1.insert(10);
  std::pair<std::set<int>::iterator, bool> insert4 = std1.insert(10);

  EXPECT_EQ(*insert3.first, *insert4.first);
  EXPECT_EQ(insert3.second, insert4.second);
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_EQ(std1.empty(), my1.empty());
  EXPECT_TRUE(is_equal_sets(my1, std1));

  std::pair<s21::set<int>::iterator, bool> insert5 = my1.insert(8);
  std::pair<std::set<int>::iterator, bool> insert6 = std1.insert(8);

  EXPECT_EQ(*insert5.first, *insert6.first);
  EXPECT_EQ(insert5.second, insert6.second);
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_EQ(std1.empty(), my1.empty());
  EXPECT_TRUE(is_equal_sets(my1, std1));

  std1.clear();
  my1.clear();
  EXPECT_EQ(std1.empty(), my1.empty());
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_EQ(my1.size(), 0);
}

TEST(Set, Erase) {
  std::set<int> std1 = {1, 2, 3, 6, 8};
  s21::set<int> my1 = {1, 2, 3, 6, 8};
  EXPECT_TRUE(is_equal_sets(my1, std1));
  std1.erase(6);
  my1.erase(my1.find(6));
  EXPECT_TRUE(is_equal_sets(my1, std1));
}

TEST(Set, Swap) {
  s21::set<int> mys1 = {1, 3, 5, 7, 9};
  s21::set<int> mys2 = {2, 4};

  std::set<int> stds1 = {1, 3, 5, 7, 9};
  std::set<int> stds2 = {2, 4};

  stds1.swap(stds2);
  mys1.swap(mys2);

  EXPECT_TRUE(is_equal_sets(mys1, stds1));
  EXPECT_TRUE(is_equal_sets(mys2, stds2));

  s21::set<int> myd1 = {1, 3, 5};
  s21::set<int> myd2 = {};

  std::set<int> stdd1 = {1, 3, 5};
  std::set<int> stdd2 = {};

  stdd1.swap(stdd2);
  myd1.swap(myd2);

  EXPECT_TRUE(is_equal_sets(myd1, stdd1));
  EXPECT_TRUE(is_equal_sets(myd2, stdd2));
}

TEST(Set, Merge) {
  std::set<int> std1 = {2, 4, 6};
  std::set<int> std2 = {1, 2, 1, 3, 9, 3, 6, 5, 7, 9};
  s21::set<int> my1 = {2, 4, 6};
  s21::set<int> my2 = {1, 2, 1, 3, 9, 3, 6, 5, 7, 9};

  std1.merge(std2);
  my1.merge(my2);

  EXPECT_TRUE(is_equal_sets(my1, std1));
  EXPECT_TRUE(is_equal_sets(my2, std2));
}

//**********************LOOKUP**********************
TEST(Set, Find) {
  std::set<int> stdset = {2, 4, 6, 8, 10, 12, 14, 16, 16, 22, 44, 66};
  s21::set<int> myset = {2, 4, 6, 8, 10, 12, 14, 16, 16, 22, 44, 66};
  auto it1 = stdset.find(16);
  auto it2 = myset.find(16);
  EXPECT_EQ(*it1, *it2);
  ++it1;
  ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(Set, Contains) {
  std::set<int> std1 = {1, 2, 3, 6, 8, 9};
  s21::set<int> my1 = {1, 2, 3, 6, 8, 9};
  EXPECT_TRUE(my1.contains(3));
  EXPECT_FALSE(my1.contains(5));
}

//**********************PART3**********************
TEST(Set, Insert_many) {
  std::set<int> s1;
  s21::set<int> s2;

  s1.insert({});
  s2.insert_many();
  EXPECT_TRUE(is_equal_sets(s2, s1));

  s1.insert({1, 2, 3});
  auto vector = s2.insert_many(1, 2, 3);
  EXPECT_TRUE(is_equal_sets(s2, s1));
  for (size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(*(vector[i].first), i + 1);
    EXPECT_EQ(vector[i].second, true);
  }

  s1.insert({1, 0, 3});
  vector = s2.insert_many(1, 0, 3);
  EXPECT_TRUE(is_equal_sets(s2, s1));
  EXPECT_EQ(*(vector[0].first), 1);
  EXPECT_EQ(vector[0].second, false);
  EXPECT_EQ(*(vector[1].first), 0);
  EXPECT_EQ(vector[1].second, true);
  EXPECT_EQ(*(vector[2].first), 3);
  EXPECT_EQ(vector[2].second, false);

  s1.insert({101});
  vector = s2.insert_many(101);
  EXPECT_TRUE(is_equal_sets(s2, s1));
  EXPECT_EQ(*(vector[0].first), 101);
  EXPECT_EQ(vector[0].second, true);

  s1.insert({7, 11, 23, 96, 3, 12, 1, -24, 88});
  s2.insert_many(7, 11, 23, 96, 3, 12, 1, -24, 88);
  EXPECT_TRUE(is_equal_sets(s2, s1));
}