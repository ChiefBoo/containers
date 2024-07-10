#ifndef SRC_S21_CONTAINERS_S21_AVLTREE_H_
#define SRC_S21_CONTAINERS_S21_AVLTREE_H_

#include <algorithm>
#include <cstddef>
#include <limits>
#include <utility>

namespace s21 {

template <typename Key, typename Value>
class AVLTree {
 private:
  struct Node {
    std::pair<Key, Value> data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    Node(const Key& k, const Value& v)
        : data(k, v),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          height(1) {}
    Node(const Key& k, const Value& v, Node* l = nullptr, Node* r = nullptr,
         Node* p = nullptr, int h = 1)
        : data(k, v), left(l), right(r), parent(p), height(h) {}
    Node& operator=(const Node& other) {
      if (this != &other) {
        this->data = other.data;
        this->left = other.left;
        this->right = other.right;
        this->parent = other.parent;
        this->height = other.height;
      }
      return *this;
    }
    Node()
        : data(), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
  };

  Node* root;

  // helper methods
  int height(Node* node);
  int balance_factor(Node* node);
  Node* rotate_right(Node* y);
  Node* rotate_left(Node* x);
  Node* balance(Node* node);
  Node* insert(Node* node, const std::pair<Key, Value>& data, Node** newNode,
               Node* parent = nullptr);
  Node* find_min(Node* node);
  Node* erase(Node* node, const Key& key);
  void clear(Node* node);
  Node* clone(Node* node, Node* parent);
  void swap(Node*& a, Node*& b);
  size_t size(Node* node) const;

 public:
  class Iterator;
  class ConstIterator;
  using key_type = Key;
  using value_type = Value;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

 public:
  class Iterator {
   public:
    using value_type = std::pair<Key, Value>;
    using reference = value_type&;
    Iterator() : current(nullptr) {}
    explicit Iterator(Node* node) : current(node) {}
    Iterator& operator++();  // Оператор для перехода к следующему элементу
    Iterator operator++(int);
    Iterator(const Iterator& other) { current = other.current; }
    Iterator& operator=(const Iterator& other) {
      if (this != &other) {
        current = other.current;
      }
      return *this;
    }
    bool operator!=(
        const Iterator& other) const;  // Оператор сравнения для цикла
    bool operator==(const Iterator& other) const;
    reference operator*() const;  // Оператор разыменования
   protected:
    Node* current;
  };

  class ConstIterator : public Iterator {
   public:
    using Iterator::Iterator;
    ConstIterator() : Iterator() {}
    const_reference operator*() const {
      return Iterator::operator*();
    };  // Оператор разыменования

   private:
    Node* current;
  };

 public:
  // constructors
  AVLTree() : root(nullptr) {}
  AVLTree(std::initializer_list<value_type> const& items);
  AVLTree(const AVLTree& tree) : root(clone(tree.root, nullptr)) {}
  AVLTree(AVLTree&& tree) noexcept;

  // destractor
  ~AVLTree();

  // assignment
  AVLTree& operator=(const AVLTree& tree);
  AVLTree& operator=(AVLTree& tree) noexcept;

  // Iterators
  Iterator begin();
  Iterator end();
  ConstIterator cbegin() const;
  ConstIterator cend() const;

  // capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // modifiers
  void clear();
  std::pair<Iterator, bool> insert(const std::pair<Key, Value>& data,
                                   bool multi);
  void erase(Iterator pos);
  void swap(AVLTree& other);
  void merge(AVLTree& other, bool multi);

  // lookup
  Iterator find(const key_type& key);
  bool contains(const key_type& key);

  // multiset
  Node* mul_insert(Node* node, const std::pair<Key, Value>& data,
                   Node** newNode, Node* parent = nullptr);
};

}  // namespace s21

#include "s21_avltree.tpp"

#endif  // SRC_S21_CONTAINERS_S21_AVLTREE_H_
