#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "s21_vector.h"

#include <algorithm>
#include <limits>
#include <stdexcept>

namespace s21 {

// Constructors and Destructor
template <typename T>
Vector<T>::Vector() : _data(nullptr), _size(0), _capacity(0) {}

template <typename T>
Vector<T>::Vector(size_type n) : _data(new T[n]()), _size(n), _capacity(n) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const& items)
    : Vector(items.size()) {
  std::copy(items.begin(), items.end(), _data);
}

template <typename T>
Vector<T>::Vector(const Vector& v) : Vector(v._size) {
  std::copy(v._data, v._data + v._size, _data);
}

template <typename T>
Vector<T>::Vector(Vector&& v) noexcept
    : _data(v._data), _size(v._size), _capacity(v._capacity) {
  v._data = nullptr;
  v._size = 0;
  v._capacity = 0;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] _data;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  if (this != &v) {
    delete[] _data;
    _size = v._size;
    _capacity = v._capacity;
    _data = new T[_capacity];
    std::copy(v._data, v._data + v._size, _data);
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& v) noexcept {
  if (this != &v) {
    delete[] _data;
    _data = v._data;
    _size = v._size;
    _capacity = v._capacity;
    v._data = nullptr;
    v._size = 0;
    v._capacity = 0;
  }
  return *this;
}

// Element access
template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= _size) throw std::out_of_range("Index out of bounds");
  return _data[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return _data[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return _data[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return _data[_size - 1];
}

template <typename T>
T* Vector<T>::data() {
  return _data;
}

template <typename T>
const T* Vector<T>::data() const {
  return _data;
}

// Iterators
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return _data;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return _data;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return _data + _size;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return _data + _size;
}

// Capacity
template <typename T>
bool Vector<T>::empty() const {
  return _size == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return _size;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void Vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > _capacity) {
    T* new_data = new T[new_capacity];
    std::move(_data, _data + _size, new_data);
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
  }
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return _capacity;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (_size < _capacity) {
    T* new_data = new T[_size];
    std::move(_data, _data + _size, new_data);
    delete[] _data;
    _data = new_data;
    _capacity = _size;
  }
}

// Modifiers
template <typename T>
void Vector<T>::clear() {
  _size = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (_size >= _capacity) reserve(_capacity == 0 ? 1 : 2 * _capacity);
  pos = begin() + index;
  std::move_backward(pos, end(), end() + 1);
  *pos = value;
  ++_size;
  return pos;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  std::move(pos + 1, end(), pos);
  --_size;
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (_size >= _capacity) reserve(_capacity == 0 ? 1 : 2 * _capacity);
  _data[_size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
  --_size;
}

template <typename T>
void Vector<T>::swap(Vector& other) {
  std::swap(_data, other._data);
  std::swap(_size, other._size);
  std::swap(_capacity, other._capacity);
}

// New Functions
template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args&&... args) {
  size_type num_new_elements = sizeof...(args);
  if (_size + num_new_elements > _capacity) {
    reserve(std::max(_capacity * 2, _size + num_new_elements));
  }
  (void)std::initializer_list<int>{(push_back(std::forward<Args>(args)), 0)...};
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  Vector<T> arr = {args...};
  auto local_pos = (iterator)pos;
  for (auto i = arr.end() - 1; i != arr.begin() - 1; i--) {
    local_pos = insert(local_pos, *i);
  }
  return local_pos;
}

}  // namespace s21
#endif