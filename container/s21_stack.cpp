#ifndef STACK_CPP
#define STACK_CPP
#include "s21_stack.h"
namespace s21 {

template <typename T>
stack<T>::stack() : tail_(nullptr), count_(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : tail_(nullptr), count_(0) {
  for (const value_type &item : items) {
    push(item);
  }
}

template <typename T>
stack<T>::stack(const stack<T> &s) : tail_(nullptr), count_(0) {
  node *current = s.tail_;
  stack<T> temp_stack;

  while (current != nullptr) {
    temp_stack.push(current->data_);
    current = current->ptr_prev_;
  }

  while (!temp_stack.empty()) {
    push(temp_stack.top());
    temp_stack.pop();
  }
}

template <typename T>
stack<T>::stack(stack<T> &&s) noexcept : tail_(s.tail_), count_(s.count_) {
  s.tail_ = nullptr;
  s.count_ = 0;
}

template <typename T>
stack<T> &stack<T>::operator=(stack<T> &&s) noexcept {
  if (this != &s) {
    while (!empty()) {
      pop();
    }
    tail_ = s.tail_;
    count_ = s.count_;
    s.tail_ = nullptr;
    s.count_ = 0;
  }
  return *this;
}

template <typename T>
stack<T>::~stack() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
bool stack<T>::empty() const {
  return count_ == 0;
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return count_;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (empty()) {
    throw std::logic_error("Cannot get top from an empty stack");
  }
  return tail_->data_;
}

template <typename T>
void stack<T>::push(const_reference value) {
  node *temp = new node(value);
  temp->ptr_prev_ = tail_;
  tail_ = temp;
  count_++;
}

template <typename T>
void stack<T>::pop() {
  if (empty()) {
    throw std::logic_error("Cannot pop from an empty stack");
  }
  node *temp = tail_->ptr_prev_;
  delete tail_;
  tail_ = temp;
  count_--;
}

template <typename T>
void stack<T>::swap(stack &other) noexcept {
  std::swap(tail_, other.tail_);
  std::swap(count_, other.count_);
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  (push(args), ...);
}

}  // namespace s21
#endif