#ifndef SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_
#define SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_

#include "../s21_containers/s21_avltree.h"
#include "../s21_containers/s21_set.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename set<Key>::iterator;
  using const_iterator = typename set<Key>::const_iterator;
  using size_type = typename AVLTree<Key, std::nullptr_t>::size_type;

  multiset() = default;
  multiset(std::initializer_list<Key> const& elements);
  multiset(const multiset& s) : tree(s.tree) {}
  multiset(multiset&& s) : tree(std::move(s.tree)) {}
  ~multiset() {}
  multiset& operator=(multiset&& other) noexcept;

  // iterators
  iterator begin() { return iterator(tree.begin()); }
  iterator end() { return iterator(tree.end()); }
  const_iterator cbegin() { return Constiterator(tree.cbegin()); }
  const_iterator cend() { return Constiterator(tree.cend()); }

  // Capacity
  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  // Modifiers
  void clear() { tree.clear(); }
  iterator insert(const value_type& value);
  void erase(iterator pos) { tree.erase(tree.find(*pos)); }
  void swap(multiset& other) { tree.swap(other.tree); }
  void merge(multiset& other) { tree.merge(other.tree, true); }

  // Lookup
  iterator find(const key_type& key) { return iterator(tree.find(key)); }
  bool contains(const key_type& key) { return tree.contains(key); }
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  size_type count(const Key& key);

  // Part 3
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  AVLTree<Key, std::nullptr_t> tree;
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif  // SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_