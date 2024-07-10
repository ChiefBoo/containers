#ifndef SRC_S21_CONTAINERS_S21_STACK_TPP_
#define SRC_S21_CONTAINERS_S21_STACK_TPP_

#include "s21_stack.h"

namespace s21 {

// assignment
template <typename T>
stack<T>& stack<T>::operator=(stack&& s) {
  if (this != &s) {
    data_ = std::move(s.data_);
  }
  return *this;
}

// Stack Element access
template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  return data_.back();
}

// Stack Capacity
template <typename T>
bool stack<T>::empty() const {
  return data_.empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return data_.size();
}

// Stack Modifiers
template <typename T>
void stack<T>::push(const_reference value) {
  data_.push_back(value);
}

template <typename T>
void stack<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Pop on empty stack");
  }
  data_.pop_back();
}

template <typename T>
void stack<T>::swap(stack& other) {
  data_.swap(other.data_);
}

// part 3
template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args&&... args) {
  size_type pos = 0;
  (data_.insert(data_.begin() + pos++, std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_STACK_TPP_