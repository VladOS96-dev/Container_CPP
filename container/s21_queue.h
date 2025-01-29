#ifndef S21_QUEUE
#define S21_QUEUE

#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  queue &operator=(queue &&q);
  ~queue();

  const_reference front();
  const_reference back();
  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  struct node {
    value_type data_;
    node *ptr_prev_;

    node(value_type data) : data_(data), ptr_prev_(nullptr) {}
  };

  node *head_;
  node *tail_;
  size_type count_;
};

}  // namespace s21
#include "s21_queue.cpp"
#endif
