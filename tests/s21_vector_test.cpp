#include "s21_main_test.h"

// Тестирование конструктора по умолчанию
TEST(VectorTest, DefaultConstructor) {
  s21::Vector<int> v;
  std::vector<int> std_v;

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
}

// Тестирование конструктора с начальным размером
TEST(VectorTest, ConstructorWithSize) {
  s21::Vector<int> v(10);
  std::vector<int> std_v(10);

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
}

// Тестирование конструктора с initializer_list
TEST(VectorTest, ConstructorWithInitializerList) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> std_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

// Тестирование конструктора копирования
TEST(VectorTest, CopyConstructor) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  s21::Vector<int> v_copy(v);
  std::vector<int> std_v = {1, 2, 3, 4, 5};
  std::vector<int> std_v_copy(std_v);

  EXPECT_EQ(v_copy.size(), std_v_copy.size());
  EXPECT_EQ(v_copy.capacity(), std_v_copy.capacity());
  for (size_t i = 0; i < v_copy.size(); ++i) {
    EXPECT_EQ(v_copy[i], std_v_copy[i]);
  }
}

// Тестирование перемещающего конструктора
TEST(VectorTest, MoveConstructor) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  s21::Vector<int> v_move(std::move(v));
  std::vector<int> std_v = {1, 2, 3, 4, 5};
  std::vector<int> std_v_move(std::move(std_v));

  EXPECT_EQ(v_move.size(), std_v_move.size());
  EXPECT_EQ(v_move.capacity(), std_v_move.capacity());
}

// Тестирование оператора присваивания
TEST(VectorTest, AssignmentOperator) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  s21::Vector<int> v_assigned;
  v_assigned = v;
  std::vector<int> std_v = {1, 2, 3, 4, 5};
  std::vector<int> std_v_assigned;
  std_v_assigned = std_v;

  EXPECT_EQ(v_assigned.size(), std_v_assigned.size());
  EXPECT_EQ(v_assigned.capacity(), std_v_assigned.capacity());
  for (size_t i = 0; i < v_assigned.size(); ++i) {
    EXPECT_EQ(v_assigned[i], std_v_assigned[i]);
  }
}

// Тестирование перемещающего оператора присваивания
TEST(VectorTest, MoveAssignmentOperator) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  s21::Vector<int> v_moved;
  v_moved = std::move(v);
  std::vector<int> std_v = {1, 2, 3, 4, 5};
  std::vector<int> std_v_moved;
  std_v_moved = std::move(std_v);

  EXPECT_EQ(v_moved.size(), std_v_moved.size());
  EXPECT_EQ(v_moved.capacity(), std_v_moved.capacity());
}

// Тестирование метода push_back
TEST(VectorTest, PushBack) {
  s21::Vector<int> v;
  std::vector<int> std_v;

  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
    std_v.push_back(i);
  }

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

// Тестирование метода pop_back
TEST(VectorTest, PopBack) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> std_v = {1, 2, 3, 4, 5};

  v.pop_back();
  std_v.pop_back();

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

// Тестирование метода insert
TEST(VectorTest, Insert) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> std_v = {1, 2, 3, 4, 5};

  auto it = v.insert(v.begin() + 2, 10);
  auto std_it = std_v.insert(std_v.begin() + 2, 10);

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
  EXPECT_EQ(*it, *std_it);
}

// Тестирование метода erase
TEST(VectorTest, Erase) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> std_v = {1, 2, 3, 4, 5};

  v.erase(v.begin() + 2);
  std_v.erase(std_v.begin() + 2);

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

// Тестирование метода clear
TEST(VectorTest, Clear) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> std_v = {1, 2, 3, 4, 5};

  v.clear();
  std_v.clear();

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
}

// Тестирование метода reserve
TEST(VectorTest, Reserve) {
  s21::Vector<int> v;
  std::vector<int> std_v;

  v.reserve(100);
  std_v.reserve(100);

  EXPECT_EQ(v.capacity(), std_v.capacity());
}

// Тестирование метода shrink_to_fit
TEST(VectorTest, ShrinkToFit) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> std_v = {1, 2, 3, 4, 5};

  v.reserve(100);
  std_v.reserve(100);

  v.shrink_to_fit();
  std_v.shrink_to_fit();

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
}

// Тестирование метода insert_many_back
TEST(VectorTest, InsertManyBack) {
  s21::Vector<int> v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  v.insert_many_back(4, 5, 6);
  std_v.insert(std_v.end(), {4, 5, 6});

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}

// Тестирование метода insert_many
TEST(VectorTest, InsertMany) {
  s21::Vector<int> v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  v.insert_many(v.begin() + 1, 4, 5, 6);
  std_v.insert(std_v.begin() + 1, {4, 5, 6});

  EXPECT_EQ(v.size(), std_v.size());
  EXPECT_EQ(v.capacity(), std_v.capacity());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], std_v[i]);
  }
}
