#ifndef S21_STACK
#define S21_STACK

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s) noexcept;
  stack &operator=(stack &&s) noexcept;
  ~stack();

  const_reference top() const;
  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(stack &other) noexcept;

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  struct node {
    value_type data_;
    node *ptr_prev_;

    node(value_type data) : data_(data), ptr_prev_(nullptr) {}
  };

  node *tail_;
  size_type count_;
};

}  // namespace s21
#include "s21_stack.cpp"
#endif  // S21_STACK
