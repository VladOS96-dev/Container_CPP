#ifndef MULTISET_ITERATOR
#define MULTISET_ITERATOR
#include "s21_multiset_iterator.h"
namespace s21 {
template <typename Key>
MultisetIterator<Key>::MultisetIterator(NodeMap<Key, int>* nodeMap,
                                        Tree<Key, int>* tree)
    : nodeMap(nodeMap), tree(tree) {}

template <typename Key>
typename MultisetIterator<Key>::reference MultisetIterator<Key>::operator*()
    const {
  return const_cast<Key&>(nodeMap->val.first);
}

template <typename Key>
typename MultisetIterator<Key>::pointer MultisetIterator<Key>::operator->()
    const {
  return &(nodeMap->val.first);
}

template <typename Key>
MultisetIterator<Key>& MultisetIterator<Key>::operator++() {
  if (nodeMap) {
    nodeMap = tree->successor(nodeMap);
  }
  return *this;
}

template <typename Key>
MultisetIterator<Key> MultisetIterator<Key>::operator++(int) {
  MultisetIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key>
MultisetIterator<Key>& MultisetIterator<Key>::operator--() {
  if (nodeMap) {
    nodeMap = tree->predecessor(nodeMap);
  }
  return *this;
}

template <typename Key>
MultisetIterator<Key> MultisetIterator<Key>::operator--(int) {
  MultisetIterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename Key>
bool MultisetIterator<Key>::operator==(
    const MultisetIterator<Key>& other) const {
  return nodeMap == other.nodeMap;
}

template <typename Key>
bool MultisetIterator<Key>::operator!=(
    const MultisetIterator<Key>& other) const {
  return nodeMap != other.nodeMap;
}

template <typename Key>
NodeMap<Key, int>* MultisetIterator<Key>::getNodeMap() const {
  return nodeMap;
}

// Реализация MultisetConstIterator
template <typename Key>
MultisetConstIterator<Key>::MultisetConstIterator(
    const NodeMap<Key, int>* nodeMap, const Tree<Key, int>* tree)
    : nodeMap(nodeMap), tree(tree) {}

template <typename Key>
typename MultisetConstIterator<Key>::reference
MultisetConstIterator<Key>::operator*() const {
  return nodeMap->val.first;
}

template <typename Key>
typename MultisetConstIterator<Key>::pointer
MultisetConstIterator<Key>::operator->() const {
  return &(nodeMap->val.first);
}

template <typename Key>
MultisetConstIterator<Key>& MultisetConstIterator<Key>::operator++() {
  if (nodeMap) {
    nodeMap = tree->successor(const_cast<NodeMap<Key, int>*>(nodeMap));
  }
  return *this;
}

template <typename Key>
MultisetConstIterator<Key> MultisetConstIterator<Key>::operator++(int) {
  MultisetConstIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key>
MultisetConstIterator<Key>& MultisetConstIterator<Key>::operator--() {
  nodeMap = tree->predecessor(const_cast<NodeMap<Key, int>*>(nodeMap));
  return *this;
}

template <typename Key>
MultisetConstIterator<Key> MultisetConstIterator<Key>::operator--(int) {
  MultisetConstIterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename Key>
bool MultisetConstIterator<Key>::operator==(
    const MultisetConstIterator<Key>& other) const {
  return nodeMap == other.nodeMap;
}

template <typename Key>
bool MultisetConstIterator<Key>::operator!=(
    const MultisetConstIterator<Key>& other) const {
  return nodeMap != other.nodeMap;
}

template <typename Key>
NodeMap<Key, int>* MultisetConstIterator<Key>::getNodeMap() const {
  return const_cast<NodeMap<Key, int>*>(nodeMap);
}

// Явная инстанциация шаблонов
template class MultisetIterator<int>;  // Замените int на нужный тип
template class MultisetConstIterator<int>;  // Замените int на нужный тип
}  // namespace s21
#endif