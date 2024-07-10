#include <gtest/gtest.h>

#include <list>

#include "s21_gtests.h"

template <typename value_type>
bool is_equal_lists(s21::list<value_type> l1, std::list<value_type> l2) {
  if (l1.size() != l2.size()) return false;
  auto it1 = l1.begin();
  auto it2 = l2.begin();
  for (; it1 != l1.end(); ++it1, ++it2) {
    if (*it1 != *it2) return false;
  }
  return true;
}

TEST(List, Default_Constructor) {
  s21::list<int> s21_l;
  std::list<int> std_l;
  EXPECT_EQ(s21_l.empty(), std_l.empty());

  s21::list<std::string> s21_ls;
  std::list<std::string> std_ls;
  EXPECT_EQ(s21_ls.empty(), std_ls.empty());

  s21::list<double> s21_ld;
  std::list<double> std_ld;
  EXPECT_EQ(s21_ld.empty(), std_ld.empty());
}

TEST(List, Size_Constructor) {
  s21::list<double> s21_d(10);
  std::list<double> std_d(10);

  EXPECT_EQ(s21_d.size(), std_d.size());
  EXPECT_EQ(s21_d.size(), 10);

  for (auto it = s21_d.begin(); it != s21_d.end(); ++it) {
    EXPECT_DOUBLE_EQ(it.node->data, 0.0);
  }

  s21::list<char> s21_l(10);
  std::list<char> std_l(10);

  EXPECT_EQ(s21_l.size(), std_l.size());
  EXPECT_EQ(s21_l.size(), 10);

  auto std_it = std_l.begin();
  for (auto s21_it : s21_l) {
    EXPECT_EQ(*std_it, s21_it);
    ++std_it;
  }
}

TEST(List, Initial_Constructor) {
  s21::list<int> ml = {8, 5, 3, 2};
  std::list<int> sl = {8, 5, 3, 2};

  EXPECT_EQ(ml.size(), sl.size());
  auto std_it = sl.begin();

  for (auto s21_it : ml) {
    EXPECT_EQ(*std_it, s21_it);
    ++std_it;
  }
}

TEST(List, Copy_Constructor) {
  s21::list<int> src = {8, 5, 3, 2};
  s21::list<int> res = src;

  EXPECT_EQ(src.size(), res.size());
  auto src_it = src.begin();

  for (auto res_it : res) {
    EXPECT_EQ(*src_it, res_it);
    ++src_it;
  }
}

TEST(List, Move_Constructor) {
  s21::list<int> l3{1, 2, 3, 4, 5};
  s21::list<int> l1(std::move(l3));
  std::list<int> l4{1, 2, 3, 4, 5};
  std::list<int> l2(std::move(l4));
  auto it = l2.begin();
  for (auto s21_it : l1) {
    EXPECT_EQ(s21_it, *it);
    ++it;
  }
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l3.empty(), true);
  EXPECT_EQ(l4.empty(), true);
}

TEST(List, Accessing) {
  s21::list<int> s21_l{1, -22, 13, 44};
  std::list<int> std_l{1, -22, 13, 44};

  EXPECT_EQ(s21_l.front(), std_l.front());
  EXPECT_EQ(s21_l.back(), std_l.back());
}

TEST(List, CopyConstructor) {
  s21::list<int> origin({5, 4, 3, 2, 1});
  s21::list<int> cp(origin);

  EXPECT_EQ(origin.size(), cp.size());

  auto origin_iter = origin.begin();
  auto copy_iter = cp.begin();
  EXPECT_NE(origin_iter, copy_iter);
  for (; origin_iter != origin.end(); ++origin_iter, ++copy_iter) {
    EXPECT_EQ(*origin_iter, *copy_iter);
  }

  for (auto iter = cp.begin(); iter != cp.end(); ++iter) {
    *iter = 6;
  }

  for (auto iter = cp.begin(); iter != cp.end(); ++iter) {
    EXPECT_EQ(*iter, 6);
  }

  origin_iter = std::move(origin.begin());
  for (size_t i = 5; i > 0; --i, ++origin_iter) {
    EXPECT_EQ(i, *origin_iter);
  }
}

TEST(List, MoveConstructor) {
  s21::list<double> origin({1.1, 2.2, 3.3, 4.4, 5.5});
  s21::list<double> moved(std::move(origin));

  EXPECT_EQ(5, moved.size());
  EXPECT_EQ(0, origin.size());

  auto i = 1;
  for (auto iter = moved.begin(); iter != moved.end(); ++iter, ++i) {
    EXPECT_DOUBLE_EQ(i * 1.1, *iter);
  }
}

TEST(List, Copy_Assignment) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy;
  our_copy = our_list;
  std::list<int> std_copy;
  std_copy = std_list;
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(List, Move_Assignment) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Capacity_size) {
  s21::list<char> s21_l = {'a', 'b', 'c', 'd', 'e'};
  std::list<char> std_l = {'a', 'b', 'c', 'd', 'e'};

  EXPECT_EQ(s21_l.size(), std_l.size());
  EXPECT_EQ(s21_l.size(), 5);
}

TEST(List, Capacity_empty) {
  s21::list<char> s21_l;
  std::list<char> std_l;

  EXPECT_EQ(s21_l.empty(), std_l.empty());
  EXPECT_EQ(s21_l.size(), 0);

  s21_l = {'a', 'b', 'c', 'd', 'e'};
  std_l = {'a', 'b', 'c', 'd', 'e'};

  EXPECT_EQ(s21_l.empty(), std_l.empty());
  EXPECT_EQ(s21_l.size(), 5);
}

TEST(List, Capacity_max_size) {
  s21::list<int> s21_l;
  std::list<int> std_l;

  EXPECT_EQ(s21_l.max_size(), std_l.max_size());

  s21::list<std::string> s21_ls;
  std::list<std::string> std_ls;

  EXPECT_EQ(s21_ls.max_size(), std_ls.max_size());

  s21::list<char> s21_lc;
  std::list<char> std_lc;

  EXPECT_EQ(s21_lc.max_size(), std_lc.max_size());
}

TEST(List, Clear) {
  s21::list<std::string> s21_l = {"zhyzha", "ploho", "sebya vedet!"};
  std::list<std::string> std_l = {"zhyzha", "ploho", "sebya vedet!"};

  EXPECT_EQ(s21_l.empty(), std_l.empty());
  EXPECT_EQ(s21_l.size(), std_l.size());

  s21_l.clear();
  std_l.clear();

  EXPECT_EQ(s21_l.empty(), std_l.empty());
  EXPECT_EQ(s21_l.size(), std_l.size());
}

TEST(List, Iterators) {
  s21::list<int> l1 = {1, 2, 3, 4, 5, 6};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6};

  auto it1 = l1.begin();
  EXPECT_EQ(*it1, 1);
  ++it1;
  EXPECT_EQ(*it1, 2);

  auto it2 = l2.begin();
  it2++;
  EXPECT_EQ(*it1, *it2);

  auto it3 = l1.begin();
  --it1;
  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(it1 == it3, 1);
  EXPECT_EQ(it1 != it2, 1);
}

TEST(List, Insert) {
  s21::list<int> s21_l1 = {'a', 'c', 'd'};
  s21::list<int> s21_l2 = {'a', 'b', 'c', 'd'};

  auto it = s21_l1.begin();
  ++it;
  s21_l1.insert(it, 'b');
  auto it1 = s21_l1.begin();
  auto it2 = s21_l2.begin();
  while (it1 != s21_l1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_l1.size(), s21_l2.size());
}

TEST(List, Insert_2) {
  s21::list<int> l1 = {1, 2, 3, 4, 5, 6};
  std::list<int> l2 = {1, 2, 3, 4, 5, 6};
  auto it1 = l1.begin();
  auto it2 = l2.begin();
  l1.insert(++it1, 10);
  l2.insert(++it2, 10);
  EXPECT_EQ(is_equal_lists(l1, l2), 1);
  l1.insert(l1.end(), 2);
  l2.insert(l2.end(), 2);
  EXPECT_EQ(is_equal_lists(l1, l2), 1);
}

TEST(List, Erase) {
  s21::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(l1.front(), l2.front());
  l1.erase(l1.begin());
  l2.erase(l2.begin());
  EXPECT_EQ(is_equal_lists(l1, l2), 1);
  EXPECT_EQ(l1.front(), l2.front());
  l1.erase(--l1.end());
  l2.erase(--l2.end());
  EXPECT_EQ(is_equal_lists(l1, l2), 1);
  EXPECT_EQ(l1.front(), l2.front());
}

TEST(List, Erase1) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Push_Back) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  std::list<int> l2 = {1, 2, 3, 4, 5};
  l1.push_back(10);
  l2.push_back(10);
  ASSERT_EQ(is_equal_lists(l1, l2), 1);
  EXPECT_EQ(l1.back(), l2.back());
}

TEST(List, Pop_Back) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  std::list<int> l2 = {1, 2, 3, 4, 5};
  l1.pop_back();
  l2.pop_back();
  ASSERT_EQ(is_equal_lists(l1, l2), 1);
  EXPECT_EQ(l1.back(), l2.back());
}

TEST(List, Push_Front) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  std::list<int> l2 = {1, 2, 3, 4, 5};
  l1.push_front(10);
  l2.push_front(10);
  ASSERT_EQ(is_equal_lists(l1, l2), 1);
  EXPECT_EQ(l1.front(), l2.front());
}

TEST(List, Pop_Front) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  std::list<int> l2 = {1, 2, 3, 4, 5};
  l1.pop_front();
  l2.pop_front();
  ASSERT_EQ(is_equal_lists(l1, l2), 1);
  EXPECT_EQ(l1.front(), l2.front());
}

TEST(List, Swap_1) {
  s21::list<int> l1 = {11, 45, 30};
  s21::list<int> l2 = {};
  std::list<int> l3 = {11, 45, 30};
  std::list<int> l4 = {};
  l1.swap(l2);
  l3.swap(l4);
  ASSERT_EQ(is_equal_lists(l1, l3), true);
  ASSERT_EQ(is_equal_lists(l2, l4), true);
}

TEST(List, Swap_2) {
  s21::list<int> l1 = {1, 2, 3};
  s21::list<int> l2 = {4, 5, 6};
  std::list<int> l3 = {1, 2, 3};
  std::list<int> l4 = {4, 5, 6};
  l1.swap(l2);
  l3.swap(l4);
  ASSERT_EQ(is_equal_lists(l1, l3), true);
  ASSERT_EQ(is_equal_lists(l2, l4), true);
}

TEST(List, Swap_3) {
  s21::list<int> l1 = {111, 27, 3};
  s21::list<int> l2 = {46, 51, 6, 128, 40};
  std::list<int> l3 = {111, 27, 3};
  std::list<int> l4 = {46, 51, 6, 128, 40};
  l1.swap(l2);
  l3.swap(l4);
  ASSERT_EQ(is_equal_lists(l1, l3), true);
  ASSERT_EQ(is_equal_lists(l2, l4), true);
}

TEST(List, Merge_sorted) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  std::list<int> l2 = {1, 2, 3, 4, 5};
  s21::list<int> l3 = {6, 7, 8, 9, 10};
  std::list<int> l4 = {6, 7, 8, 9, 10};
  l1.merge(l3);
  l2.merge(l4);
  ASSERT_EQ(is_equal_lists(l1, l2), true);
  ASSERT_EQ(is_equal_lists(l3, l4), true);
  EXPECT_EQ(l3.empty(), true);
}

TEST(List, Merge_unsorted) {
  s21::list<int> l1 = {11, 52, 33, 48, 15};
  s21::list<int> l2 = {-91, 32, 33, 40, 18};
  std::list<int> l3 = {11, 52, 33, 48, 15};
  std::list<int> l4 = {-91, 32, 33, 40, 18};
  l1.merge(l2);
  l3.merge(l4);
  ASSERT_EQ(is_equal_lists(l1, l3), true);
  ASSERT_EQ(is_equal_lists(l2, l4), true);
  EXPECT_EQ(l2.empty(), true);
}

TEST(List, Splice_1) {
  s21::list<int> l1 = {11, 52, 33, 48, 15};
  s21::list<int> l2 = {-91, 32, 33, 40, 18};
  std::list<int> l3 = {11, 52, 33, 48, 15};
  std::list<int> l4 = {-91, 32, 33, 40, 18};
  l1.splice(l1.begin(), l2);
  l3.splice(l3.begin(), l4);
  ASSERT_EQ(is_equal_lists(l1, l3), true);
  ASSERT_EQ(is_equal_lists(l2, l4), true);
  EXPECT_EQ(l2.empty(), true);
}

TEST(List, Splice_2) {
  s21::list<int> l1 = {11, 52, 33, 48, 15};
  std::list<int> l2 = {11, 52, 33, 48, 15};
  s21::list<int> l3 = {-91, 32, 33, 40, 18};
  std::list<int> l4 = {-91, 32, 33, 40, 18};
  l1.splice(--l1.end(), l3);
  l2.splice(--l2.end(), l4);
  ASSERT_EQ(is_equal_lists(l1, l2), true);
  ASSERT_EQ(is_equal_lists(l3, l4), true);
  EXPECT_EQ(l3.empty(), true);
}

TEST(List, Unique_1) {
  s21::list<int> l1 = {1, 2, 2, 3, 3, 1, 23, 44, 4, 4, 5, 1, 1};
  std::list<int> l2 = {1, 2, 2, 3, 3, 1, 23, 44, 4, 4, 5, 1, 1};
  l1.unique();
  l2.unique();
  ASSERT_EQ(is_equal_lists(l1, l2), true);
}

TEST(List, Unique_2) {
  s21::list<int> l1 = {1};
  std::list<int> l2 = {1};
  l1.unique();
  l2.unique();
  ASSERT_EQ(is_equal_lists(l1, l2), true);
}

TEST(List, Sort_1) {
  s21::list<int> l1 = {81, 22, -3, 1, 14};
  std::list<int> l2 = {81, 22, -3, 1, 14};
  l1.sort();
  l2.sort();
  ASSERT_EQ(is_equal_lists(l1, l2), true);
}

TEST(List, Sort_2) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  std::list<int> l2 = {1, 2, 3, 4, 5};
  l1.sort();
  l2.sort();
  ASSERT_EQ(is_equal_lists(l1, l2), true);
}

TEST(List, SORT_TYPE_STRING) {
  s21::list<std::string> L1 = {"abcd", "abcdef", "abc"};
  std::list<std::string> L2 = {"abcd", "abcdef", "abc"};
  L1.sort();
  L2.sort();
  s21::list<std::string>::iterator it_L1 = L1.begin();
  std::list<std::string>::iterator it_L2 = L2.begin();
  for (; it_L2 != L2.end(); ++it_L2, ++it_L1) {
    ASSERT_EQ(*it_L1, *it_L2);
  }
}

TEST(List, Reverse_1) {
  s21::list<int> l1 = {1, 2, 3, 4, 5};
  std::list<int> l2 = {1, 2, 3, 4, 5};
  l1.reverse();
  l2.reverse();
  ASSERT_EQ(is_equal_lists(l1, l2), true);
}

TEST(List, Reverse_2) {
  s21::list<int> l1 = {1};
  std::list<int> l2 = {1};
  l1.reverse();
  l2.reverse();
  ASSERT_EQ(is_equal_lists(l1, l2), true);
}

TEST(List, Reverse_3) {
  s21::list<int> l1 = {};
  std::list<int> l2 = {};
  l1.reverse();
  l2.reverse();
  ASSERT_EQ(is_equal_lists(l1, l2), true);
}

TEST(List, const_it) {
  s21::list<int> L1 = {1, 2, 3};
  std::list<int> L2 = {1, 2, 3};
  s21::list<int>::const_iterator it_L1 = L1.begin();
  std::list<int>::const_iterator it_L2 = L2.begin();
  ASSERT_EQ(*it_L1, *it_L2);
}

TEST(List, Assignment_copy2) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4 = {4, 5, 6};
  L1 = L2;
  L3 = L4;
  ASSERT_EQ(is_equal_lists(L1, L3), true);
  ASSERT_EQ(is_equal_lists(L2, L4), true);
}

TEST(List, Assignment_move2) {
  s21::list<int> L1 = {1, 2, 3};
  s21::list<int> L2 = {4, 5, 6};
  std::list<int> L3 = {1, 2, 3};
  std::list<int> L4 = {4, 5, 6};
  L1 = std::move(L2);
  L3 = std::move(L4);
  ASSERT_EQ(is_equal_lists(L1, L3), true);
  ASSERT_EQ(is_equal_lists(L2, L4), true);
}

TEST(List, Insert_many) {
  std::list<int> std1 = {1, 2, 3, 4};
  s21::list<int> my1 = {1, 2, 3, 4};
  auto its = std1.insert(std1.begin(), {11, 22, 33});
  auto itm = my1.insert_many(my1.begin(), 11, 22, 33);
  EXPECT_EQ(*its, *itm);
  EXPECT_TRUE(is_equal_lists(my1, std1));

  its = std1.insert(std1.end(), {44, 55, 66});
  itm = my1.insert_many(my1.end(), 44, 55, 66);
  EXPECT_EQ(*its, *itm);
  EXPECT_TRUE(is_equal_lists(my1, std1));

  auto it1 = ++std1.begin();
  auto it2 = ++my1.begin();
  ++it1;
  ++it2;
  its = std1.insert(it1, {101, 202, 303});
  itm = my1.insert_many(it2, 101, 202, 303);
  EXPECT_EQ(*its, *itm);
  EXPECT_TRUE(is_equal_lists(my1, std1));

  std::list<int> std2;
  s21::list<int> my2;

  auto iter1 = std2.insert(std2.begin(), {});
  auto iter2 = my2.insert_many(my2.begin());
  EXPECT_EQ(*iter1, *iter2);
  EXPECT_TRUE(is_equal_lists(my2, std2));

  iter1 = std2.insert(std2.begin(), {6, 11, 23, -4, 55, 9, 101});
  iter2 = my2.insert_many(my2.begin(), 6, 11, 23, -4, 55, 9, 101);
  EXPECT_EQ(*iter1, *iter2);
  EXPECT_TRUE(is_equal_lists(my2, std2));

  iter1 = std2.insert(std2.begin(), {});
  iter2 = my2.insert_many(my2.begin());
  EXPECT_EQ(*iter1, *iter2);
  EXPECT_TRUE(is_equal_lists(my2, std2));

  iter1 = std2.insert(std2.end(), {2024});
  iter2 = my2.insert_many(my2.end(), 2024);
  EXPECT_EQ(*iter1, *iter2);
  EXPECT_TRUE(is_equal_lists(my2, std2));
}

TEST(List, Insert_many_back) {
  std::list<int> std1;
  s21::list<int> my1;

  std1.insert(std1.end(), {1, 2, 3});
  my1.insert_many_back(1, 2, 3);
  EXPECT_TRUE(is_equal_lists(my1, std1));

  std1.insert(std1.end(), {11});
  my1.insert_many_back(11);
  EXPECT_TRUE(is_equal_lists(my1, std1));

  std1.insert(std1.end(), {});
  my1.insert_many_back();
  EXPECT_TRUE(is_equal_lists(my1, std1));

  std1.insert(std1.end(), {-1, -2, -1, -4, -2, -11, -11});
  my1.insert_many_back(-1, -2, -1, -4, -2, -11, -11);
  EXPECT_TRUE(is_equal_lists(my1, std1));
}

TEST(List, Insert_many_front) {
  std::list<int> std1;
  s21::list<int> my1;

  std1.insert(std1.begin(), {1, 2, 3});
  my1.insert_many_front(1, 2, 3);
  EXPECT_TRUE(is_equal_lists(my1, std1));

  std1.insert(std1.begin(), {11});
  my1.insert_many_front(11);
  EXPECT_TRUE(is_equal_lists(my1, std1));

  std1.insert(std1.begin(), {});
  my1.insert_many_front();
  EXPECT_TRUE(is_equal_lists(my1, std1));

  std1.insert(std1.begin(), {-1, -2, -1, -4, -2, -11, -11});
  my1.insert_many_front(-1, -2, -1, -4, -2, -11, -11);
  EXPECT_TRUE(is_equal_lists(my1, std1));
}