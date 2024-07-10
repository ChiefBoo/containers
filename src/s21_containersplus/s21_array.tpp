#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_ARRAY_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_ARRAY_TPP_

#include "s21_array.h"

namespace s21 {
// member functions

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), elements);
}

template <typename T, std::size_t N>
array<T, N>::array(const array &other) {
  for (size_t i = 0; i < other.size(); i++) {
    elements[i] = other.elements[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array &&other) {
  for (size_t i = 0; i < other.size(); i++) {
    elements[i] = std::move(other.elements[i]);
  }
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(
    const array &other) noexcept {
  for (size_t i = 0; i < other.size(); i++) {
    elements[i] = other.elements[i];
  }

  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(array &&other) noexcept {
  for (size_t i = 0; i < other.size(); i++) {
    elements[i] = std::move(other.elements[i]);
  }

  return *this;
}

// element access

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos > N) throw std::out_of_range("s21:array at - Index out of range");
  return elements[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos > N) throw std::out_of_range("s21:array at - Index out of range");
  return elements[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return elements[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return elements[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return elements[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return elements[0];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return elements[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return elements[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return elements;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const {
  return elements;
}

// iterators

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return elements;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return elements;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return elements + capacity;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return elements + capacity;
}

// capacity

template <typename T, std::size_t N>
constexpr bool array<T, N>::empty() const noexcept {
  return begin() == end();
}

template <typename T, std::size_t N>
constexpr typename array<T, N>::size_type array<T, N>::size() const noexcept {
  // return std::distance(begin(), end());
  return capacity;
}

template <typename T, std::size_t N>
constexpr typename array<T, N>::size_type array<T, N>::max_size()
    const noexcept {
  return capacity;
}

// operations

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  // for (int i = 0; i < capacity; i++)
  //     elements[i] = value;

  std::fill(begin(), end(), value);
  return;
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) noexcept {
  std::swap_ranges(begin(), end(), other.begin());
  return;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_ARRAY_TPP_