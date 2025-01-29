#ifndef QUEUE_CPP
#define QUEUE_CPP
#include "s21_queue.h"
namespace s21 {

template <typename T>
s21::queue<T>::queue() : head_(nullptr), tail_(nullptr), count_(0) {}

template <typename T>
s21::queue<T>::queue(const std::initializer_list<value_type> &items)
    : head_(nullptr), tail_(nullptr), count_(0) {
  for (const value_type &i : items) {
    push(i);
  }
}

template <typename T>
s21::queue<T>::queue(const queue &q)
    : head_(nullptr), tail_(nullptr), count_(0) {
  for (auto i = q.head_; i != nullptr; i = i->ptr_prev_) {
    push(i->data_);
  }
}

template <typename T>
s21::queue<T>::queue(queue &&q)
    : head_(q.head_), tail_(q.tail_), count_(q.count_) {
  q.head_ = nullptr;
  q.tail_ = nullptr;
  q.count_ = 0;
}

template <typename T>
s21::queue<T> &s21::queue<T>::operator=(queue &&q) {
  if (this != &q) {
    while (!empty()) {
      pop();
    }
    head_ = q.head_;
    tail_ = q.tail_;
    count_ = q.count_;
    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.count_ = 0;
  }
  return *this;
}

template <typename T>
s21::queue<T>::~queue() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
bool s21::queue<T>::empty() const {
  return head_ == nullptr;
}

template <typename T>
typename s21::queue<T>::size_type s21::queue<T>::size() const {
  return count_;
}

template <typename T>
typename s21::queue<T>::const_reference s21::queue<T>::front() {
  if (empty()) {
    throw std::logic_error("Cannot get front from an empty queue");
  }
  return head_->data_;
}

template <typename T>
typename s21::queue<T>::const_reference s21::queue<T>::back() {
  if (empty()) {
    throw std::logic_error("Cannot get back from an empty queue");
  }
  return tail_->data_;
}

template <typename T>
void s21::queue<T>::push(const_reference value) {
  node *temp = new node(value);
  if (!head_) {
    head_ = temp;
    tail_ = temp;
  } else {
    tail_->ptr_prev_ = temp;
    tail_ = temp;
  }
  count_++;
}

template <typename T>
void s21::queue<T>::pop() {
  if (empty()) {
    throw std::logic_error("Cannot pop from an empty queue");
  }
  node *temp = head_;
  head_ = head_->ptr_prev_;
  delete temp;
  count_--;
}

template <typename T>
void s21::queue<T>::swap(queue &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(count_, other.count_);
}

template <typename T>
template <typename... Args>
void s21::queue<T>::insert_many_back(Args &&...args) {
  (push(args), ...);
}
}  // namespace s21
#endif