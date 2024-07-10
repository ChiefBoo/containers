#ifndef SRC_S21_CONTAINERS_S21_LIST_TPP_
#define SRC_S21_CONTAINERS_S21_LIST_TPP_

namespace s21 {

// constructors
template <typename T>
list<T>::list() : tail(new Node()), list_sz(0){};

template <typename T>
list<T>::list(size_type n) : list() {
  for (; n; --n) push_back(value_type());
}

template <typename T>
list<T>::list(std::initializer_list<T> const &items) : list() {
  for (auto value : items) push_back(value);
}

template <typename T>
list<T>::list(const list &other) : list() {
  for (auto nodes : other) push_back(nodes);
}

template <typename T>
list<T>::list(list &&other) : list() {
  splice(begin(), other);
}

// destructor
template <typename T>
list<T>::~list() {
  clear();
  delete tail;
  tail = nullptr;
}

// assignment operators
template <typename T>
list<T> &list<T>::operator=(const list &other) {
  if (this != &other) {
    clear();
    delete tail;
    tail = nullptr;
    new (this) list(other);
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list &&other) {
  if (this != &other) {
    clear();
    splice(begin(), other);
  }
  return *this;
}

// methods to access elements of the class
template <typename T>
typename list<T>::const_reference list<T>::front() {
  return *begin();
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  return *(--end());
}

// methods for iterating over class elements
template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(tail->next);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  return const_iterator(tail->next);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(tail);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(tail);
}

// container capacity information
template <typename T>
bool list<T>::empty() const {
  return list_sz == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return list_sz;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return ((std::numeric_limits<size_type>::max() / 2) / sizeof(Node));
}

// methods for modifying a container
template <typename T>
void list<T>::clear() {
  for (; list_sz > 0;) erase(begin());
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *new_node = new Node(value);
  pos.node->links_insert(new_node);
  ++list_sz;
  return iterator(new_node);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos != end()) {
    pos.node->links_erase();
    delete pos.node;
    --list_sz;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename T>
void list<T>::pop_back() {
  erase(--end());
}

template <typename T>
void list<T>::pop_front() {
  erase(begin());
}

template <typename T>
void list<T>::swap(list &other) noexcept {
  if (this != &other) {
    std::swap(tail, other.tail);
    std::swap(list_sz, other.list_sz);
  }
}

template <typename T>
void list<T>::merge(list &other) {
  if (this != &other) {
    iterator this_slider = begin();
    iterator other_slider = other.begin();
    while (this_slider != end() && other_slider != other.end()) {
      if (*this_slider > *other_slider) {
        Node *tmp = other_slider.node;
        ++other_slider;
        tmp->links_erase();
        this_slider.node->links_insert(tmp);
        --other.list_sz;
        ++list_sz;
      } else {
        ++this_slider;
      }
    }
    splice(end(), other);
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (this != &other && !other.empty()) {
    Node *curr = const_cast<Node *>(pos.node);
    Node *oth = other.tail;
    oth->prev->next = curr;
    oth->next->prev = curr->prev;
    curr->prev->next = oth->next;
    curr->prev = oth->prev;
    list_sz += other.size();
    other.list_sz = 0;
    other.tail->next = other.tail;
    other.tail->prev = other.tail;
  }
}

template <typename T>
void list<T>::reverse() noexcept {
  for (auto slider = begin(), it_end = end(); slider != it_end; --slider)
    std::swap(slider.node->next, slider.node->prev);
  std::swap(tail->next, tail->prev);
}

template <typename T>
void list<T>::unique() {
  iterator slider = ++begin();
  iterator at_end = end();
  iterator in_mind = begin();
  while (slider != at_end) {
    if (*slider == *in_mind) {
      erase(slider);
      slider = in_mind;
    } else {
      ++in_mind;
    }
    ++slider;
  }
}

template <typename T>
void list<T>::sort() {
  iterator slider_slow = begin();
  iterator slider_fast = begin();
  while (slider_fast != end() && ++slider_fast != end()) {
    ++slider_fast;
    ++slider_slow;
  }
  list<value_type> temp;
  for (auto it = temp.begin(); slider_slow != this->end();) {
    iterator temp_it = slider_slow;
    temp.insert(it, *slider_slow);
    ++slider_slow;
    this->erase(temp_it);
    ++it;
  }
  if (this->size() != 1) {
    this->sort();
  }
  if (temp.size() != 1) {
    temp.sort();
  }
  this->merge(temp);
}

// part 3
template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const iterator pos,
                                                Args &&...args) {
  size_type n = sizeof...(args);
  iterator res = pos;
  (insert(pos, std::forward<Args>(args)), ...);
  while (n) {
    --res;
    --n;
  }
  return res;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  insert_many(begin(), args...);
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_LIST_TPP_