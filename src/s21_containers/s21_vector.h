#ifndef SRC_S21_CONTAINERS_S21_VECTOR_H_
#define SRC_S21_CONTAINERS_S21_VECTOR_H_

#include <cstddef>  // For size_t
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class vector {
  // Member types
  // private attributes
 private:
  size_t size_;
  size_t capacity_;
  T *arr_;
  // public attribures
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // private method
 private:
  void reserve_more_capacity(size_type size);

  // public methods
 public:
  // constructors
  // default constructor (simplified syntax for assigning values to attributes)
  vector() : size_(0U), capacity_(0U), arr_(nullptr) {}
  // parametrized constructor for fixed size vector (explicit was used in order
  // to avoid automatic type conversion)
  explicit vector(size_type n)
      : size_(n), capacity_(n), arr_(n ? new T[n]{} : nullptr) {}
  // initializer list constructor (allows creating lists with initializer lists,
  // see main.cpp)
  vector(std::initializer_list<value_type> const &items);
  // copy constructor with simplified syntax
  vector(const vector &v) : size_(v.size_), capacity_(v.capacity_) {
    arr_ = new value_type[v.capacity_];
    std::copy(v.arr_, v.arr_ + v.size_, arr_);
  }
  // move constructor with simplified syntax
  vector(vector &&v) : size_(v.size_), capacity_(v.capacity_), arr_(v.arr_) {
    v.arr_ = nullptr;
    v.size_ = 0;
  }
  // destructor
  ~vector() { delete[] arr_; }

  // assignment
  vector &operator=(vector &&v);

  // element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T *data();

  // iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  // part 3
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // SRC_S21_CONTAINERS_S21_VECTOR_H_