#pragma once
#include <iostream>
#include <queue>
#include <utility>

#include "s21_queue.h"
namespace s21 {

enum COLOR { RED, BLACK };

template <typename Key, typename T>
class NodeMap {
 public:
  std::pair<Key, T> val;
  COLOR color;
  NodeMap *left, *right, *parent;
  NodeMap(std::pair<Key, T> val);

  NodeMap* uncle();
  bool isOnLeft();
  NodeMap* sibling();
  bool hasRedChild();
};

template <typename Key, typename T>
class Tree {
 public:
  Tree();
  Tree(const Tree& other);
  Tree(Tree&& other) noexcept;
  Tree& operator=(Tree&& other) noexcept;
  ~Tree();
  NodeMap<Key, T>* getRoot() const;
  NodeMap<Key, T>* search(const Key& key) const;
  NodeMap<Key, T>* insert(const std::pair<Key, T>& value);
  NodeMap<Key, T>* successor(NodeMap<Key, T>* nodeMap) const;
  void remove(Key key);
  void printLevelOrder();

  void inOrderTraversal(NodeMap<Key, T>* nodeMap);

  class iterator;
  class const_iterator;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  NodeMap<Key, T>* predecessor(NodeMap<Key, T>* nodeMap) const;

  void printTreeStructure(NodeMap<Key, T>* nodeMap, int level = 0);
  class iterator {
   public:
    iterator(NodeMap<Key, T>* nodeMap);

    std::pair<const Key, T>& operator*() const;
    std::pair<const Key, T>* operator->() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

   private:
    NodeMap<Key, T>* current;
  };

  class const_iterator {
   public:
    const_iterator(const NodeMap<Key, T>* nodeMap);

    const std::pair<const Key, T>& operator*() const;
    const std::pair<const Key, T>* operator->() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;

   private:
    const NodeMap<Key, T>* current;
  };

 private:
  NodeMap<Key, T>* root;
  void leftRotate(NodeMap<Key, T>* x);
  void rightRotate(NodeMap<Key, T>* x);
  void swapColors(NodeMap<Key, T>* x1, NodeMap<Key, T>* x2);
  void swapValues(NodeMap<Key, T>* u, NodeMap<Key, T>* v);
  void fixRedRed(NodeMap<Key, T>* x);
  NodeMap<Key, T>* BSTreplace(NodeMap<Key, T>* x);
  void deleteNodeMap(NodeMap<Key, T>* v);
  void fixDoubleBlack(NodeMap<Key, T>* x);
  void levelOrder(NodeMap<Key, T>* x);
  void copyTree(NodeMap<Key, T>*& thisRoot, NodeMap<Key, T>* otherRoot);
  void deleteTree(NodeMap<Key, T>* node);
};

}  // namespace s21
#include "s21_tree.cpp"