#pragma once
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename T>
class Vector {
 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  // Constructors and Destructor
  Vector();
  explicit Vector(size_type n);
  Vector(std::initializer_list<value_type> const& items);
  Vector(const Vector& v);
  Vector(Vector&& v) noexcept;
  ~Vector();
  Vector& operator=(const Vector& v);
  Vector& operator=(Vector&& v) noexcept;

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T* data();
  const T* data() const;

  // Iterators
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type new_capacity);
  size_type capacity() const;
  void shrink_to_fit();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector& other);

  // New Functions
  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

 private:
  T* _data;
  size_type _size;
  size_type _capacity;
};

}  // namespace s21
#include "s21_vector.cpp"
