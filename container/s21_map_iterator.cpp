#ifndef MAP_ITERATOR
#define MAP_ITERATOR
#include "s21_map_Iterator.h"
namespace s21 {

// Определение конструктора
template <typename Key, typename T>
MapIterator<Key, T>::MapIterator(NodeMap<Key, T>* node) : current(node) {}

template <typename Key, typename T>
typename MapIterator<Key, T>::reference MapIterator<Key, T>::operator*() const {
  return *(reinterpret_cast<value_type*>(&current->val));
}

template <typename Key, typename T>
typename MapIterator<Key, T>::pointer MapIterator<Key, T>::operator->() const {
  return reinterpret_cast<value_type*>(&current->val);
}

template <typename Key, typename T>
MapIterator<Key, T>& MapIterator<Key, T>::operator++() {
  if (current->right != nullptr) {
    current = current->right;
    while (current->left != nullptr) {
      current = current->left;
    }
  } else {
    NodeMap<Key, T>* parent = current->parent;
    while (parent != nullptr && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename T>
MapIterator<Key, T> MapIterator<Key, T>::operator++(int) {
  MapIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename T>
MapIterator<Key, T>& MapIterator<Key, T>::operator--() {
  if (current->left != nullptr) {
    current = current->left;
    while (current->right != nullptr) {
      current = current->right;
    }
  } else {
    NodeMap<Key, T>* parent = current->parent;
    while (parent != nullptr && current == parent->left) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename T>
MapIterator<Key, T> MapIterator<Key, T>::operator--(int) {
  MapIterator temp = *this;
  --(*this);
  return temp;
}

template <typename Key, typename T>
bool MapIterator<Key, T>::operator==(const MapIterator& other) const {
  return current == other.current;
}

template <typename Key, typename T>
bool MapIterator<Key, T>::operator!=(const MapIterator& other) const {
  return current != other.current;
}
template class MapIterator<int, int>;  // Example, replace with actual types

template <typename Key, typename T>
MapConstIterator<Key, T>::MapConstIterator(const NodeMap<Key, T>* NodeMap)
    : current(NodeMap) {}

template <typename Key, typename T>
typename MapConstIterator<Key, T>::reference
MapConstIterator<Key, T>::operator*() const {
  return *(reinterpret_cast<const value_type*>(&current->val));
}

template <typename Key, typename T>
typename MapConstIterator<Key, T>::pointer
MapConstIterator<Key, T>::operator->() const {
  return reinterpret_cast<const value_type*>(&current->val);
}

template <typename Key, typename T>
MapConstIterator<Key, T>& MapConstIterator<Key, T>::operator++() {
  if (current->right != nullptr) {
    current = current->right;
    while (current->left != nullptr) {
      current = current->left;
    }
  } else {
    const NodeMap<Key, T>* parent = current->parent;
    while (parent != nullptr && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename T>
MapConstIterator<Key, T> MapConstIterator<Key, T>::operator++(int) {
  MapConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename T>
MapConstIterator<Key, T>& MapConstIterator<Key, T>::operator--() {
  if (current->left != nullptr) {
    current = current->left;
    while (current->right != nullptr) {
      current = current->right;
    }
  } else {
    const NodeMap<Key, T>* parent = current->parent;
    while (parent != nullptr && current == parent->left) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename T>
MapConstIterator<Key, T> MapConstIterator<Key, T>::operator--(int) {
  MapConstIterator temp = *this;
  --(*this);
  return temp;
}

template <typename Key, typename T>
bool MapConstIterator<Key, T>::operator==(const MapConstIterator& other) const {
  return current == other.current;
}

template <typename Key, typename T>
bool MapConstIterator<Key, T>::operator!=(const MapConstIterator& other) const {
  return current != other.current;
}

template class MapConstIterator<int, int>;
}  // namespace s21
#endif