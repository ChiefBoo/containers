#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_ARRAY_H_

//#include <cstdlib>

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;

  // member functions
  array() = default;
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  ~array() = default;
  array &operator=(const array &other) noexcept;
  array &operator=(array &&other) noexcept;

  // element access
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  iterator data() noexcept;
  const_iterator data() const;

  // iterators
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  // capacity
  constexpr bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;

  // operations
  void fill(const_reference value);
  void swap(array &other) noexcept;

 private:
  value_type elements[N] = {};
  size_type capacity = N;
};
}  // namespace s21

#include "s21_array.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_ARRAY_H_