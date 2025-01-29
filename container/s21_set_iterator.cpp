#ifndef SET_ITERATOR
#define SET_ITERATOR
#include "s21_set_iterator.h"
namespace s21 {
template <typename Key>
SetIterator<Key>::SetIterator(NodePtr node, Tree<Key, bool>* tree)
    : node(node), tree(tree) {}

template <typename Key>
Key& SetIterator<Key>::operator*() const {
  return const_cast<Key&>(node->val.first);
}

template <typename Key>
SetIterator<Key>& SetIterator<Key>::operator++() {
  node = tree->successor(node);
  return *this;
}

template <typename Key>
bool SetIterator<Key>::operator!=(const SetIterator<Key>& other) const {
  return node != other.node;
}

// SetConstIterator Implementation
template <typename Key>
SetConstIterator<Key>::SetConstIterator(NodePtr node,
                                        const Tree<Key, bool>* tree)
    : node(node), tree(tree) {}

template <typename Key>
const Key& SetConstIterator<Key>::operator*() const {
  return node->val.first;
}

template <typename Key>
SetConstIterator<Key>& SetConstIterator<Key>::operator++() {
  if (node != nullptr) {
    node = tree->successor(const_cast<NodeMap<Key, bool>*>(node));
  }
  return *this;
}

template <typename Key>
bool SetConstIterator<Key>::operator!=(
    const SetConstIterator<Key>& other) const {
  return node != other.node;
}
template class SetIterator<int>;
template class SetConstIterator<int>;
}  // namespace s21
#endif