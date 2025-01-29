#ifndef TREE_CPP
#define TREE_CPP
#include "s21_tree.h"
namespace s21 {

template <typename Key, typename T>
NodeMap<Key, T>::NodeMap(std::pair<Key, T> val)
    : val(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

template <typename Key, typename T>
NodeMap<Key, T>* NodeMap<Key, T>::uncle() {
  if (parent == nullptr || parent->parent == nullptr) {
    return nullptr;
  }
  if (parent->isOnLeft()) {
    return parent->parent->right;
  } else {
    return parent->parent->left;
  }
}

template <typename Key, typename T>
bool NodeMap<Key, T>::isOnLeft() {
  return this == parent->left;
}

template <typename Key, typename T>
NodeMap<Key, T>* NodeMap<Key, T>::sibling() {
  if (parent == nullptr) {
    return nullptr;
  }
  if (isOnLeft()) {
    return parent->right;
  } else {
    return parent->left;
  }
}

template <typename Key, typename T>
bool NodeMap<Key, T>::hasRedChild() {
  return (left && left->color == RED) || (right && right->color == RED);
}
template <typename Key, typename T>
Tree<Key, T>::iterator::iterator(NodeMap<Key, T>* nodeMap) : current(nodeMap) {}

template <typename Key, typename T>
std::pair<const Key, T>& Tree<Key, T>::iterator::operator*() const {
  return current->val;
}

template <typename Key, typename T>
std::pair<const Key, T>* Tree<Key, T>::iterator::operator->() const {
  return &(current->val);
}

template <typename Key, typename T>
typename Tree<Key, T>::iterator& Tree<Key, T>::iterator::operator++() {
  // Реализуйте логику для перехода к следующему элементу
  return *this;
}

template <typename Key, typename T>
typename Tree<Key, T>::iterator Tree<Key, T>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename Key, typename T>
bool Tree<Key, T>::iterator::operator!=(const iterator& other) const {
  return !(*this == other);
}

// Реализация const_iterator
template <typename Key, typename T>
Tree<Key, T>::const_iterator::const_iterator(const NodeMap<Key, T>* nodeMap)
    : current(nodeMap) {}

template <typename Key, typename T>
const std::pair<const Key, T>& Tree<Key, T>::const_iterator::operator*() const {
  return current->val;
}

template <typename Key, typename T>
const std::pair<const Key, T>* Tree<Key, T>::const_iterator::operator->()
    const {
  return &(current->val);
}

template <typename Key, typename T>
typename Tree<Key, T>::const_iterator&
Tree<Key, T>::const_iterator::operator++() {
  // Реализуйте логику для перехода к следующему элементу
  return *this;
}

template <typename Key, typename T>
typename Tree<Key, T>::const_iterator Tree<Key, T>::const_iterator::operator++(
    int) {
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename T>
bool Tree<Key, T>::const_iterator::operator==(
    const const_iterator& other) const {
  return current == other.current;
}

template <typename Key, typename T>
bool Tree<Key, T>::const_iterator::operator!=(
    const const_iterator& other) const {
  return !(*this == other);
}

template <typename Key, typename T>
Tree<Key, T>::Tree() : root(nullptr) {}
template <typename Key, typename T>
Tree<Key, T>::Tree(const Tree& other) : root(nullptr) {
  if (other.root) {
    copyTree(root, other.root);
  }
}
template <typename Key, typename T>
Tree<Key, T>::Tree(Tree&& other) noexcept : root(other.root) {
  other.root = nullptr;
}
template <typename Key, typename T>
Tree<Key, T>& Tree<Key, T>::operator=(Tree&& other) noexcept {
  if (this != &other) {
    deleteTree(root);
    root = other.root;
    other.root = nullptr;
  }
  return *this;
}
template <typename Key, typename T>
inline Tree<Key, T>::~Tree() {
  deleteTree(root);
}
template <typename Key, typename T>
void Tree<Key, T>::copyTree(NodeMap<Key, T>*& thisRoot,
                            NodeMap<Key, T>* otherRoot) {
  if (!otherRoot) {
    thisRoot = nullptr;
    return;
  }

  thisRoot = new NodeMap<Key, T>(otherRoot->val);
  thisRoot->color = otherRoot->color;
  copyTree(thisRoot->left, otherRoot->left);
  copyTree(thisRoot->right, otherRoot->right);

  if (thisRoot->left) {
    thisRoot->left->parent = thisRoot;
  }
  if (thisRoot->right) {
    thisRoot->right->parent = thisRoot;
  }
}

template <typename Key, typename T>
void Tree<Key, T>::deleteTree(NodeMap<Key, T>* node) {
  if (node) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}
template <typename Key, typename T>
NodeMap<Key, T>* Tree<Key, T>::getRoot() const {
  return root;
}
template <typename Key, typename T>
NodeMap<Key, T>* Tree<Key, T>::predecessor(NodeMap<Key, T>* nodeMap) const {
  if (!nodeMap) return nullptr;

  if (nodeMap->left) {
    NodeMap<Key, T>* pred = nodeMap->left;
    while (pred->right) {
      pred = pred->right;
    }
    return pred;
  }

  NodeMap<Key, T>* current = nodeMap;
  NodeMap<Key, T>* parent = nodeMap->parent;
  while (parent && current == parent->left) {
    current = parent;
    parent = parent->parent;
  }
  return parent;
}
template <typename Key, typename T>
void Tree<Key, T>::leftRotate(NodeMap<Key, T>* x) {
  NodeMap<Key, T>* y = x->right;
  x->right = y->left;
  if (y->left != nullptr) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename Key, typename T>
void Tree<Key, T>::rightRotate(NodeMap<Key, T>* x) {
  NodeMap<Key, T>* y = x->left;
  x->left = y->right;
  if (y->right != nullptr) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

template <typename Key, typename T>
void Tree<Key, T>::swapColors(NodeMap<Key, T>* x1, NodeMap<Key, T>* x2) {
  COLOR temp = x1->color;
  x1->color = x2->color;
  x2->color = temp;
}

template <typename Key, typename T>
void Tree<Key, T>::swapValues(NodeMap<Key, T>* u, NodeMap<Key, T>* v) {
  std::swap(u->val, v->val);
}

template <typename Key, typename T>
void Tree<Key, T>::fixRedRed(NodeMap<Key, T>* x) {
  if (x == root) {
    x->color = BLACK;
    return;
  }
  NodeMap<Key, T>* parent = x->parent;
  NodeMap<Key, T>* grandparent = parent->parent;
  NodeMap<Key, T>* uncle = x->uncle();
  if (parent->color == BLACK) {
    return;
  }
  if (uncle != nullptr && uncle->color == RED) {
    parent->color = BLACK;
    uncle->color = BLACK;
    grandparent->color = RED;
    fixRedRed(grandparent);
  } else {
    if (parent->isOnLeft()) {
      if (x->isOnLeft()) {
        swapColors(parent, grandparent);
      } else {
        leftRotate(parent);
        swapColors(x, grandparent);
      }
      rightRotate(grandparent);
    } else {
      if (x->isOnLeft()) {
        rightRotate(parent);
        swapColors(x, grandparent);
      } else {
        swapColors(parent, grandparent);
      }
      leftRotate(grandparent);
    }
  }
}

template <typename Key, typename T>
NodeMap<Key, T>* Tree<Key, T>::successor(NodeMap<Key, T>* nodeMap) const {
  if (nodeMap->right != nullptr) {
    NodeMap<Key, T>* temp = nodeMap->right;
    while (temp->left != nullptr) {
      temp = temp->left;
    }
    return temp;
  }
  NodeMap<Key, T>* temp = nodeMap->parent;
  while (temp != nullptr && nodeMap == temp->right) {
    nodeMap = temp;
    temp = temp->parent;
  }
  return temp;
}

template <typename Key, typename T>
NodeMap<Key, T>* Tree<Key, T>::BSTreplace(NodeMap<Key, T>* x) {
  if (x->left != nullptr && x->right != nullptr) {
    return successor(x);
  }
  if (x->left != nullptr) {
    return x->left;
  } else {
    return x->right;
  }
}

template <typename Key, typename T>
void Tree<Key, T>::deleteNodeMap(NodeMap<Key, T>* v) {
  if (v == nullptr) {
    std::cout << "NULL" << std::endl;
  }
  NodeMap<Key, T>* u = BSTreplace(v);  // Узел для замены
  bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
  NodeMap<Key, T>* parent = v->parent;

  // Случай 1: Удаляемый узел не имеет детей
  if (u == nullptr) {
    if (v == root) {
      root = nullptr;
    } else {
      if (uvBlack) {
        fixDoubleBlack(v);
      } else {
        if (v->sibling() != nullptr) {
          v->sibling()->color = RED;
        }
      }

      if (v->isOnLeft()) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    }
    delete v;
    return;
  }

  if (v->left == nullptr || v->right == nullptr) {
    NodeMap<Key, T>* child = (v->left != nullptr) ? v->left : v->right;
    if (v == root) {
      root = child;
    } else {
      if (v->isOnLeft()) {
        parent->left = child;
      } else {
        parent->right = child;
      }
      child->parent = parent;
      if (uvBlack) {
        fixDoubleBlack(child);
      } else {
        child->color = BLACK;
      }
    }
    delete v;
    return;
  }

  swapValues(u, v);

  deleteNodeMap(u);
}
template <typename Key, typename T>
void Tree<Key, T>::fixDoubleBlack(NodeMap<Key, T>* x) {
  if (x == root) {
    return;
  }

  NodeMap<Key, T>* sibling = x->sibling();
  NodeMap<Key, T>* parent = x->parent;

  if (sibling == nullptr) {
    fixDoubleBlack(parent);
  } else {
    if (sibling->color == RED) {
      parent->color = RED;
      sibling->color = BLACK;
      if (sibling->isOnLeft()) {
        rightRotate(parent);
      } else {
        leftRotate(parent);
      }
      sibling = parent->sibling();
    }

    if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
        (sibling->right == nullptr || sibling->right->color == BLACK)) {
      sibling->color = RED;
      if (parent->color == BLACK) {
        fixDoubleBlack(parent);
      } else {
        parent->color = BLACK;
      }
    } else {
      if (sibling->isOnLeft()) {
        if (sibling->left == nullptr || sibling->left->color == BLACK) {
          sibling->right->color = BLACK;
          sibling->color = RED;
          leftRotate(sibling);
          sibling = parent->left;
        }
        sibling->color = parent->color;
        parent->color = BLACK;
        if (sibling->left != nullptr) {
          sibling->left->color = BLACK;
        }
        rightRotate(parent);
      } else {
        if (sibling->right == nullptr || sibling->right->color == BLACK) {
          sibling->left->color = BLACK;
          sibling->color = RED;
          rightRotate(sibling);
          sibling = parent->right;
        }
        sibling->color = parent->color;
        parent->color = BLACK;
        if (sibling->right != nullptr) {
          sibling->right->color = BLACK;
        }
        leftRotate(parent);
      }
    }
  }
}

template <typename Key, typename T>
void Tree<Key, T>::levelOrder(NodeMap<Key, T>* x) {
  if (x == nullptr) return;
  std::queue<NodeMap<Key, T>*> q;
  q.push(x);
  while (!q.empty()) {
    NodeMap<Key, T>* nodeMap = q.front();
    q.pop();
    std::cout << nodeMap->val.first << " ";
    if (nodeMap->left != nullptr) {
      q.push(nodeMap->left);
    }
    if (nodeMap->right != nullptr) {
      q.push(nodeMap->right);
    }
  }
}

template <typename Key, typename T>
NodeMap<Key, T>* Tree<Key, T>::insert(const std::pair<Key, T>& value) {
  NodeMap<Key, T>* nodeMap =
      new NodeMap<Key, T>(value);  // Создаем новый узел с значением
  if (root == nullptr) {
    root = nodeMap;
    root->color = BLACK;

  } else {
    NodeMap<Key, T>* temp = root;
    NodeMap<Key, T>* parent = nullptr;
    while (temp != nullptr) {
      parent = temp;
      if (nodeMap->val.first < temp->val.first) {
        temp = temp->left;
      } else if (nodeMap->val.first > temp->val.first) {
        temp = temp->right;
      } else {
        temp->val.second = value.second;
        delete nodeMap;  // Удаляем временно созданный узел, так как он больше
                         // не нужен

        return temp;
      }
    }
    nodeMap->parent = parent;
    if (nodeMap->val.first < parent->val.first) {
      parent->left = nodeMap;

    } else {
      parent->right = nodeMap;
    }
    fixRedRed(nodeMap);
  }
  return nodeMap;
}
template <typename Key, typename T>
void Tree<Key, T>::printTreeStructure(NodeMap<Key, T>* nodeMap, int level) {
  if (nodeMap == nullptr) return;
  printTreeStructure(nodeMap->right, level + 1);
  std::cout << std::string(level * 4, ' ') << nodeMap->val.first << std::endl;
  printTreeStructure(nodeMap->left, level + 1);
}
template <typename Key, typename T>
NodeMap<Key, T>* Tree<Key, T>::search(const Key& key) const {
  NodeMap<Key, T>* temp = root;
  while (temp != nullptr) {
    if (key == temp->val.first) {
      return temp;
    } else if (key < temp->val.first) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }
  return nullptr;
}

template <typename Key, typename T>
void Tree<Key, T>::remove(Key key) {
  NodeMap<Key, T>* nodeMap = search(key);
  if (nodeMap != nullptr) {
    deleteNodeMap(nodeMap);
  }
}

template <typename Key, typename T>
void Tree<Key, T>::printLevelOrder() {
  levelOrder(root);
}

template <typename Key, typename T>
void Tree<Key, T>::inOrderTraversal(NodeMap<Key, T>* nodeMap) {
  if (nodeMap == nullptr) return;
  inOrderTraversal(nodeMap->left);
  std::cout << nodeMap->val.first << " ";
  inOrderTraversal(nodeMap->right);
}
}  // namespace s21
#endif