#ifndef ARRAY_CPP
#define ARRAY_CPP
#include "s21_array.h"

template <class T, size_t N>
s21::array<T, N>::array() {
  constexpr T object{};
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = object;
  }
}

template <typename T, size_t N>
s21::array<T, N>::array(std::initializer_list<T> const &items) {
  size_t i = 0;
  for (auto it = items.begin(); it != items.end() && i < N; ++it, ++i) {
    data_[i] = *it;
  }
}

template <class T, size_t N>
s21::array<T, N>::array(const array_type &a) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
  }
}

template <class T, size_t N>
s21::array<T, N>::array(array_type &&a) noexcept {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
    a.data_[i] = 0;
  }
}

template <class T, size_t N>
s21::array<T, N> &s21::array<T, N>::operator=(const array &a) {
  if (this != &a) {
    for (size_type i = 0; i < a.size_; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
}

template <class T, size_t N>
s21::array<T, N> &s21::array<T, N>::operator=(array &&a) noexcept {
  if (this != &a) {
    for (size_type i = 0; i < a.size_; ++i) {
      data_[i] = a.data_[i];
      a.data_[i] = 0;
    }
  }
  return *this;
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::reference s21::array<T, N>::operator[](
    size_type pos) {
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_reference
s21::array<T, N>::operator[](size_type pos) const {
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::reference s21::array<T, N>::at(
    size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index is out of range");
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_reference s21::array<T, N>::at(
    size_type pos) const {
  if (pos >= size_) throw std::out_of_range("Index is out of range");
  return data_[pos];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::reference s21::array<T, N>::front() {
  return data_[0];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_reference s21::array<T, N>::front()
    const {
  return data_[0];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::reference s21::array<T, N>::back() {
  return data_[size_ - 1];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_reference s21::array<T, N>::back()
    const {
  return data_[size_ - 1];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::iterator
s21::array<T, N>::data() noexcept {
  return data_;
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_iterator s21::array<T, N>::data()
    const noexcept {
  if (size_ == 0) return nullptr;
  return data_;
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::iterator
s21::array<T, N>::begin() noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_iterator s21::array<T, N>::begin()
    const noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_iterator s21::array<T, N>::cbegin()
    const noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::iterator s21::array<T, N>::end() noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_iterator s21::array<T, N>::end()
    const noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::const_iterator s21::array<T, N>::cend()
    const noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr bool s21::array<T, N>::empty() const noexcept {
  return false;
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::size_type s21::array<T, N>::size()
    const noexcept {
  return size_;
}

template <class T, size_t N>
constexpr typename s21::array<T, N>::size_type s21::array<T, N>::max_size()
    const noexcept {
  return size_;
}

template <class T, size_t N>
void s21::array<T, N>::swap(array &other) noexcept {
  if (this != &other) {
    for (size_t i = 0; i < size_; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }
}

template <class T, size_t N>
void s21::array<T, N>::fill(const T &value) {
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}
#endif