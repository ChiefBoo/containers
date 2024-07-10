#include <map>

#include "s21_gtests.h"

template <typename Key, typename Val>
void print_maps(s21::map<Key, Val> &mymap, std::map<Key, Val> &stdmap) {
  std::cout << "\n\tTEST_MAP:PRINT\n\n";
  std::cout << "std::Map : " << std::endl;
  for (const auto &kv : stdmap) {
    std::cout << kv.first << ": " << kv.second << std::endl;
  }
  std::cout << "s21::Map :" << std::endl;
  for (const auto &kv : mymap) {
    std::cout << kv.first << ": " << kv.second << std::endl;
  }
  std::cout << '\n';
}

template <typename Key, typename Val>
bool is_equal_maps(s21::map<Key, Val> &mymap, std::map<Key, Val> &stdmap) {
  bool success = true;
  if (mymap.size() != stdmap.size()) success = false;
  auto it1 = mymap.begin();
  auto it2 = stdmap.begin();
  for (; it1 != mymap.end(); ++it1, ++it2) {
    if ((*it1).first != (*it2).first || (*it1).second != (*it2).second)
      success = false;
  }
  if (!success) print_maps(mymap, stdmap);
  return success;
}

//**********************CONSTRUCTORS**********************
TEST(map, Default_Constructor) {
  s21::map<int, int> s21_m;
  std::map<int, int> std_m;
  EXPECT_EQ(s21_m.empty(), std_m.empty());

  s21::map<int, std::string> s21_ms;
  std::map<int, std::string> std_ms;
  EXPECT_EQ(s21_ms.empty(), std_ms.empty());

  s21::map<int, double> s21_md;
  std::map<int, double> std_md;
  EXPECT_EQ(s21_md.empty(), std_md.empty());
}

TEST(map, Initial_Constructor) {
  s21::map<int, int> t1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> t2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_TRUE(is_equal_maps(t1, t2));

  s21::map<int, int> t7{{4, 4}, {3, 3}, {5, 5}, {1, 1}, {4, 4}, {4, 4}, {2, 2}};
  std::map<int, int> t8{{4, 4}, {3, 3}, {5, 5}, {1, 1}, {4, 4}, {4, 4}, {2, 2}};
  EXPECT_TRUE(is_equal_maps(t7, t8));

  s21::map<int, std::string> t3 = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> t4 = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_TRUE(is_equal_maps(t3, t4));

  s21::map<int, std::string> t5{
      {1, "one"}, {2, "two"}, {3, "three"}, {2, "two"}};
  std::map<int, std::string> t6{
      {1, "one"}, {2, "two"}, {3, "three"}, {2, "two"}};
  EXPECT_TRUE(is_equal_maps(t5, t6));
}

TEST(map, Copy_Constructor) {
  s21::map<int, int> src1{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {2, 2}, {1, 1}};
  std::map<int, int> src2{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {2, 2}, {1, 1}};
  s21::map<int, int> res1(src1);
  std::map<int, int> res2(src2);
  EXPECT_TRUE(is_equal_maps(res1, res2));

  std::map<int, std::string> src3 = {{6, "six"}, {7, "seven"}, {10, "ten"}};
  s21::map<int, std::string> src4 = {{6, "six"}, {7, "seven"}, {10, "ten"}};
  std::map<int, std::string> res3 = src3;
  s21::map<int, std::string> res4 = src4;
  EXPECT_TRUE(is_equal_maps(res4, res3));

  s21::map<int, int> src5 = {};
  s21::map<int, int> res5 = src5;
  std::map<int, int> res6;
  EXPECT_TRUE(is_equal_maps(res5, res6));
}

TEST(map, Move_Constructor) {
  s21::map<int, char> m1{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> m2{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  s21::map<int, char> m3(std::move(m1));
  std::map<int, char> m4(std::move(m2));

  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_TRUE(is_equal_maps(m3, m4));
}

// //**********************CAPACITY**********************

TEST(map, Empty) {
  s21::map<int, char> s21_s;
  std::map<int, char> std_s;

  EXPECT_EQ(s21_s.empty(), std_s.empty());
  EXPECT_EQ(s21_s.size(), 0);

  s21_s = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std_s = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};

  EXPECT_EQ(s21_s.empty(), std_s.empty());
  EXPECT_EQ(s21_s.size(), 5);
}

TEST(map, Max_size) {
  // s21::map<int, int> s21_s;
  // std::map<int, int> std_s;
  // EXPECT_EQ(s21_s.max_size(), std_s.max_size());

  // s21::map<int, std::string> s21_ss;
  // std::map<int, std::string> std_ss;
  // EXPECT_EQ(s21_ss.max_size(), std_ss.max_size());

  // s21::map<char, std::string> s21_sc;
  // std::map<char, std::string> std_sc;
  // EXPECT_EQ(s21_sc.max_size(), std_sc.max_size());
}

// //**********************Iterator**********************
TEST(map, Iterators) {
  s21::map<int, char> s1 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> s2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  EXPECT_EQ((*s1.begin()).first, (*s2.begin()).first);
  EXPECT_EQ((*s1.begin()).second, (*s2.begin()).second);

  auto it1 = s1.begin();
  auto it2 = s2.begin();
  ++it1;
  ++it2;
  EXPECT_EQ((*it1).first, (*it2).first);
  EXPECT_EQ((*it1).second, (*it2).second);
}

//**********************MODIFIERS**********************
TEST(map, Insert) {
  std::map<int, std::string> std1;
  s21::map<int, std::string> my1;

  EXPECT_EQ(std1.empty(), my1.empty());
  std1.insert({5, "five"});
  std1.insert({2, "two"});
  my1.insert({5, "five"});
  my1.insert({2, "two"});
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_TRUE(is_equal_maps(my1, std1));

  std1.insert({2, "two"});
  my1.insert({2, "two"});
  EXPECT_EQ(std1.empty(), my1.empty());
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_TRUE(is_equal_maps(my1, std1));

  std1.insert({6, "six"});
  my1.insert({6, "six"});
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_TRUE(is_equal_maps(my1, std1));

  std1.insert(std::make_pair(10, "ten"));
  my1.insert(std::make_pair(10, "ten"));
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_TRUE(is_equal_maps(my1, std1));

  my1.insert(11, "eleven");
  std1.insert({11, "eleven"});
  EXPECT_EQ(std1.size(), my1.size());
  EXPECT_TRUE(is_equal_maps(my1, std1));
}

TEST(map, Insert_detailed) {
  s21::map<int, int> t1{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> t2{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto [it1, inserted1] = t1.insert({6, 6});
  auto [it2, inserted2] = t2.insert({6, 6});
  EXPECT_TRUE(is_equal_maps(t1, t2));
  EXPECT_EQ((*it1).first, (*it2).first);
  EXPECT_EQ((*it1).second, (*it2).second);
  EXPECT_EQ(inserted1, true);
  EXPECT_EQ(inserted1, inserted2);

  auto [it3, inserted3] = t1.insert({1, 1});
  auto [it4, inserted4] = t2.insert({1, 1});
  EXPECT_TRUE(is_equal_maps(t1, t2));
  EXPECT_EQ((*it3).first, (*it4).first);
  EXPECT_EQ((*it3).second, (*it4).second);
  EXPECT_EQ(inserted3, false);
  EXPECT_EQ(inserted3, inserted4);
}

TEST(map, Insert_or_assign) {
  s21::map<int, std::string> t1{{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> t2{{1, "one"}, {2, "two"}, {3, "three"}};

  t1.insert_or_assign(6, "six");
  t2.insert_or_assign(6, "six");
  EXPECT_TRUE(is_equal_maps(t1, t2));
  t1.insert_or_assign(6, "new six");
  t2.insert_or_assign(6, "new six");
  EXPECT_TRUE(is_equal_maps(t1, t2));
}

TEST(map, Erase) {
  s21::map<int, int> t1{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> t2{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  t2.erase(t2.find(4));
  t1.erase(t1.find(4));
  EXPECT_TRUE(is_equal_maps(t1, t2));
  t1.clear();
  t2.clear();
  EXPECT_EQ(t1.empty(), t2.empty());
  EXPECT_TRUE(is_equal_maps(t1, t2));
}

TEST(map, Swap) {
  s21::map<int, char> my1{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  s21::map<int, char> my2;
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> std2;

  my1.swap(my2);
  std1.swap(std2);
  EXPECT_TRUE(is_equal_maps(my1, std1));
  EXPECT_TRUE(is_equal_maps(my2, std2));

  s21::map<int, int> my3{{1, 1}, {8, 8}};
  std::map<int, int> std3{{1, 1}, {8, 8}};
  s21::map<int, int> my4{{3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> std4{{3, 3}, {4, 4}, {5, 5}};

  my3.swap(my4);
  std3.swap(std4);
  EXPECT_TRUE(is_equal_maps(my3, std3));
  EXPECT_TRUE(is_equal_maps(my4, std4));
}

TEST(map, Merge) {
  s21::map<int, char> my1{{1, 'a'}, {4, 'd'}, {5, 'e'}};
  s21::map<int, char> my2{{2, 'b'}, {3, 'c'}};
  std::map<int, char> std1{{1, 'a'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> std2{{2, 'b'}, {3, 'c'}};

  my1.merge(my2);
  std1.merge(std2);
  EXPECT_TRUE(is_equal_maps(my1, std1));
  EXPECT_TRUE(is_equal_maps(my2, std2));

  s21::map<int, int> my3{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> my4{{2, 2}, {3, 3}, {8, 8}, {1, 1}};
  std::map<int, int> std3{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> std4{{2, 2}, {3, 3}, {8, 8}, {1, 1}};

  my3.merge(my4);
  std3.merge(std4);
  EXPECT_TRUE(is_equal_maps(my3, std3));
  EXPECT_TRUE(is_equal_maps(my4, std4));
}

// //**********************LOOKUP**********************

TEST(map, Contains) {
  s21::map<int, int> my1{{2, 2}, {3, 3}, {8, 8}, {1, 1}};
  EXPECT_TRUE(my1.contains(3));
  EXPECT_FALSE(my1.contains(5));
}

// //**********************ACCESS**********************

TEST(map, Accessor) {
  std::map<int, std::string> check{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> test;

  test[1] = "one";
  test[2] = "two";
  test[3] = "three";
  EXPECT_TRUE(is_equal_maps(test, check));
  test[2] = "ten";
  check[2] = "ten";
  EXPECT_TRUE(is_equal_maps(test, check));
}

TEST(map, At) {
  s21::map<int, char> my1{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};
  std::map<int, char> std1{{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};

  EXPECT_EQ(my1.at(4), 'd');
  EXPECT_EQ(my1.at(4), std1.at(4));
  EXPECT_EQ(my1.at(1), 'a');
  EXPECT_EQ(my1.at(1), std1.at(1));
  EXPECT_ANY_THROW(my1.at(11));
}

// //**********************PART 3**********************

TEST(map, Insert_many) {
  std::map<int, std::string> s1;
  s21::map<int, std::string> s2;

  s1.insert({});
  s2.insert_many();
  EXPECT_TRUE(is_equal_maps(s2, s1));

  s1.insert({{1, "one"}, {2, "two"}, {3, "three"}});
  auto vector =
      s2.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                     std::make_pair(3, "three"));
  EXPECT_TRUE(is_equal_maps(s2, s1));
  for (size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ((*vector[i].first).first, i + 1);
    EXPECT_EQ(vector[i].second, true);
  }

  s1.insert({{1, "one"}, {0, "zero"}, {3, "three"}});
  vector = s2.insert_many(std::make_pair(1, "one"), std::make_pair(0, "zero"),
                          std::make_pair(3, "three"));
  EXPECT_TRUE(is_equal_maps(s2, s1));
  EXPECT_EQ((*vector[0].first).first, 1);
  EXPECT_EQ(vector[0].second, false);
  EXPECT_EQ((*vector[1].first).first, 0);
  EXPECT_EQ(vector[1].second, true);
  EXPECT_EQ((*vector[2].first).first, 3);
  EXPECT_EQ(vector[2].second, false);

  s1.insert({{101, "five"}});
  vector = s2.insert_many(std::make_pair(101, "five"));
  EXPECT_TRUE(is_equal_maps(s2, s1));
  EXPECT_EQ((*vector[0].first).first, 101);
  EXPECT_EQ(vector[0].second, true);

  s1.insert({{7, "ne dva"},
             {11, "ne dva"},
             {23, "ne dva"},
             {96, "ne dva"},
             {3, "three"},
             {12, "ne dva"},
             {1, "one"},
             {-24, "ne dva"},
             {88, "ne dva"}});
  s2.insert_many(std::make_pair(7, "ne dva"), std::make_pair(11, "ne dva"),
                 std::make_pair(23, "ne dva"), std::make_pair(96, "ne dva"),
                 std::make_pair(3, "three"), std::make_pair(12, "ne dva"),
                 std::make_pair(1, "one"), std::make_pair(-24, "ne dva"),
                 std::make_pair(88, "ne dva"));
  EXPECT_TRUE(is_equal_maps(s2, s1));
}