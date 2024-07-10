#ifndef SRC_S21_CONTAINERS_S21_LIST_H_
#define SRC_S21_CONTAINERS_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node;
  class ListIterator;
  class ListConstIterator;

 public:
  // aliases
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // constructors / destructor
  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list &&other);
  ~list();

  // assignment
  list &operator=(const list &other);
  list &operator=(list &&other);

  // accessing
  const_reference front();
  const_reference back();

  // iterating
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  // capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // modifying
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void swap(list &other) noexcept;
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse() noexcept;
  void unique();
  void sort();

  // part 3
  template <typename... Args>
  iterator insert_many(const iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

  // Node Struct
 private:
  struct Node {
    // constructors
    Node() : next(this), prev(this), data(value_type()) {}
    explicit Node(value_type value)
        : next(nullptr), prev(nullptr), data(value) {}

    // methods
    void links_insert(Node *new_node) {
      new_node->next = this;
      new_node->prev = prev;
      prev->next = new_node;
      prev = new_node;
    }

    void links_erase() {
      next->prev = prev;
      prev->next = next;
      next = this;
      prev = this;
    }

    // fields
    Node *next;
    Node *prev;
    value_type data;
  };

  // Iterator Class
  class ListIterator {
   public:
    // constructor
    ListIterator() = default;
    explicit ListIterator(Node *node) noexcept : node(node) {}

    // operators overloading
    reference operator*() const { return node->data; }

    iterator &operator++() {
      node = node->next;
      return *this;
    }

    iterator &operator--() {
      node = node->prev;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(node);
      ++(*this);
      return tmp;
    }

    iterator operator--(int) {
      iterator tmp(node);
      --(*this);
      return tmp;
    }

    bool operator==(const iterator &it) const { return node == it.node; }

    bool operator!=(const iterator &it) const { return node != it.node; }

    // field
    Node *node;
  };

  // Const Iterator Class
  class ListConstIterator {
   public:
    // constructors
    ListConstIterator() = default;
    explicit ListConstIterator(const Node *node) : node(node) {}
    ListConstIterator(const iterator &it) : node(it.node) {}

    // operators overloading
    const_reference operator*() const { return node->data; }

    const_iterator &operator++() {
      node = node->next;
      return *this;
    }

    const_iterator &operator--() {
      node = node->prev;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp(node);
      ++(*this);
      return tmp;
    }

    const_iterator operator--(int) {
      const_iterator tmp(node);
      --(*this);
      return tmp;
    }

    bool operator==(const const_iterator &other) const {
      return node == other.node;
    }

    bool operator!=(const const_iterator &other) const {
      return node != other.node;
    }

    // field
    const Node *node;
  };

  // class fields
  Node *tail;
  size_type list_sz;
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // SRC_S21_CONTAINERS_S21_LIST_H_