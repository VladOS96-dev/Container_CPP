#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <iostream>

#include "s21_containers.h"

namespace s21 {
template <class T, class Allocator = std::allocator<T> >
class list {
 public:
  struct Node;
  class ListIterator;
  class ListConstIterator;
  class ListIterator {
    friend s21::list<T, Allocator>;

   public:
    using node_type = Node;
    ListIterator() {}
    ListIterator(node_type* node) : node_(node) {}

    const T& operator*() const { return node_->value_; }
    ListIterator& operator++() {
      node_ = node_->next_;
      return *this;
    }

    ListIterator& operator--() {
      node_ = node_->prev_;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    ListIterator operator--(int) {
      ListIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const ListIterator& other) const noexcept {
      return other.node_ == node_;
    }

    bool operator!=(const ListIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      return other.node_ == node_;
    }
    bool operator!=(const ListConstIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    ~ListIterator() { node_ = nullptr; }

   private:
    Node* node_;
  };

  class ListConstIterator {
    friend s21::list<T, Allocator>;

   public:
    using node_type = Node;

    ListConstIterator() {}
    explicit ListConstIterator(node_type* node) { node_ = node; }

    const T& operator*() const { return node_->value_; }

    ListConstIterator& operator++() {
      node_ = node_->next_;
      return *this;
    }

    ListConstIterator& operator--() {
      node_ = node_->prev_;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    ListConstIterator operator--(int) {
      ListConstIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      return other.node_ == node_;
    }

    bool operator!=(const ListConstIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    bool operator==(const ListIterator& other) const noexcept {
      return other.node_ == node_;
    }
    bool operator!=(const ListIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    ~ListConstIterator() { node_ = nullptr; }

   private:
    Node* node_;
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;
  using allocator_type = Allocator;
  using rebind_allocator_type =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
  /**
   * rebind_allocator_type - новый тип аллокатора, который переопределяет
   * тип выделения памяти для объектов типа Node.
   *
   * Он использует стандартный шаблонный класс std::allocator_traits для
   * получения типа аллокатора Allocator, а затем вызывает его метод
   * rebind_alloc для создания нового типа аллокатора, который может выделять
   * память для объектов типа Node.
   */
  using node_allocator =
      typename std::allocator_traits<Allocator>::template rebind_traits<Node>;
  /**
   * Тип node_allocator - переопределение типа Allocator для выделения
   * памяти для объектов типа Node.
   *
   * std::allocator_traits - утилита, которая предоставляет типы и функции
   * для работы с аллокаторами. rebind_traits - это функция-член
   * allocator_traits, которая создает новый аллокатор, переопределяя тип
   * выделяемых объектов на указанный тип.
   */
  using list_type = s21::list<value_type, allocator_type>;

  list();
  list(size_type count);
  list(std::initializer_list<T> init);
  list(const list& other);
  list(list&& other);
  ~list() { clear(); }

  list& operator=(const list_type& other);
  list& operator=(list_type&& other) noexcept;

  reference front();  // Reference to the first element
  const_reference front() const;
  reference back();  // Reference to the last element
  const_reference back() const;

  iterator begin() noexcept;  // Iterator to the first element
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;

  iterator end() noexcept;  // Iterator to the element following the last
                            // element
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  bool empty()
      const noexcept;  // true if the container is empty, false otherwise
  size_type size() const noexcept;  // The number of elements in the container
  size_type max_size() const noexcept;  // Maximum number of elements

  void clear() noexcept;
  iterator insert(const_iterator pos,
                  const T& value);     // Inserts value before pos
  iterator erase(const_iterator pos);  // Removes the element at pos

  void push_back(
      const T& value);  // The new element is initialized as a copy of value
  void pop_back();
  void push_front(const T& value);
  void pop_front();
  void swap(list& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse() noexcept;
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <class... Args>
  void insert_many_back(Args&&... args);

  template <class... Args>
  void insert_many_front(Args&&... args);

  struct Node {
    Node* next_;
    Node* prev_;
    T value_;

    Node();
    ~Node();
  };

 private:
  Node* head_;
  Node* tail_;
  Node* fake_node_;
  size_type size_;
  rebind_allocator_type allocator_;

  Node* allocate_node();
  void deallocate_node(Node* ptr) noexcept;
  void quick_sort(iterator first, iterator last, size_type size);
};
}  // namespace s21

#include "s21_list.cpp"
#endif  // 21_LIST_H_