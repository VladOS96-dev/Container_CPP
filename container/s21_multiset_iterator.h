#pragma once
#include <iterator>

#include "s21_tree.h"

namespace s21 {

template <typename Key>
class MultisetIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = Key;
  using difference_type = std::ptrdiff_t;
  using pointer = Key*;
  using reference = Key&;

  MultisetIterator(NodeMap<Key, int>* nodeMap, Tree<Key, int>* tree);

  reference operator*() const;
  pointer operator->() const;

  MultisetIterator& operator++();
  MultisetIterator operator++(int);

  MultisetIterator& operator--();
  MultisetIterator operator--(int);

  bool operator==(const MultisetIterator& other) const;
  bool operator!=(const MultisetIterator& other) const;

  NodeMap<Key, int>* getNodeMap() const;

 private:
  NodeMap<Key, int>* nodeMap;
  Tree<Key, int>* tree;
};

template <typename Key>
class MultisetConstIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = Key;
  using difference_type = std::ptrdiff_t;
  using pointer = const Key*;
  using reference = const Key&;

  MultisetConstIterator(const NodeMap<Key, int>* nodeMap,
                        const Tree<Key, int>* tree);

  reference operator*() const;
  pointer operator->() const;

  MultisetConstIterator& operator++();
  MultisetConstIterator operator++(int);

  MultisetConstIterator& operator--();
  MultisetConstIterator operator--(int);

  bool operator==(const MultisetConstIterator& other) const;
  bool operator!=(const MultisetConstIterator& other) const;

  NodeMap<Key, int>* getNodeMap() const;

 private:
  const NodeMap<Key, int>* nodeMap;
  const Tree<Key, int>* tree;
};

}  // namespace s21
#include "s21_multiset_iterator.cpp"