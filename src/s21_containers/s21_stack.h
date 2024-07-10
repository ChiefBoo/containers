#ifndef SRC_S21_CONTAINERS_S21_STACK_H_
#define SRC_S21_CONTAINERS_S21_STACK_H_

#include "s21_vector.h"

namespace s21 {

template <typename T>
class stack {
 private:
  vector<T> data_;

 public:
  using value_type = typename vector<T>::value_type;
  using reference = typename vector<T>::reference;
  using const_reference = typename vector<T>::const_reference;
  using size_type = typename vector<T>::size_type;

  // constructors
  stack() = default;
  stack(std::initializer_list<T> const &items) : data_(items) {}
  stack(const stack &s) : data_(s.data_) {}
  stack(stack &&s) : data_(std::move(s.data_)) {}

  // destructor
  ~stack() {}

  // assignment
  stack &operator=(stack &&s);

  // Stack Element access
  const_reference top() const;

  // Stack Capacity
  bool empty() const;
  size_type size() const;

  // Stack Modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  // part 3
  template <typename... Args>
  void insert_many_front(Args &&...args);
};

}  // namespace s21

#include "s21_stack.tpp"

#endif  // SRC_S21_CONTAINERS_S21_STACK_H_