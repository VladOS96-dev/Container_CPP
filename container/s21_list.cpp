#ifndef LIST_CPP
#define LIST_CPP
#include "s21_list.h"
namespace s21 {

template <class T, class Allocator>
s21::list<T, Allocator>::Node::Node() : next_(nullptr), prev_(nullptr) {}

template <class T, class Allocator>
s21::list<T, Allocator>::Node::~Node() {
  next_ = nullptr;
  prev_ = nullptr;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::Node*
s21::list<T, Allocator>::allocate_node() {
  Node* node = nullptr;
  node = node_allocator::allocate(allocator_, 1);
  node_allocator::construct(allocator_, node);
  return node;
}

template <class T, class Allocator>
void s21::list<T, Allocator>::deallocate_node(Node* ptr) noexcept {
  node_allocator::destroy(allocator_, ptr);
  node_allocator::deallocate(allocator_, ptr, 1);
}

template <class T, class Allocator>
s21::list<T, Allocator>::list() : allocator_() {
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
  fake_node_ = nullptr;
}

template <class T, class Allocator>
s21::list<T, Allocator>::list(size_type count) : list() {
  while (count > 0) {
    push_back(value_type());
    --count;
  }
}

template <class T, class Allocator>
s21::list<T, Allocator>::list(std::initializer_list<T> init) : list() {
  for (auto iter = init.begin(); iter != init.end(); ++iter) {
    push_back(*iter);
  }
}

template <class T, class Allocator>
s21::list<T, Allocator>::list(const list& other) : list() {
  Node* tmp = other.head_;
  while (tmp != other.fake_node_) {
    push_back(tmp->value_);
    tmp = tmp->next_;
  }
}

template <class T, class Allocator>
s21::list<T, Allocator>::list(list&& other) {
  size_ = other.size_;
  head_ = other.head_;
  tail_ = other.tail_;
  fake_node_ = other.fake_node_;
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.fake_node_ = nullptr;
}

template <class T, class Allocator>
s21::list<T, Allocator>& s21::list<T, Allocator>::operator=(
    const list_type& other) {
  if (this != &other) {
    clear();
    Node* tmp = other.head_;
    while (tmp != other.fake_node_) {
      push_back(tmp->value_);
      tmp = tmp->next_;
    }
  }
  return *this;
}

template <class T, class Allocator>
s21::list<T, Allocator>& s21::list<T, Allocator>::operator=(
    list_type&& other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    fake_node_ = other.fake_node_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.fake_node_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::reference s21::list<T, Allocator>::front() {
  return head_->value_;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::const_reference
s21::list<T, Allocator>::front() const {
  return head_->value_;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::reference s21::list<T, Allocator>::back() {
  return tail_->value_;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::const_reference
s21::list<T, Allocator>::back() const {
  return tail_->value_;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::iterator
s21::list<T, Allocator>::begin() noexcept {
  return ListIterator(head_);
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::const_iterator
s21::list<T, Allocator>::begin() const noexcept {
  return ListConstIterator(head_);
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::const_iterator
s21::list<T, Allocator>::cbegin() const noexcept {
  return ListConstIterator(head_);
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::iterator
s21::list<T, Allocator>::end() noexcept {
  return ListIterator(fake_node_);
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::const_iterator s21::list<T, Allocator>::end()
    const noexcept {
  return ListConstIterator(fake_node_);
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::const_iterator s21::list<T, Allocator>::cend()
    const noexcept {
  return ListConstIterator(fake_node_);
}

template <class T, class Allocator>
bool s21::list<T, Allocator>::empty() const noexcept {
  return size_ == 0;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::size_type s21::list<T, Allocator>::size()
    const noexcept {
  return size_;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::size_type s21::list<T, Allocator>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <class T, class Allocator>
void s21::list<T, Allocator>::clear() noexcept {
  if (size_ == 0) {
    return;
  }
  while (size_ > 0) {
    pop_back();
  }
  deallocate_node(fake_node_);
  head_ = nullptr;
  tail_ = nullptr;
  fake_node_ = nullptr;
  size_ = 0;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::iterator s21::list<T, Allocator>::insert(
    const_iterator pos, const T& value) {
  ListIterator it = begin();
  if (pos != begin() && pos != end()) {
    Node* new_node = allocate_node();
    new_node->value_ = value;
    while (it != pos) {
      ++it;
    }
    Node* cur = it.node_;
    Node* back = cur->prev_;
    cur->prev_ = new_node;
    back->next_ = new_node;
    new_node->next_ = cur;
    new_node->prev_ = back;
    ++size_;
    --it;
  } else if (pos == begin()) {
    push_front(value);
    it = begin();
  } else {
    push_back(value);
    it = end();
  }
  return it;
}

template <class T, class Allocator>
typename s21::list<T, Allocator>::iterator s21::list<T, Allocator>::erase(
    const_iterator pos) {
  ListIterator it = begin();
  if (pos != begin() && pos != tail_) {
    while (it.node_ != pos.node_) {
      ++it;
    }
    Node* cur = it.node_;
    Node* back = cur->prev_;
    Node* next = cur->next_;
    back->next_ = next;
    next->prev_ = back;
    it.node_ = next;
    deallocate_node(cur);
    cur = nullptr;
    --size_;
  } else if (pos == begin()) {
    pop_front();
    it = begin();
  } else {
    pop_back();
    it = end();
  }
  return it;
}

template <class T, class Allocator>
void s21::list<T, Allocator>::push_back(const T& value) {
  Node* new_node = allocate_node();
  new_node->value_ = value;
  if (head_) {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = tail_->next_;
    tail_->next_ = fake_node_;
    fake_node_->prev_ = tail_;
  } else {
    head_ = new_node;
    tail_ = new_node;
    fake_node_ = allocate_node();
    head_->prev_ = fake_node_;
    tail_->next_ = fake_node_;
    fake_node_->next_ = head_;
    fake_node_->prev_ = tail_;
  }
  ++size_;
}

template <class T, class Allocator>
void s21::list<T, Allocator>::pop_back() {
  Node* tmp = tail_;
  tail_ = tail_->prev_;
  tail_->next_ = fake_node_;
  fake_node_->prev_ = tail_;
  deallocate_node(tmp);
  --size_;
}

template <class T, class Allocator>
void s21::list<T, Allocator>::push_front(const T& value) {
  Node* new_node = allocate_node();
  new_node->value_ = value;
  if (head_) {
    head_->prev_ = new_node;
    new_node->next_ = head_;
    head_ = head_->prev_;
    head_->prev_ = fake_node_;
    fake_node_->next_ = head_;
  } else {
    head_ = new_node;
    tail_ = new_node;
    fake_node_ = allocate_node();
    head_->prev_ = fake_node_;
    tail_->next_ = fake_node_;
    fake_node_->next_ = head_;
    fake_node_->prev_ = tail_;
  }
  ++size_;
}

template <class T, class Allocator>
void s21::list<T, Allocator>::pop_front() {
  Node* tmp = head_;
  head_ = head_->next_;
  head_->prev_ = fake_node_;
  fake_node_->next_ = head_;
  deallocate_node(tmp);
  --size_;
}

template <class T, class Allocator>
void s21::list<T, Allocator>::swap(list& other) noexcept {
  if (this != &other) {
    std::swap(size_, other.size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(fake_node_, other.fake_node_);
  }
}

template <class T, class Allocator>
void s21::list<T, Allocator>::merge(list& other) {
  ListConstIterator it_this = cbegin();
  ListConstIterator it_other = other.cbegin();
  while (it_this != cend() && it_other != other.cend()) {
    if (it_other.node_->value_ < it_this.node_->value_) {
      insert(it_this, *it_other);
      ++it_other;
    } else {
      ++it_this;
    }
  }
  while (it_other != other.cend()) {
    insert(it_this, *it_other);
    ++it_other;
  }
  other.clear();
}

template <class T, class Allocator>
void s21::list<T, Allocator>::splice(const_iterator pos, list& other) {
  for (iterator it = other.begin(); it != other.end(); ++it) {
    insert(pos, *it);
  }
}

template <class T, class Allocator>
void s21::list<T, Allocator>::reverse() noexcept {
  if (size_ > 0) {
    ListIterator lhs = begin();
    ListIterator rhs = --end();
    for (size_type i = 0; i < size() / 2; ++i) {
      std::swap(lhs.node_->value_, rhs.node_->value_);
      ++lhs;
      --rhs;
    }
  }
}

template <class T, class Allocator>
void s21::list<T, Allocator>::unique() {
  ListIterator begin_it = begin();
  ListIterator end_it = end();
  ListIterator back_it = begin_it;
  ++begin_it;
  while (begin_it != end_it) {
    if (*begin_it == *back_it) {
      ListConstIterator removed{begin_it.node_};
      erase(removed);
      begin_it = back_it;
    } else {
      ++back_it;
    }
    ++begin_it;
  }
}

template <class T, class Allocator>
void s21::list<T, Allocator>::sort() {
  quick_sort(begin(), --end(), size_);
}

template <class T, class Allocator>
void s21::list<T, Allocator>::quick_sort(ListIterator first, ListIterator last,
                                         size_type size) {
  if (first != last && size > 1) {
    ListIterator pivot_it = first;
    ListIterator lhs = first;
    ListIterator rhs = last;
    size_type shift = 0;
    ++pivot_it;
    value_type pivot = *pivot_it;
    shift = 0;
    while (true) {
      while (*lhs < pivot && lhs != rhs) {
        ++lhs;
        ++shift;
      }
      while (*rhs >= pivot && rhs != lhs) --rhs;
      if (lhs == rhs) {
        break;
      }
      std::swap(lhs.node_->value_, rhs.node_->value_);
    }
    ListIterator next_it = lhs;
    size_type next_size_lhs = shift;
    quick_sort(first, --next_it, next_size_lhs);
    size_type next_size_rhs = size - shift;
    quick_sort(next_it, last, next_size_rhs);
  }
}

template <class T, class Allocator>
template <class... Args>
typename s21::list<T, Allocator>::iterator s21::list<T, Allocator>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator it{pos.node_};
  for (const auto& arg : {args...}) {
    it = insert(const_iterator{it.node_}, arg);
  }
  return it;
}

template <class T, class Allocator>
template <class... Args>
void s21::list<T, Allocator>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

template <class T, class Allocator>
template <class... Args>
void s21::list<T, Allocator>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_front(arg);
  }
}
}  // namespace s21
#endif