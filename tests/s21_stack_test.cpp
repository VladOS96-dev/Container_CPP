#include "s21_main_test.h"

TEST(stack, initial_conditions) {
  s21::stack<int> int_stack;
  s21::stack<double> double_stack;
  s21::stack<std::string> string_stack;

  EXPECT_EQ(int_stack.size(), 0U);
  EXPECT_THROW(int_stack.top(), std::logic_error);
  EXPECT_THROW(int_stack.pop(), std::logic_error);

  EXPECT_EQ(double_stack.size(), 0U);
  EXPECT_THROW(double_stack.top(), std::logic_error);
  EXPECT_THROW(double_stack.pop(), std::logic_error);

  EXPECT_EQ(string_stack.size(), 0U);
  EXPECT_THROW(string_stack.top(), std::logic_error);
  EXPECT_THROW(string_stack.pop(), std::logic_error);
}

TEST(stack, push_and_top) {
  s21::stack<int> int_stack{3, 6, 9, 12};
  s21::stack<double> double_stack{3.3, 6.6, 9.9};
  s21::stack<std::string> string_stack{"Start", "Middle", "End"};

  EXPECT_EQ(int_stack.size(), 4U);
  EXPECT_EQ(int_stack.top(), 12);

  EXPECT_EQ(double_stack.size(), 3U);
  EXPECT_EQ(double_stack.top(), 9.9);

  EXPECT_EQ(string_stack.size(), 3U);
  EXPECT_EQ(string_stack.top(), "End");
}

TEST(stack, copy_constructor) {
  s21::stack<int> original_stack{3, 6, 9};
  s21::stack<int> copied_stack(original_stack);

  EXPECT_EQ(copied_stack.size(), 3U);
  EXPECT_EQ(copied_stack.top(), 9);
}

TEST(stack, move_constructor) {
  s21::stack<std::string> original_stack{"A", "B", "C"};
  s21::stack<std::string> moved_stack(std::move(original_stack));

  EXPECT_EQ(moved_stack.size(), 3U);
  EXPECT_EQ(moved_stack.top(), "C");
  EXPECT_EQ(original_stack.size(), 0U);
}

TEST(stack, move_assignment) {
  s21::stack<int> original_stack{10, 20, 30};
  s21::stack<int> moved_stack;
  moved_stack = std::move(original_stack);

  EXPECT_EQ(moved_stack.size(), 3U);
  EXPECT_EQ(moved_stack.top(), 30);
  EXPECT_EQ(original_stack.size(), 0U);
}

TEST(stack, pop_elements) {
  s21::stack<int> int_stack{5, 10, 15, 20};
  int_stack.pop();
  EXPECT_EQ(int_stack.top(), 15);
  int_stack.pop();
  EXPECT_EQ(int_stack.top(), 10);
}

TEST(stack, swap_stacks) {
  s21::stack<int> stack_a{1, 2, 3};
  s21::stack<int> stack_b{4, 5};

  stack_a.swap(stack_b);

  EXPECT_EQ(stack_a.size(), 2U);
  EXPECT_EQ(stack_a.top(), 5);
  EXPECT_EQ(stack_b.size(), 3U);
  EXPECT_EQ(stack_b.top(), 3);
}

TEST(stack, empty_check) {
  s21::stack<std::string> string_stack;
  EXPECT_TRUE(string_stack.empty());
  string_stack.push("Test");
  EXPECT_FALSE(string_stack.empty());
}

TEST(stack, large_number_of_elements) {
  const unsigned long n = 10000;
  s21::stack<int> large_stack;
  for (unsigned long i = 0; i < n; ++i) {
    large_stack.push(i);
  }
  EXPECT_EQ(large_stack.size(), n);
  EXPECT_EQ(large_stack.top(), static_cast<int>(n - 1));
}

TEST(stack, other_test) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  EXPECT_EQ(static_cast<unsigned long>(stack.size()), 3U);

  EXPECT_EQ(stack.top(), 3);
}

TEST(stack, top_on_empty_stack) {
  s21::stack<int> empty_stack;
  EXPECT_THROW(empty_stack.top(), std::logic_error);
}

TEST(stack, pop_on_empty_stack) {
  s21::stack<double> empty_stack;
  EXPECT_THROW(empty_stack.pop(), std::logic_error);
}

TEST(stack, push_after_pop) {
  s21::stack<int> int_stack{1, 2, 3};
  int_stack.pop();
  int_stack.push(4);
  EXPECT_EQ(int_stack.top(), 4);
}
