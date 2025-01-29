#pragma once
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <utility>
#include <vector>

#include "s21_multiset_iterator.h"
#include "s21_tree.h"
namespace s21 {

template <typename Key>
class Multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  using iterator = MultisetIterator<Key>;
  using const_iterator = MultisetConstIterator<Key>;

  Multiset();
  Multiset(std::initializer_list<value_type> const& items);
  Multiset(const Multiset& ms);
  Multiset(Multiset&& ms) noexcept;
  ~Multiset();

  Multiset& operator=(Multiset&& ms) noexcept;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(Multiset& other);
  void merge(Multiset& other);

  size_type count(const Key& key) const;
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  Tree<Key, int> tree;
};

}  // namespace s21
#include "s21_multiset.cpp"