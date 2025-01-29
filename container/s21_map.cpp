#ifndef MAP_CPP
#define MAP_CPP
#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
NodeMap<Key, T>* Map<Key, T>::findNodeMapByKey(const Key& key) {
  return tree->search(key);
}

template <typename Key, typename T>
const NodeMap<Key, T>* Map<Key, T>::findNodeMapByKey(const Key& key) const {
  return tree->search(key);
}

template <typename Key, typename T>
Map<Key, T>::Map() : tree(new Tree<Key, T>()), cnt(0) {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items) : Map() {
  for (const auto& item : items) {
    insert(item.first, item.second);
  }
  cnt = items.size();
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& m) : cnt(m.cnt) {
  if (m.tree != nullptr) {
    tree = new Tree<Key, T>(*m.tree);

  } else {
    tree = new Tree<Key, T>();
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map&& m) noexcept : tree(m.tree), cnt(m.cnt) {
  m.tree = nullptr;
  m.cnt = 0;
}
template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear();
}

template <typename Key, typename T>
Map<Key, T>& Map<Key, T>::operator=(Map&& m) noexcept {
  if (this != &m) {
    // Clear current resources
    clear();

    // Transfer ownership
    tree = m.tree;
    cnt = m.cnt;

    // Nullify the source
    m.tree = nullptr;
    m.cnt = 0;
  }
  return *this;
}

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
  NodeMap<Key, T>* NodeMap = findNodeMapByKey(key);
  if (NodeMap != nullptr) {
    return NodeMap->val.second;
  }
  throw std::out_of_range("Key not found");
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
  NodeMap<Key, T>* NodeMap = findNodeMapByKey(key);
  if (NodeMap == nullptr) {
    NodeMap = tree->insert(std::make_pair(key, T()));
    cnt++;
  }
  return NodeMap->val.second;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::count(const Key& key) const {
  return (findNodeMapByKey(key) != nullptr) ? 1 : 0;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const {
  return cnt;
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  erase(pos->first);
}

template <typename Key, typename T>
void Map<Key, T>::erase(const Key& key) {
  if (findNodeMapByKey(key) != nullptr) {
    tree->remove(key);

    cnt--;
  }
}

template <typename Key, typename T>
bool Map<Key, T>::empty() const {
  bool flag = true;
  if (tree != nullptr) {
    if (tree->getRoot() != nullptr) {
      flag = false;
    }
  }
  return flag;
}

template <typename Key, typename T>
void Map<Key, T>::update(const Key& key, const T& value) {
  NodeMap<Key, T>* temp = findNodeMapByKey(key);
  if (temp != nullptr) {
    temp->val.second = value;
  }
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  if (tree != nullptr) {
    delete tree;
    tree = nullptr;
    cnt = 0;
  }
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  NodeMap<Key, T>* root = tree->getRoot();
  if (root == nullptr) {
    return iterator(nullptr);
  }
  NodeMap<Key, T>* current = root;
  while (current->left != nullptr) {
    current = current->left;
  }
  return iterator(current);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(nullptr);
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
  std::swap(tree, other.tree);
  std::swap(cnt, other.cnt);
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(it->first, it->second);
  }
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) const {
  return findNodeMapByKey(key) != nullptr;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type& value) {
  NodeMap<Key, T>* nodeMap = findNodeMapByKey(value.first);
  if (nodeMap == nullptr) {
    nodeMap = tree->insert(value);
    cnt++;
    return std::make_pair(iterator(nodeMap), true);
  }
  return std::make_pair(iterator(nodeMap), false);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key& key, const T& value) {
  NodeMap<Key, T>* nodeMap = findNodeMapByKey(key);
  if (nodeMap == nullptr) {
    nodeMap = tree->insert(std::make_pair(key, value));
    cnt++;
  } else {
    nodeMap->val.second = value;
  }
  return std::make_pair(iterator(nodeMap), true);
}
template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  NodeMap<Key, T>* nodeMap = findNodeMapByKey(key);
  if (nodeMap == nullptr) {
    nodeMap = tree->insert(std::make_pair(key, obj));
    cnt++;
    return std::make_pair(iterator(nodeMap), true);
  } else {
    nodeMap->val.second = obj;
    return std::make_pair(iterator(nodeMap), false);
  }
}

template <typename Key, typename T>
template <typename... Args>
inline std::vector<std::pair<typename Map<Key, T>::iterator, bool>>
Map<Key, T>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}
// Explicit instantiation for a particular type combination
template class Map<int, int>;

}  // namespace s21
#endif