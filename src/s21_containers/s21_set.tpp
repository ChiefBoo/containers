#ifndef SRC_S21_CONTAINERS_S21_SET_TPP_
#define SRC_S21_CONTAINERS_S21_SET_TPP_

#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set(std::initializer_list<Key> const& items) {
  for (const auto& item : items) {
    tree.insert(std::make_pair(item, nullptr), false);
  }
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) noexcept {
  if (this != &s) {
    tree = s.tree;
  }
  return *this;
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  auto iter = tree.insert(std::make_pair(value, nullptr), false);
  return std::make_pair(Iterator(iter.first), iter.second);
}

template <typename Key>
template <typename... Args>
vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  vector<std::pair<iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_SET_TPP_
