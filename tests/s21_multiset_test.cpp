#include "s21_main_test.h"
TEST(MultisetTest, DefaultConstructor) {
  s21::Multiset<int> ms;
  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::Multiset<int> ms{1, 2, 3, 4, 5};
  EXPECT_EQ(ms.size(), 5);
}

TEST(MultisetTest, CopyConstructor) {
  s21::Multiset<int> ms1{1, 2, 3, 4, 5};
  s21::Multiset<int> ms2(ms1);
  EXPECT_EQ(ms2.size(), 5);
}

TEST(MultisetTest, MoveConstructor) {
  s21::Multiset<int> ms1{1, 2, 3, 4, 5};
  s21::Multiset<int> ms2(std::move(ms1));
  EXPECT_EQ(ms2.size(), 5);
  EXPECT_TRUE(ms1.empty());
}

TEST(MultisetTest, MoveAssignmentOperator) {
  s21::Multiset<int> ms1{1, 2, 3, 4, 5};
  s21::Multiset<int> ms2;
  ms2 = std::move(ms1);
  EXPECT_EQ(ms2.size(), 5);
  EXPECT_TRUE(ms1.empty());
}

TEST(MultisetTest, Insert) {
  s21::Multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.max_size();
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
}

TEST(MultisetTest, Erase) {
  s21::Multiset<int> ms{1, 2, 2, 3};
  auto it = ms.find(2);
  ms.erase(it);
  EXPECT_EQ(ms.count(2), 1);
}

TEST(MultisetTest, Clear) {
  s21::Multiset<int> ms{1, 2, 3};
  ms.insert(1);
  ms.clear();
  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, Swap) {
  s21::Multiset<int> ms1{1, 2, 3};
  s21::Multiset<int> ms2{4, 5};
  ms1.swap(ms2);
  EXPECT_EQ(ms1.count(4), 1);
  EXPECT_EQ(ms2.count(1), 1);
}

TEST(MultisetTest, Merge) {
  s21::Multiset<int> ms1{1, 2};
  s21::Multiset<int> ms2{2, 3};
  ms1.merge(ms2);

  EXPECT_EQ(ms1.count(1), 1);
  EXPECT_EQ(ms1.count(2), 2);
  EXPECT_EQ(ms1.count(3), 1);
}

TEST(MultisetTest, Count) {
  s21::Multiset<int> ms{1, 2, 2, 3};
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 1);
  EXPECT_EQ(ms.count(4), 0);
}

TEST(MultisetTest, Find) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.find(2);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 2);
}

TEST(MultisetTest, Contains) {
  s21::Multiset<int> ms{1, 2, 3};
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

TEST(MultisetTest, EqualRange) {
  s21::Multiset<int> ms{1, 2, 2, 3};
  auto range = ms.equal_range(2);
  EXPECT_EQ(range.first, ms.find(2));
  EXPECT_EQ(range.second, ms.find(3));
}

TEST(MultisetTest, LowerBound) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.lower_bound(2);
  EXPECT_EQ(*it, 2);
}

TEST(MultisetTest, UpperBound) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.upper_bound(2);
  EXPECT_EQ(*it, 3);
}
TEST(MultisetTest, IteratorIncrement) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(MultisetTest, IteratorEquality) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it1 = ms.begin();
  auto it2 = ms.begin();
  EXPECT_TRUE(it1 == it2);
  ++it2;
  EXPECT_TRUE(it1 != it2);
}

TEST(MultisetTest, IteratorDereference) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  EXPECT_EQ(*it, 1);
}
TEST(MultisetTest, InsertMany) {
  s21::Multiset<int> s21_set;
  std::multiset<int> std_set;

  auto result_s21 = s21_set.insert_many(1, 2, 3, 4, 5);
  std_set.insert({1, 2, 3, 4, 5});

  EXPECT_EQ(s21_set.size(), std_set.size());
  for (const auto& item : std_set) {
    EXPECT_TRUE(s21_set.contains(item));
  }
}
TEST(MultisetTest, IteratorDereference1) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  it++;
  EXPECT_EQ(*it, 2);
}
TEST(MultisetTest, IteratorDereference2) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  it++;
  it--;
  EXPECT_EQ(*it, 1);
}
TEST(MultisetTest, IteratorDereference3) {
  const s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  it++;
  EXPECT_EQ(*it, 2);
}
TEST(MultisetTest, IteratorDereference4) {
  const s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  it++;
  it--;
  EXPECT_EQ(*it, 1);
}
TEST(MultisetTest, IteratorEquality1) {
  const s21::Multiset<int> ms{1, 2, 3};
  auto it1 = ms.begin();
  auto it2 = ms.begin();
  EXPECT_TRUE(it1 == it2);
  ++it2;
  EXPECT_TRUE(it1 != it2);
}
TEST(MultisetTest, IteratorArrowOperator) {
  s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();

  EXPECT_EQ(*(it.operator->()), 1);

  it++;

  EXPECT_EQ(*(it.operator->()), 2);

  it--;

  EXPECT_EQ(*(it.operator->()), 1);
}
TEST(MultisetTest, IteratorArrowOperator1) {
  const s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();

  EXPECT_EQ(*(it.operator->()), 1);

  it++;

  EXPECT_EQ(*(it.operator->()), 2);

  it--;

  EXPECT_EQ(*(it.operator->()), 1);
}
TEST(MultisetTest, IteratorDereference6) {
  const s21::Multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  it++;
  EXPECT_EQ(it.getNodeMap()->val.first, 2);
}