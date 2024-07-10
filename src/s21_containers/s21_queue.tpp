#ifndef SRC_S21_CONTAINERS_S21_QUEUE_TPP_
#define SRC_S21_CONTAINERS_S21_QUEUE_TPP_

#include "s21_queue.h"

namespace s21 {

// assignment
template <typename T>
queue<T>& queue<T>::operator=(queue&& q) {
  if (this != &q) {
    data_ = std::move(q.data_);
  }
  return *this;
}

// Element access
template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("Front on empty queue");
  }
  return data_.front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("Back on empty queue");
  }
  return data_.back();
}

// Capacity
template <typename T>
bool queue<T>::empty() const {
  return data_.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return data_.size();
}

// Modifiers
template <typename T>
void queue<T>::push(const_reference value) {
  data_.push_back(value);
}

template <typename T>
void queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Pop on empty queue");
  }
  data_.erase(data_.begin());
}

template <typename T>
void queue<T>::swap(queue& other) {
  data_.swap(other.data_);
}

// part 3
template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  data_.insert_many_back(args...);
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_QUEUE_TPP_