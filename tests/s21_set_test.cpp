#include "s21_main_test.h"

// Проверка конструктора по умолчанию и проверка на пустоту
TEST(SetTest, DefaultConstructor) {
  s21::Set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.empty());
  EXPECT_TRUE(std_set.empty());
}

// Проверка конструктора и вставки элементов
TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_set.size(), std_set.size());
  for (const auto& item : std_set) {
    EXPECT_TRUE(s21_set.contains(item));
  }
}

// Проверка вставки и возврата пар (iterator, bool)
TEST(SetTest, Insert) {
  s21::Set<int> s21_set;
  std::set<int> std_set;

  auto [it1, inserted1] = s21_set.insert(1);
  auto [it2, inserted2] = std_set.insert(1);

  EXPECT_TRUE(inserted1);
  EXPECT_TRUE(inserted2);
  EXPECT_EQ(*it1, *it2);

  auto [it1_dup, inserted1_dup] = s21_set.insert(1);
  auto [it2_dup, inserted2_dup] = std_set.insert(1);

  EXPECT_FALSE(inserted1_dup);
  EXPECT_FALSE(inserted2_dup);
  EXPECT_EQ(*it1, *it2);
}
TEST(SetTest, Insert1) {
  const s21::Set<int> s21_set{1, 2, 3};
  auto it = s21_set.begin();
  EXPECT_EQ(*it, 1);
}

// Проверка удаления элемента
TEST(SetTest, Erase) {
  s21::Set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  s21_set.erase(s21_set.find(3));
  std_set.erase(3);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_FALSE(s21_set.contains(3));
  EXPECT_FALSE(std_set.count(3));
}

// Проверка swap
TEST(SetTest, Swap) {
  s21::Set<int> s21_set1 = {1, 2, 3};
  s21::Set<int> s21_set2 = {4, 5, 6};

  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2 = {4, 5, 6};

  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);

  EXPECT_EQ(s21_set1.size(), std_set2.size());
  EXPECT_EQ(s21_set2.size(), std_set1.size());
  EXPECT_EQ(s21_set1.size(), std_set1.size());

  for (const auto& item : std_set1) {
    EXPECT_TRUE(s21_set1.contains(item));
  }

  for (const auto& item : std_set2) {
    EXPECT_TRUE(s21_set2.contains(item));
  }
}

// Проверка merge
TEST(SetTest, Merge) {
  s21::Set<int> s21_set1 = {1, 2, 3};
  s21::Set<int> s21_set2 = {4, 5, 6};

  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2 = {4, 5, 6};

  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);

  EXPECT_EQ(s21_set1.size(), std_set1.size());
  for (const auto& item : std_set1) {
    EXPECT_TRUE(s21_set1.contains(item));
  }
}

// Проверка insert_many
TEST(SetTest, InsertMany) {
  s21::Set<int> s21_set;
  std::set<int> std_set;

  auto result_s21 = s21_set.insert_many(1, 2, 3, 4, 5);
  std_set.insert({1, 2, 3, 4, 5});

  EXPECT_EQ(s21_set.size(), std_set.size());
  for (const auto& item : std_set) {
    EXPECT_TRUE(s21_set.contains(item));
  }
}
