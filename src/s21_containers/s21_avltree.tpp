#ifndef SRC_S21_CONTAINERS_S21_AVLTREE_TPP_
#define SRC_S21_CONTAINERS_S21_AVLTREE_TPP_

#include "s21_avltree.h"

namespace s21 {

template <typename Key, typename Value>
int AVLTree<Key, Value>::height(Node* node) {
  return node ? node->height : 0;
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::balance_factor(Node* node) {
  return node ? height(node->right) - height(node->left) : 0;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::rotate_right(Node* y) {
  Node* x = y->left;
  Node* T = x->right;
  x->right = y;
  y->left = T;
  if (T) T->parent = y;
  if (y->left) y->left->parent = y;
  x->parent = y->parent;
  y->parent = x;
  y->height = std::max(height(y->left), height(y->right)) + 1;
  x->height = std::max(height(x->left), height(x->right)) + 1;
  return x;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::rotate_left(Node* x) {
  Node* y = x->right;
  Node* T = y->left;
  y->left = x;
  x->right = T;
  if (x->right) x->right->parent = x;
  y->parent = x->parent;
  x->parent = y;
  if (T) T->parent = x;
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;
  return y;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::balance(Node* node) {
  node->height = std::max(height(node->left), height(node->right)) + 1;
  int balance = balance_factor(node);
  // Left Heavy
  if (balance > 1) {
    // Right Right Case
    if (balance_factor(node->right) < 0) {
      node->right = rotate_right(node->right);
    }
    // Right Left Case
    return rotate_left(node);
  }
  // Right Heavy
  if (balance < -1) {
    // Left Left Case
    if (balance_factor(node->left) > 0) {
      node->left = rotate_left(node->left);
    }
    // Left Right Case
    return rotate_right(node);
  }
  return node;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::find_min(Node* node) {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::erase(Node* node,
                                                               const Key& key) {
  if (!node) {
    return nullptr;
  }
  if (key < node->data.first) {
    node->left = erase(node->left, key);
  } else if (key > node->data.first) {
    node->right = erase(node->right, key);
  } else {
    if (!node->left || !node->right) {
      Node* temp = node->left ? node->left : node->right;
      if (!temp) {
        temp = node;
        node = nullptr;
      } else {
        temp->parent = node->parent;
        *node = *temp;
      }
      delete temp;
    } else {
      Node* temp = find_min(node->right);
      node->data = temp->data;
      node->right = erase(node->right, temp->data.first);
    }
  }
  if (!node) {
    return nullptr;
  }
  return balance(node);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear(Node* node) {
  if (!node) {
    return;
  }
  clear(node->left);
  clear(node->right);
  node->left = nullptr;
  node->right = nullptr;
  delete node;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::clone(Node* node,
                                                               Node* parent) {
  if (!node) {
    return nullptr;
  }
  Node* new_node =
      new Node(node->data.first, node->data.second, nullptr, nullptr, parent);
  new_node->left = clone(node->left, node);
  new_node->right = clone(node->right, node);
  return new_node;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::swap(Node*& a, Node*& b) {
  Node* temp = a;
  a = b;
  b = temp;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::size_type AVLTree<Key, Value>::size(
    Node* node) const {
  if (!node) {
    return 0;
  }
  return size(node->left) + size(node->right) + 1;
}

// Оператор для перехода к следующему элементу
template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator&
AVLTree<Key, Value>::Iterator::operator++() {
  if (current->right) {
    current = current->right;
    while (current->left) {
      current = current->left;
    }
  } else {
    Node* parent = current->parent;
    while (parent && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator
AVLTree<Key, Value>::Iterator::operator++(int) {
  iterator it(*this);
  ++(*this);
  return it;
}

// Оператор сравнения для цикла
template <typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator!=(const Iterator& other) const {
  return current != other.current;
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator==(const Iterator& other) const {
  return current == other.current;
}

// Оператор разыменования
template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator::reference
AVLTree<Key, Value>::Iterator::operator*() const {
  if (current) {
    return current->data;
  } else {
    throw std::out_of_range("Dereferencing end() iterator");
  }
}

// contructors
template <typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(std::initializer_list<value_type> const& items)
    : root(nullptr) {
  for (const auto& item : items) {
    root = insert(root, item);
  }
}

template <typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(AVLTree&& tree) noexcept : root(nullptr) {
  swap(root, tree.root);
}

// destructors
template <typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
  clear(root);
}

// Assignment
template <typename Key, typename Value>
AVLTree<Key, Value>& AVLTree<Key, Value>::operator=(const AVLTree& tree) {
  if (this != &tree) {
    clear(root);
    root = clone(tree.root);
  }
  return *this;
}

template <typename Key, typename Value>
AVLTree<Key, Value>& AVLTree<Key, Value>::operator=(AVLTree& tree) noexcept {
  if (this != &tree) {
    clear(root);
    swap(root, tree.root);
  }
  return *this;
}

// Iterators
template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::begin() {
  if (!root) {
    return end();
  }
  Node* current = root;
  while (current->left) {
    current = current->left;
  }
  return Iterator(current);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::end() {
  return Iterator(nullptr);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::ConstIterator AVLTree<Key, Value>::cbegin()
    const {
  if (!root) {
    return cend();
  }
  Node* current = root;
  while (current->left) {
    current = current->left;
  }
  return ConstIterator(current);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::ConstIterator AVLTree<Key, Value>::cend() const {
  return ConstIterator(nullptr);
}

// Capacity
template <typename Key, typename Value>
bool AVLTree<Key, Value>::empty() const {
  return !root;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::size_type AVLTree<Key, Value>::size() const {
  return size(root);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::size_type AVLTree<Key, Value>::max_size() const {
  // return std::numeric_limits<size_type>::max();
  return (std::numeric_limits<size_type>::max() / sizeof(value_type));
}

// Modifiers
template <typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
  clear(root);
  root = nullptr;
}

template <typename Key, typename Value>
std::pair<typename AVLTree<Key, Value>::Iterator, bool>
AVLTree<Key, Value>::insert(const std::pair<Key, Value>& data, bool multi) {
  Node* newNode{};
  if (!multi) {
    root = insert(root, data, &newNode);
    if (iterator(newNode) != end()) {
      return std::make_pair(Iterator(newNode), true);
    } else {
      return std::make_pair(find(data.first), false);
    }
  } else {
    root = mul_insert(root, data, &newNode);
    return std::make_pair(Iterator(newNode), true);
  }
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::insert(
    Node* node, const std::pair<Key, Value>& data, Node** newNode,
    Node* parent) {
  if (!node) {
    // Node *tmp = new Node(data.first, data.second, nullptr, nullptr, parent);
    *newNode = new Node(data.first, data.second, nullptr, nullptr, parent);
    // *newNode = tmp;
    return *newNode;
  }
  if (data.first < node->data.first) {
    node->left = insert(node->left, data, newNode, node);
  } else if (data.first > node->data.first) {
    node->right = insert(node->right, data, newNode, node);
  } else {
    //     // Duplicate keys are not allowed in AVL trees
    return node;
  }

  return balance(node);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::erase(Iterator pos) {
  if (pos == end() || empty()) {
    return;
  }
  key_type key_to_erase = (*pos).first;
  root = erase(root, key_to_erase);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::swap(AVLTree& other) {
  swap(root, other.root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::merge(AVLTree& other, bool multi) {
  for (auto it = other.begin(); it != other.end();) {
    if (!contains((*it).first) || multi) {
      insert(*it, multi);
      other.erase(it);
      it = other.begin();
    } else {
      ++it;
    }
  }
}

// Lookup
template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::find(
    const key_type& key) {
  Node* current = root;
  while (current) {
    if (key == current->data.first) {
      return Iterator(current);
    } else if (key < current->data.first) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return end();
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::contains(const key_type& key) {
  return find(key) != end();
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::mul_insert(
    Node* node, const std::pair<Key, Value>& data, Node** newNode,
    Node* parent) {
  if (!node) {
    *newNode = new Node(data.first, data.second, nullptr, nullptr, parent);
    return *newNode;
  }
  if (data.first <= node->data.first) {
    node->left = mul_insert(node->left, data, newNode, node);
  } else {
    node->right = mul_insert(node->right, data, newNode, node);
  }
  return balance(node);
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_AVLTREE_TPP_
