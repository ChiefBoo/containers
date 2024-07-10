#include <vector>

#include "s21_gtests.h"

template <typename value_type>
bool is_equal_vector(s21::vector<value_type>& v1, std::vector<value_type>& v2) {
  if (v1.size() != v2.size()) return false;
  for (size_t i = 0; i < v1.size(); ++i) {
    if (v1[i] != v2[i]) return false;
  }
  return true;
}

TEST(Vector, Constructor_Default) {
  s21::vector<int> v1;
  std::vector<int> v2;
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(is_equal_vector(v1, v2), 1);
}

TEST(Vector, Constructor_Size) {
  s21::vector<int> v1(5);
  std::vector<int> v2(5);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(is_equal_vector(v1, v2), 1);
}

TEST(Vector, Constructor_Parametrized) {
  s21::vector<int> v1(77);
  std::vector<int> v2(77);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(is_equal_vector(v1, v2), 1);
}

TEST(Vector, Constructor_Initialized) {
  s21::vector<int> v1 = {1, 4, 5, 7};
  std::vector<int> v2 = {1, 4, 5, 7};
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(is_equal_vector(v1, v2), 1);
}

TEST(Vector, Constructor_Copy) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> c1 = v1;
  std::vector<int> v2{1, 2, 3};
  std::vector<int> c2 = v2;
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(is_equal_vector(v1, v2), 1);
}

TEST(Vector, Constructor_Move) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v1_moved(std::move(v1));
  std::vector<int> v2{1, 2, 3};
  std::vector<int> v2_moved(std::move(v2));
  EXPECT_TRUE(is_equal_vector(v1_moved, v2_moved));
}

TEST(Vector, MoveAssignment) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v1_moved;
  v1_moved = std::move(v1);
  std::vector<int> v2{1, 2, 3};
  std::vector<int> v2_moved;
  v2_moved = std::move(v2);
  EXPECT_TRUE(is_equal_vector(v1_moved, v2_moved));
}

TEST(Vector, At_1) {
  s21::vector<double> v1{1123, 902, 33};
  std::vector<double> v2{1123, 902, 33};
  EXPECT_TRUE(is_equal_vector(v1, v2));
}

TEST(Vector, At_2) {
  s21::vector<int> v1{1, 2, 3};
  EXPECT_EQ(v1.at(0), 1);
  EXPECT_EQ(v1.at(1), 2);
  EXPECT_EQ(v1.at(2), 3);
}

TEST(Vector, At_3) {
  s21::vector<int> v1{1, 2, 3};
  EXPECT_THROW(v1.at(3), std::out_of_range);
}

TEST(Vector, Front_Back_1) {
  s21::vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  EXPECT_EQ(v1.front(), v2.front());
  EXPECT_EQ(v1.back(), v2.back());
}

TEST(Vector, Front_Back_2) {
  s21::vector<int> v1{1, 2, 3};
  EXPECT_EQ(v1.front(), 1);
  EXPECT_EQ(v1.back(), 3);
}

TEST(Vector, Data) {
  s21::vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  EXPECT_EQ(*v1.data(), *v2.data());
  int* ar1 = v1.data();
  int* ar2 = v2.data();
  EXPECT_EQ(ar1[1], ar2[1]);
}

TEST(Vector, Empty_1) {
  s21::vector<int> v1;
  std::vector<int> v2;
  EXPECT_EQ(v1.empty(), v2.empty());
}

TEST(Vector, Empty_2) {
  s21::vector<int> v1{1, 2, 3};
  EXPECT_FALSE(v1.empty());
}

TEST(Vector, Size) {
  s21::vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.size(), 3);
}

TEST(Vector, MaxSize) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5, 6, 8, 9, 11, 1, 1, 88};
  std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 8, 9, 11, 1, 1, 88};
  EXPECT_EQ(v1.max_size(), v2.max_size());

  s21::vector<int> v3;
  EXPECT_GT(v3.max_size(), 0);
}

TEST(Vector, Capacity) {
  s21::vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};
  v1.reserve(100);
  v2.reserve(100);
  EXPECT_EQ(v1.capacity(), v2.capacity());
  EXPECT_EQ(v1.capacity(), 100);
}

TEST(Vector, Shrink_to_fit) {
  s21::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> v2{1, 2, 3, 4, 5};
  v1.reserve(80);
  v2.reserve(80);
  EXPECT_EQ(v1.capacity(), v2.capacity());
  EXPECT_EQ(v1.capacity(), 80);
  EXPECT_EQ(v1.size(), v2.size());
  v1.shrink_to_fit();
  v2.shrink_to_fit();
  EXPECT_EQ(v1.capacity(), v2.capacity());
  EXPECT_EQ(v1.capacity(), 5);
  EXPECT_EQ(v1.size(), v2.size());
}

TEST(Vector, Clear) {
  s21::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> v2{1, 2, 3, 4, 5};
  v1.clear();
  v2.clear();
  EXPECT_EQ(is_equal_vector(v1, v2), 1);
  EXPECT_TRUE(v1.empty());
}

TEST(Vector, Push_Pop_Back) {
  s21::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> v2{1, 2, 3, 4, 5};
  v1.push_back(9);
  v2.push_back(9);
  EXPECT_TRUE(is_equal_vector(v1, v2));
  v1.pop_back();
  v2.pop_back();
  EXPECT_TRUE(is_equal_vector(v1, v2));
}

TEST(Vector, Swap) {
  s21::vector<char> v1 = {'c', 'h', 'i', 'v', 'o'};
  s21::vector<char> v1_swap = {'n', 'n', 'a', 'd', 'a'};
  std::vector<char> v2 = {'c', 'h', 'i', 'v', 'o'};
  std::vector<char> v2_swap = {'n', 'n', 'a', 'd', 'a'};
  v1.swap(v1_swap);
  v2.swap(v2_swap);

  EXPECT_TRUE(is_equal_vector(v1, v2));
  EXPECT_TRUE(is_equal_vector(v1_swap, v2_swap));
}

TEST(Vector, Iterator_1) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  s21::vector<int>::iterator it = v.begin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
}

TEST(Vector, Iterator_2) {
  s21::vector<int> v{1, 2, 3};
  s21::vector<int>::iterator it1 = v.begin();
  s21::vector<int>::iterator it2 = v.begin();
  EXPECT_TRUE(it1 == it2);
  ++it1;
  EXPECT_TRUE(it1 != it2);
}

TEST(Vector, cosnt_Iterator_1) {
  const s21::vector<int> v{1, 2, 3, 4, 5};
  s21::vector<int>::const_iterator it = v.cbegin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  s21::vector<int>::const_iterator ite = v.cend();
  --ite;
  EXPECT_EQ(*ite, 5);
}

TEST(Vector, const_Iterator_2) {
  const s21::vector<int> v{1, 2, 3};
  s21::vector<int>::const_iterator it1 = v.cbegin();
  s21::vector<int>::const_iterator it2 = v.cbegin();
  EXPECT_TRUE(it1 == it2);
  ++it1;
  EXPECT_TRUE(it1 != it2);
}

TEST(Vector, const_Iterator_3) {
  const s21::vector<int> v{1, 2, 3};

  s21::vector<int>::const_iterator it = v.cbegin();
  s21::vector<int>::const_iterator result = it + 2;
  EXPECT_EQ(*result, 3);
}

TEST(Vector, Bracket) {
  s21::vector<int> v;
  EXPECT_THROW(v[0], std::out_of_range);
  EXPECT_THROW(v[5], std::out_of_range);

  v.push_back(42);
  EXPECT_NO_THROW(v[0]);
  EXPECT_THROW(v[1], std::out_of_range);
}

TEST(Vector, Insert_Throw) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_NO_THROW(v.insert(v.begin() + 1, 42));
  EXPECT_THROW(v.insert(v.begin() + 5, 42), std::out_of_range);
}

TEST(Vector, Erase_Throw) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_NO_THROW(v.erase(v.begin() + 1));
  EXPECT_THROW(v.erase(v.begin() + 5), std::out_of_range);
}

TEST(Vector, Reserve_IncreaseCapacity) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(Vector, Reserve_DecreaseCapacity) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity - 2;
  v.reserve(newCapacity);
  EXPECT_LE(v.capacity(), initialCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(Vector, Insert_many) {
  std::vector<int> std1 = {1, 3, 5, 6};
  s21::vector<int> my1 = {1, 3, 5, 6};

  auto its1 = std1.insert(std1.begin(), {});
  auto itm1 = my1.insert_many(my1.begin());
  EXPECT_TRUE(is_equal_vector(my1, std1));
  EXPECT_EQ(*its1, *itm1);

  auto its2 = std1.insert(std1.begin(), {11});
  auto itm2 = my1.insert_many(my1.begin(), 11);
  EXPECT_TRUE(is_equal_vector(my1, std1));
  EXPECT_EQ(*its2, *itm2);

  auto its3 = std1.insert(std1.end(), {22, 33, 44});
  auto itm3 = my1.insert_many(my1.end(), 22, 33, 44);
  EXPECT_TRUE(is_equal_vector(my1, std1));
  EXPECT_EQ(*its3, *itm3);

  auto its4 = std1.insert((std1.begin() + 3), {505, 606, 707, 808, 909});
  auto itm4 = my1.insert_many((my1.begin() + 3), 505, 606, 707, 808, 909);
  EXPECT_TRUE(is_equal_vector(my1, std1));
  EXPECT_EQ(*its4, *itm4);

  std::vector<int> std2 = {};
  s21::vector<int> my2 = {};

  auto its5 = std2.insert(std2.begin(), {505, 606, 707, 808, 909});
  auto itm5 = my2.insert_many(my2.begin(), 505, 606, 707, 808, 909);
  EXPECT_TRUE(is_equal_vector(my2, std2));
  EXPECT_EQ(*its5, *itm5);
}

TEST(Vector, Insert_many_back) {
  s21::vector<int> my1 = {};
  std::vector<int> check1 = {1, 3, 5, 6};

  my1.insert_many_back(1, 3, 5, 6);
  EXPECT_TRUE(is_equal_vector(my1, check1));

  my1.insert_many_back();
  EXPECT_TRUE(is_equal_vector(my1, check1));

  my1.insert_many_back(11);
  check1.push_back(11);
  EXPECT_TRUE(is_equal_vector(my1, check1));

  my1.insert_many_back(101, 202, 303, 404, 505);
  std::vector<int> check2 = {1, 3, 5, 6, 11, 101, 202, 303, 404, 505};
  EXPECT_TRUE(is_equal_vector(my1, check2));
}
