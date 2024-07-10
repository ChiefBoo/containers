#ifndef SRC_S21_CONTAINERS_S21_MAP_H_
#define SRC_S21_CONTAINERS_S21_MAP_H_

#include "s21_avltree.h"

namespace s21 {

template <typename Key, typename Val>
class map {
 private:
  AVLTree<Key, Val> tree;

 public:
  using key_type = Key;
  using mapped_type = Val;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename AVLTree<Key, Val>::iterator;
  using const_iterator = typename AVLTree<Key, Val>::const_iterator;
  using size_type = typename AVLTree<Key, Val>::size_type;

  // constructors
  map() = default;
  map(std::initializer_list<value_type> const& items);
  map(const map& m) : tree(m.tree) {}
  map(map&& m) : tree(std::move(m.tree)) {}

  // destructor
  ~map() = default;

  // assignment
  map& operator=(map&& m) noexcept;

  // element access
  Val& at(const Key& key);
  Val& operator[](const Key& key);

  // iterators
  iterator begin() { return tree.begin(); }
  iterator end() { return tree.end(); }
  const_iterator cbegin() { return tree.cbegin(); }
  const_iterator cend() { return tree.cend(); }

  // Capacity
  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  // Modifiers
  void clear() { tree.clear(); }
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const Val& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const Val& obj);
  void erase(iterator pos) { tree.erase(pos); }
  void swap(map& other) { tree.swap(other.tree); }
  void merge(map& other) { tree.merge(other.tree, false); }

  // Lookup
  bool contains(const key_type& key) { return tree.contains(key); }

  // extra methods
  iterator find(const key_type& key) { return tree.find(key); }

  // part 3
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

}  // namespace s21

#include "s21_map.tpp"

#endif  // SRC_S21_CONTAINERS_S21_MAP_H_
