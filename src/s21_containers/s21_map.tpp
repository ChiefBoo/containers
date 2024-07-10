#ifndef SRC_S21_CONTAINERS_S21_MAP_TPP_
#define SRC_S21_CONTAINERS_S21_MAP_TPP_

#include "s21_map.h"

namespace s21 {

template <typename Key, typename Val>
map<Key, Val>::map(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    tree.insert(item, false);
  }
}

template <typename Key, typename Val>
map<Key, Val>& map<Key, Val>::operator=(map&& m) noexcept {
  if (this != &m) {
    tree = m.tree;
  }
  return *this;
}

template <typename Key, typename Val>
Val& map<Key, Val>::at(const Key& key) {
  auto res = tree.find(key);
  if (res == end()) throw std::out_of_range("key not found");
  return (*res).second;
}

template <typename Key, typename Val>
Val& map<Key, Val>::operator[](const Key& key) {
  auto res = tree.insert(std::make_pair(key, Val()), false).first;
  return (*res).second;
}

template <typename Key, typename Val>
std::pair<typename map<Key, Val>::iterator, bool> map<Key, Val>::insert(
    const value_type& value) {
  return tree.insert(value, false);
}

template <typename Key, typename Val>
std::pair<typename map<Key, Val>::iterator, bool> map<Key, Val>::insert(
    const Key& key, const Val& obj) {
  return tree.insert(std::make_pair(key, obj), false);
}

template <typename Key, typename Val>
std::pair<typename map<Key, Val>::iterator, bool>
map<Key, Val>::insert_or_assign(const Key& key, const Val& obj) {
  auto res = tree.insert(std::make_pair(key, obj), false);
  if (!res.second) {
    (*res.first).second = obj;
  }
  return res;
}

template <typename Key, typename Val>
template <typename... Args>
vector<std::pair<typename map<Key, Val>::iterator, bool>>
map<Key, Val>::insert_many(Args&&... args) {
  vector<std::pair<iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_MAP_TPP_
