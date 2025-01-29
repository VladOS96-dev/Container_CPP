#pragma once
#include "s21_tree.h"
namespace s21 {

template <typename Key>
class SetIterator {
 public:
  using NodePtr = NodeMap<Key, bool>*;

  SetIterator(NodePtr node, Tree<Key, bool>* tree);

  Key& operator*() const;
  SetIterator& operator++();
  bool operator!=(const SetIterator& other) const;

 private:
  NodePtr node;
  Tree<Key, bool>* tree;

  template <typename>
  friend class Set;
};

template <typename Key>
class SetConstIterator {
 public:
  using NodePtr = const NodeMap<Key, bool>*;

  SetConstIterator(NodePtr node, const Tree<Key, bool>* tree);

  const Key& operator*() const;
  SetConstIterator& operator++();
  bool operator!=(const SetConstIterator& other) const;

 private:
  NodePtr node;
  const Tree<Key, bool>* tree;

  template <typename>
  friend class Set;
};

}  // namespace s21
#include "s21_set_iterator.cpp"