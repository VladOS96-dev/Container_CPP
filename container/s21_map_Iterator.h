

#pragma once
#include <iterator>

#include "s21_tree.h"

namespace s21 {

template <typename Key, typename T>
class MapIterator {
 private:
  NodeMap<Key, T>* current;

 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = std::pair<Key, T>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  MapIterator(NodeMap<Key, T>* node = nullptr);

  reference operator*() const;
  pointer operator->() const;

  MapIterator& operator++();
  MapIterator operator++(int);

  MapIterator& operator--();
  MapIterator operator--(int);

  bool operator==(const MapIterator& other) const;
  bool operator!=(const MapIterator& other) const;
};
template <typename Key, typename T>
class MapConstIterator {
 private:
  const NodeMap<Key, T>* current;

 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = std::pair<Key, int>;
  using difference_type = std::ptrdiff_t;
  using pointer = const value_type*;
  using reference = const value_type&;

  MapConstIterator(const NodeMap<Key, T>* NodeMap = nullptr);

  reference operator*() const;
  pointer operator->() const;

  MapConstIterator& operator++();
  MapConstIterator operator++(int);

  MapConstIterator& operator--();
  MapConstIterator operator--(int);

  bool operator==(const MapConstIterator& other) const;
  bool operator!=(const MapConstIterator& other) const;
};

}  // namespace s21
#include "s21_map_iterator.cpp"