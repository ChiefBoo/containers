#ifndef SRC_S21_CONTAINERSPLUS_S21_MULTISET_TPP_
#define SRC_S21_CONTAINERSPLUS_S21_MULTISET_TPP_

namespace s21 {

template <typename Key>
multiset<Key>::multiset(std::initializer_list<Key> const& elements) {
  for (const auto& elem : elements) {
    tree.insert(std::make_pair(elem, nullptr), true);
  }
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& other) noexcept {
  if (this != &other) {
    tree = other.tree;
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  auto iter = tree.insert(std::make_pair(value, nullptr), true);
  return iterator(iter.first);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  auto iter = begin();
  while (iter != end() && *iter < key) {
    ++iter;
  }
  return iter;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  auto iter = lower_bound(key);
  while (iter != end() && *iter == key) {
    ++iter;
  }
  return iter;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  size_type n = 0;
  auto iter = lower_bound(key);
  while (iter != end() && *iter == key) {
    ++n;
    ++iter;
  }
  return n;
}

template <typename Key>
template <typename... Args>
vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  vector<std::pair<iterator, bool>> result;
  (result.push_back({insert(std::forward<Args>(args)), true}), ...);
  return result;
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERSPLUS_S21_MULTISET_TPP_