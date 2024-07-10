#ifndef SRC_S21_CONTAINERS_S21_VECTOR_TPP_
#define SRC_S21_CONTAINERS_S21_VECTOR_TPP_

#include "s21_vector.h"

namespace s21 {

// private method
template <typename T>
void vector<T>::reserve_more_capacity(size_type size) {
  if (size > capacity_) {
    value_type *buff = new value_type[size];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size;
  }
}

// constructors
template <typename T>
inline vector<T>::vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  size_ = items.size();
  capacity_ = items.size();
}

// assignment operator
template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    delete[] arr_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    arr_ = v.arr_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.arr_ = nullptr;
  }
  return *this;
}

// element access
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (this->empty()) {
    throw std::out_of_range("Out of range");
  }
  return arr_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (this->empty()) {
    throw std::out_of_range("Out of range");
  }
  return arr_[size_ - 1];
}

template <typename T>
T *vector<T>::data() {
  return arr_;
}

// iterators
template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return arr_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
  return arr_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
  return arr_ + size_;
}

// capacity
template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return ((std::numeric_limits<size_type>::max() / 2) / sizeof(value_type));
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    reserve_more_capacity(size);
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    value_type *buff = new value_type[size_];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size_;
  }
}

// modifiers
template <typename T>
void vector<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - arr_;
  if (index > size_) {
    throw std::out_of_range("Invalid insertion position");
  }
  if (size_ == capacity_) {
    reserve_more_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  for (size_type i = size_; i > index; --i) {
    arr_[i] = std::move(arr_[i - 1]);
  }
  arr_[index] = value;
  ++size_;
  return arr_ + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - arr_;
  if (index >= size_) {
    throw std::out_of_range("Invalid erase position");
  }
  for (size_type i = index; i < size_ - 1; i++) {
    arr_[i] = std::move(arr_[i + 1]);
  }
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve_more_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  arr_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// part 3
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  size_type index;
  size_type numArgs = sizeof...(args);
  if (empty()) {
    index = 0;
    ;
  } else if (pos >= end()) {
    index = size_;
  } else {
    index = pos - begin();
  }
  reserve(size_ + numArgs);
  iterator it = begin() + index;
  iterator res = it;
  (insert(it++, std::forward<Args>(args)), ...);
  return res;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  size_type numArgs = sizeof...(args);
  reserve(size_ + numArgs);
  (push_back(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_VECTOR_TPP_