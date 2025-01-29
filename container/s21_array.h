#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>

namespace s21 {
template <class T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using array_type = array<T, N>;

  array();
  array(std::initializer_list<T> const &items);
  array(const array_type &a);
  array(array_type &&a) noexcept;
  ~array() {}

  array_type &operator=(const array &other);
  array_type &operator=(array &&a) noexcept;

  constexpr reference operator[](size_type pos);
  constexpr const_reference operator[](size_type pos) const;

  constexpr reference at(size_type pos);
  constexpr const_reference at(size_type pos) const;
  constexpr reference front();
  constexpr const_reference front() const;
  constexpr reference back();
  constexpr const_reference back() const;

  constexpr iterator data() noexcept;
  constexpr const_iterator data() const noexcept;

  constexpr iterator begin() noexcept;
  constexpr const_iterator begin() const noexcept;
  constexpr const_iterator cbegin() const noexcept;

  constexpr iterator end() noexcept;
  constexpr const_iterator end() const noexcept;
  constexpr const_iterator cend() const noexcept;

  constexpr bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;

  void swap(array &other) noexcept;
  void fill(const_reference value);

 private:
  const size_type size_ = N;
  value_type data_[N];
};

template <class T>
class array<T, 0> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using array_type = array<T, 0>;

  array() {}
  array([[maybe_unused]] const array_type &a) : array() {}
  array([[maybe_unused]] array_type &&a) noexcept : array() {}
  ~array() {}

  array_type &operator=([[maybe_unused]] const array &other) { return *this; }
  array_type &operator=([[maybe_unused]] array &&a) noexcept { return *this; }

  constexpr reference at([[maybe_unused]] size_type pos) {
    throw std::out_of_range("Out of range");
  }
  constexpr const_reference at([[maybe_unused]] size_type pos) const {
    throw std::out_of_range("Out of range");
  }

  constexpr reference front() { throw std::out_of_range("Out of range"); }
  constexpr const_reference front() const {
    throw std::out_of_range("Out of range");
  }
  constexpr reference back() { throw std::out_of_range("Out of range"); }
  constexpr const_reference back() const {
    throw std::out_of_range("Out of range");
  }
  constexpr iterator data() noexcept { return nullptr; }
  constexpr const_iterator data() const noexcept { return nullptr; }

  constexpr iterator begin() noexcept { return nullptr; }
  constexpr const_iterator begin() const noexcept { return nullptr; }
  constexpr const_iterator cbegin() const noexcept { return nullptr; }

  constexpr iterator end() noexcept { return nullptr; }
  constexpr const_iterator end() const noexcept { return nullptr; }
  constexpr const_iterator cend() const noexcept { return nullptr; }

  constexpr bool empty() const noexcept { return true; }
  constexpr size_type size() const noexcept { return 0; }
  constexpr size_type max_size() const noexcept { return 0; }

  void swap([[maybe_unused]] array &other) noexcept {}
  void fill([[maybe_unused]] const_reference value) {}

 private:
  value_type data_[1];
  const size_type size_ = 0;
};
}  // namespace s21
#include "s21_array.cpp"
#endif  // S21_ARRAY_H