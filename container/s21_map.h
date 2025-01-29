#pragma once
#include <cstddef>  // for size_t
#include <initializer_list>
#include <iostream>
#include <utility>  // for std::pair
#include <vector>

#include "s21_map_Iterator.h"
#include "s21_tree.h"

namespace s21 {

template <typename Key, typename T>
class Map {
 private:
  Tree<Key, T>* tree;
  size_t cnt;

  NodeMap<Key, T>* findNodeMapByKey(const Key& key);
  const NodeMap<Key, T>* findNodeMapByKey(const Key& key) const;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator<Key, T>;
  using const_iterator = MapConstIterator<Key, T>;
  using size_type = size_t;

  Map();
  Map(std::initializer_list<value_type> const& items);
  Map(const Map& m);      // Copy constructor
  Map(Map&& m) noexcept;  // Move constructor
  ~Map();
  Map& operator=(Map&& m) noexcept;

  T& at(const Key& key);
  T& operator[](const Key& key);

  size_type count(const Key& key) const;
  size_type size() const;
  void erase(iterator pos);
  void erase(const Key& key);
  bool empty() const;
  void update(const Key& key, const T& value);
  void clear();
  iterator begin();
  iterator end();
  void swap(Map& other);
  void merge(Map& other);
  bool contains(const Key& key) const;
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& value);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  template <typename... Args>
  std::vector<std::pair<typename Map<Key, T>::iterator, bool>> insert_many(
      Args&&... args);
};

}  // namespace s21
#include "s21_map.cpp"