#ifndef MULTISET_CPP
#define MULTISET_CPP
#include "s21_multiset.h"
namespace s21 {

template <typename Key>
Multiset<Key>::Multiset() : tree() {}

template <typename Key>
Multiset<Key>::Multiset(std::initializer_list<value_type> const& items)
    : tree() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
Multiset<Key>::Multiset(const Multiset& ms) : tree(ms.tree) {}

template <typename Key>
Multiset<Key>::Multiset(Multiset&& ms) noexcept {
  if (this != &ms) {
    tree = std::move(ms.tree);

    ms.clear();
  }
}

template <typename Key>
Multiset<Key>::~Multiset() = default;

template <typename Key>
Multiset<Key>& Multiset<Key>::operator=(Multiset&& ms) noexcept {
  if (this != &ms) {
    tree = std::move(ms.tree);
  }
  return *this;
}
template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::begin() {
  return iterator(tree.predecessor(tree.getRoot()), &tree);
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::end() {
  return iterator(nullptr, &tree);
}

template <typename Key>
typename Multiset<Key>::const_iterator Multiset<Key>::begin() const {
  return const_iterator(tree.predecessor(tree.getRoot()), &tree);
}

template <typename Key>
typename Multiset<Key>::const_iterator Multiset<Key>::end() const {
  return const_iterator(nullptr, &tree);
}
template <typename Key>
bool Multiset<Key>::empty() const {
  return tree.getRoot() == nullptr;
}

template <typename Key>
typename Multiset<Key>::size_type Multiset<Key>::size() const {
  size_type count = 0;
  for (auto it = begin(); it != end(); ++it) {
    ++count;
  }
  return count;
}
template <typename Key>
typename Multiset<Key>::size_type Multiset<Key>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename Key>
void Multiset<Key>::clear() {
  while (!empty()) {
    erase(iterator(tree.getRoot(), &tree));
  }
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::insert(
    const value_type& value) {
  NodeMap<Key, int>* nodeMap = tree.search(value);
  if (nodeMap) {
    nodeMap->val.second++;
  } else {
    tree.insert(std::make_pair(value, 1));
  }
  return iterator(tree.search(value), &tree);
}

template <typename Key>
void Multiset<Key>::erase(iterator pos) {
  if (pos.getNodeMap() != nullptr) {
    NodeMap<Key, int>* nodeMap = pos.getNodeMap();
    if (nodeMap->val.second > 1) {
      nodeMap->val.second--;
    } else {
      tree.remove(nodeMap->val.first);
    }
  }
}

template <typename Key>
void Multiset<Key>::swap(Multiset& other) {
  std::swap(tree, other.tree);
}

template <typename Key>
void Multiset<Key>::merge(Multiset& other) {
  for (auto it = iterator(other.tree.getRoot(), &tree); it != other.end();) {
    auto next = it;
    insert(*it);
    ++next;

    other.erase(it);

    it = next;
  }
}

template <typename Key>
typename Multiset<Key>::size_type Multiset<Key>::count(const Key& key) const {
  size_type count = 0;
  NodeMap<Key, int>* nodeMap = tree.search(key);
  if (nodeMap != nullptr) {
    count = nodeMap->val.second;
  }

  return count;
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::find(const Key& key) {
  for (iterator it = begin(); it != end(); ++it) {
    if (*it == key) {
      return it;
    }
  }
  return end();
}

template <typename Key>
bool Multiset<Key>::contains(const Key& key) {
  return find(key) != end();
}

template <typename Key>
std::pair<typename Multiset<Key>::iterator, typename Multiset<Key>::iterator>
Multiset<Key>::equal_range(const Key& key) {
  auto lower = lower_bound(key);
  auto upper = upper_bound(key);
  return {lower, upper};
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::lower_bound(const Key& key) {
  for (auto it = begin(); it != end(); ++it) {
    if (!(*it < key)) {
      return it;
    }
  }
  return end();
}

template <typename Key>
typename Multiset<Key>::iterator Multiset<Key>::upper_bound(const Key& key) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it > key) {
      return it;
    }
  }
  return end();
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename Multiset<Key>::iterator, bool>>
Multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(std::make_pair(insert(std::forward<Args>(args)), true)),
   ...);
  return result;
}

}  // namespace s21
#endif