#pragma once
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "s21_set_iterator.h"
#include "s21_tree.h"
namespace s21 {

template <typename Key>
class Set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  using iterator = SetIterator<Key>;
  using const_iterator = SetConstIterator<Key>;

  Set();
  Set(std::initializer_list<value_type> const& items);
  Set(const Set& s);
  Set(Set&& s) noexcept;
  ~Set();

  Set& operator=(Set&& s) noexcept;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(Set& other);
  void merge(Set& other);

  iterator find(const Key& key);
  bool contains(const Key& key) const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  Tree<Key, bool> tree;
};

}  // namespace s21
#include "s21_set.cpp"