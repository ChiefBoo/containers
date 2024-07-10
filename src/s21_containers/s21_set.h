#ifndef SRC_S21_CONSTAINERS_S21_SET_H_
#define SRC_S21_CONSTAINERS_S21_SET_H_

#include "s21_avltree.h"

namespace s21 {

template <typename Key>
class set {
 private:
  AVLTree<Key, std::nullptr_t> tree;

 public:
  class Iterator;
  class ConstIterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;  // make
  using size_type = typename AVLTree<Key, std::nullptr_t>::size_type;

  class Iterator {
   public:
    explicit Iterator(typename AVLTree<Key, std::nullptr_t>::Iterator it)
        : it_(it) {}
    Iterator() = default;
    Iterator& operator++() {
      ++it_;
      return *this;
    }
    bool operator!=(const Iterator& other) const { return it_ != other.it_; }
    bool operator==(const Iterator& other) const { return it_ == other.it_; }
    const value_type operator*() const { return (*it_).first; }

   protected:
    typename AVLTree<Key, std::nullptr_t>::Iterator it_;
    friend class set;
  };

  class ConstIterator : public Iterator {
   public:
    using Iterator::Iterator;
    ConstIterator()
        : Iterator(typename AVLTree<Key, std::nullptr_t>::ConstIterator()) {}
    const_reference operator*() const { return Iterator::operator*(); };
    ConstIterator& operator++() {
      Iterator::operator++();
      return *this;
    }
  };

  // constructors
  set() = default;
  set(std::initializer_list<Key> const& items);
  set(const set& s) : tree(s.tree) {}
  set(set&& s) : tree(std::move(s.tree)) {}

  // destructor
  ~set() {}

  // assignment
  set& operator=(set&& s) noexcept;

  // iterators
  iterator begin() { return Iterator(tree.begin()); }
  iterator end() { return Iterator(tree.end()); }
  const_iterator cbegin() { return ConstIterator(tree.cbegin()); }
  const_iterator cend() { return ConstIterator(tree.cend()); }

  // Capacity
  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  // Modifiers
  void clear() { tree.clear(); }
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos) { tree.erase(tree.find(*pos)); }
  void swap(set& other) { tree.swap(other.tree); }
  void merge(set& other) { tree.merge(other.tree, false); }

  // Lookup
  iterator find(const key_type& key) { return Iterator(tree.find(key)); }
  bool contains(const key_type& key) { return tree.contains(key); }

  // part 3
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // SRC_S21_CONSTAINERS_S21_SET_H_