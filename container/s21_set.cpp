#ifndef SET_CPP
#define SET_CPP
#include "s21_set.h"
namespace s21 {

template <typename Key>
Set<Key>::Set() : tree() {}

template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const& items) : tree() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
Set<Key>::Set(const Set& s) : tree(s.tree) {}

template <typename Key>
Set<Key>::Set(Set&& s) noexcept : tree(std::move(s.tree)) {}

template <typename Key>
Set<Key>::~Set() = default;

template <typename Key>
Set<Key>& Set<Key>::operator=(Set&& s) noexcept {
  tree = std::move(s.tree);
  return *this;
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() {
  return iterator(tree.predecessor(tree.getRoot()), &tree);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() {
  return iterator(nullptr, &tree);
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::begin() const {
  return const_iterator(tree.predecessor(tree.getRoot()), &tree);
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::end() const {
  return const_iterator(nullptr, &tree);
}

template <typename Key>
bool Set<Key>::empty() const {
  return tree.getRoot() == nullptr;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::size() const {
  size_type count = 0;
  if (!empty()) {
    for (auto it = begin(); it != end(); ++it) {
      ++count;
    }
  }
  return count;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename Key>
void Set<Key>::clear() {
  while (!empty()) {
    erase(tree.getRoot());
  }
}

template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const value_type& value) {
  if (tree.search(value) != nullptr) {
    return {iterator(tree.search(value), &tree), false};
  }
  NodeMap<Key, bool>* insertedNodeMap =
      tree.insert(std::make_pair(value, true));
  return {iterator(insertedNodeMap, &tree), true};
}

template <typename Key>
void Set<Key>::erase(iterator pos) {
  if (pos.node != nullptr) {
    tree.remove(pos.node->val.first);
  }
}

template <typename Key>
void Set<Key>::swap(Set& other) {
  std::swap(tree, other.tree);
}

template <typename Key>
void Set<Key>::merge(Set& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto next = it;
    insert(*it);
    other.erase(it);
    ++next;
    it = next;
  }
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const Key& key) {
  NodeMap<Key, bool>* NodeMap = tree.search(key);
  return NodeMap != nullptr ? iterator(NodeMap, &tree) : end();
}

template <typename Key>
bool Set<Key>::contains(const Key& key) const {
  return tree.search(key) != nullptr;
}
template <typename Key>
template <typename... Args>
std::vector<std::pair<typename Set<Key>::iterator, bool>> Set<Key>::insert_many(
    Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

}  // namespace s21
#endif