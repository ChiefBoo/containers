#ifndef SRC_S21_CONTAINERS_S21_QUEUE_H_
#define SRC_S21_CONTAINERS_S21_QUEUE_H_

#include "s21_vector.h"

namespace s21 {

template <typename T>
class queue {
 private:
  vector<T> data_;

 public:
  using value_type = typename vector<T>::value_type;
  using reference = typename vector<T>::reference;
  using const_reference = typename vector<T>::const_reference;
  using size_type = typename vector<T>::size_type;

  // constructors
  queue() = default;
  queue(std::initializer_list<T> const &items) : data_(items) {}
  queue(const queue &q) : data_(q.data_) {}
  queue(queue &&q) : data_(std::move(q.data_)) {}

  // destructor
  ~queue() {}

  // assignment
  queue &operator=(queue &&q);

  // Element access
  const_reference front() const;
  const_reference back() const;

  // Capacity
  bool empty() const;
  size_type size() const;

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  // part 3
  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

#include "s21_queue.tpp"

#endif  // SRC_S21_CONTAINERS_S21_QUEUE_H_