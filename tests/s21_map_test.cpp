#include "s21_main_test.h"

TEST(MapTest, DefaultConstructor) {
  s21::Map<int, int> s21_map;
  std::map<int, int> std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_TRUE(s21_map.empty());
  EXPECT_TRUE(std_map.empty());
}

// Проверка конструктора и вставки элементов
TEST(MapTest, InitializerListConstructor) {
  s21::Map<int, int> s21_map = {{1, 100}, {2, 200}, {3, 300}};
  std::map<int, int> std_map = {{1, 100}, {2, 200}, {3, 300}};

  EXPECT_EQ(s21_map.size(), std_map.size());
  for (const auto &pair : std_map) {
    EXPECT_EQ(s21_map.at(pair.first), pair.second);
  }
}

// Проверка вставки и доступа к элементам
TEST(MapTest, InsertAndAccess) {
  s21::Map<int, int> s21_map;
  std::map<int, int> std_map;

  s21_map.insert(1, 100);
  std_map.insert({1, 100});

  EXPECT_EQ(s21_map.at(1), 100);
  EXPECT_EQ(std_map.at(1), 100);

  s21_map[2] = 200;
  std_map[2] = 200;

  EXPECT_EQ(s21_map[2], 200);
  EXPECT_EQ(std_map[2], 200);
}

// Проверка удаления элемента
TEST(MapTest, Erase) {
  s21::Map<int, int> s21_map = {{1, 100}, {2, 200}, {3, 300}};
  std::map<int, int> std_map = {{1, 100}, {2, 200}, {3, 300}};

  s21_map.erase(2);
  std_map.erase(2);

  EXPECT_EQ(s21_map.size(), std_map.size());

  EXPECT_FALSE(s21_map.contains(2));
  EXPECT_FALSE(std_map.count(2));
}

// Проверка обновления значения
TEST(MapTest, Update) {
  s21::Map<int, int> s21_map = {{1, 100}};
  std::map<int, int> std_map = {{1, 100}};

  s21_map.update(1, 200);
  std_map[1] = 200;

  EXPECT_EQ(s21_map.at(1), 200);
  EXPECT_EQ(std_map.at(1), 200);
}

// Проверка работы оператора []
TEST(MapTest, OperatorSquareBrackets) {
  s21::Map<int, int> s21_map;
  std::map<int, int> std_map;

  s21_map[1] = 100;
  std_map[1] = 100;

  EXPECT_EQ(s21_map[1], 100);
  EXPECT_EQ(std_map[1], 100);

  s21_map[2] = 200;
  std_map[2] = 200;

  EXPECT_EQ(s21_map[2], 200);
  EXPECT_EQ(std_map[2], 200);
}

// Проверка работы метода count
TEST(MapTest, Count) {
  s21::Map<int, int> s21_map = {{1, 100}, {2, 200}};
  std::map<int, int> std_map = {{1, 100}, {2, 200}};

  EXPECT_EQ(s21_map.count(1), std_map.count(1));
  EXPECT_EQ(s21_map.count(3), std_map.count(3));
}
TEST(MapTest, EraseTest2) {
  s21::Map<int, int> s21_map = {{1, 100}, {2, 200}};
  std::map<int, int> std_map = {{1, 100}, {2, 200}};
  s21_map.erase(1);
  std_map.erase(1);
  EXPECT_EQ(s21_map.size(), std_map.size());
}
TEST(MapTest, OperatorSearch) {
  s21::Map<int, int> s21_map = {{1, 100}, {2, 200}};
  std::map<int, int> std_map = {{1, 100}, {2, 200}};
  const int check = 1;
  EXPECT_EQ(s21_map[check], std_map[check]);
}
TEST(MapTest, SearchExistingKey) {
  s21::Map<int, int> map;
  map.insert(1, 100);
  map.insert(2, 200);

  EXPECT_EQ(map[1], 100);
  EXPECT_EQ(map[2], 200);
}

TEST(MapTest, SearchNonExistingKey) {
  s21::Map<int, int> map;
  map.insert(1, 100);

  EXPECT_THROW(map.at(2), std::out_of_range);
}
TEST(MapTest, Erase2) {
  s21::Map<int, int> map;
  map.insert(1, 100);
  map.insert(2, 200);

  auto it = map.begin();
  ++it;

  map.erase(it);

  EXPECT_EQ(map.count(2), 0);
  EXPECT_NO_THROW(map.at(1));
  EXPECT_THROW(map.at(2), std::out_of_range);
}

TEST(MapInsertTest, InsertNewElement) {
  s21::Map<int, int> map = s21::Map<int, int>();
  auto result = map.insert(std::make_pair(1, 100));
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, 100);
  EXPECT_EQ(map.size(), 1);
}

TEST(MapInsertTest, InsertDuplicateElement) {
  s21::Map<int, int> map = s21::Map<int, int>();
  map.insert(std::make_pair(1, 100));
  auto result = map.insert(std::make_pair(1, 200));
  EXPECT_FALSE(result.second);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, 100);
  EXPECT_EQ(map.size(), 1);
}

TEST(MapInsertByKeyTest, InsertNewElementByKey) {
  s21::Map<int, int> map = s21::Map<int, int>();
  auto result = map.insert(1, 100);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, 100);
  EXPECT_EQ(map.size(), 1);
}

TEST(MapInsertByKeyTest, UpdateExistingElementByKey) {
  s21::Map<int, int> map = s21::Map<int, int>();
  map.insert(1, 100);
  auto result = map.insert(1, 200);

  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, 200);
  EXPECT_EQ(map.size(), 1);
}
TEST(MapBeginTest, BeginOnEmptyTree) {
  s21::Map<int, int> map = s21::Map<int, int>();
  auto it = map.begin();
  EXPECT_EQ(it, map.end());
}
TEST(MapBeginTest, BeginOnNonEmptyTree) {
  s21::Map<int, int> map = s21::Map<int, int>();
  map.insert(std::make_pair(1, 100));
  map.insert(std::make_pair(2, 200));

  auto it = map.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, 100);
}
TEST(MapEmptyTest, MapIsInitiallyEmpty) {
  s21::Map<int, int> map = s21::Map<int, int>();
  EXPECT_TRUE(map.empty());
}

TEST(MapEmptyTest, MapIsNotEmptyAfterInsertion) {
  s21::Map<int, int> map = s21::Map<int, int>();
  map.insert(std::make_pair(1, 100));
  EXPECT_FALSE(map.empty());
}
TEST(MapCopyConstructorTest, CopyConstructorNonEmptyMap) {
  s21::Map<int, int> map = s21::Map<int, int>();

  map.insert(std::make_pair(1, 100));
  map.insert(std::make_pair(2, 200));

  s21::Map<int, int> copy(map);

  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(1), 100);
  EXPECT_EQ(copy.at(2), 200);
}

TEST(MapCopyConstructorTest, CopyConstructorEmptyMap) {
  s21::Map<int, int> map = s21::Map<int, int>();

  s21::Map<int, int> copy(map);

  EXPECT_TRUE(copy.empty());
}
TEST(MapTest, MoveConstructor) {
  s21::Map<int, int> map1;
  map1.insert(1, 100);
  map1.insert(2, 200);

  s21::Map<int, int> map2(std::move(map1));

  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map1.size(), 0);
}

TEST(MapTest, OperatorBracket) {
  s21::Map<int, int> map;
  map.insert(1, 100);
  map.insert(2, 200);

  EXPECT_EQ(map[1], 100);
  EXPECT_EQ(map[2], 200);

  // Проверяем, что добавление нового элемента работает
  map[3] = 300;
  EXPECT_EQ(map[3], 300);
  EXPECT_EQ(map.size(), 3);
}

// Проверка работы метода clear
TEST(MapTest, Clear) {
  s21::Map<int, int> s21_map = {{1, 100}, {2, 200}};
  std::map<int, int> std_map = {{1, 100}, {2, 200}};

  s21_map.clear();
  std_map.clear();

  EXPECT_TRUE(s21_map.empty());
  EXPECT_TRUE(std_map.empty());
}
TEST(MapTest, CopyConstructor) {
  s21::Map<int, int> s21_map1 = {{1, 100}, {2, 200}};
  s21::Map<int, int> s21_map2(s21_map1);

  EXPECT_EQ(s21_map2.size(), 2);
  EXPECT_EQ(s21_map1.size(), 2);
}

TEST(MapTest, MoveAssignmentOperator) {
  s21::Map<int, int> s21_map1 = {{1, 100}, {2, 200}};
  s21::Map<int, int> s21_map2;

  s21_map2 = std::move(s21_map1);

  EXPECT_EQ(s21_map2.size(), 2);
  EXPECT_TRUE(s21_map1.empty());
}

TEST(MapTest, InsertOrAssign_InsertNewKey) {
  s21::Map<int, std::string> map;
  auto result = map.insert_or_assign(1, "Value1");

  EXPECT_EQ(result.second, true);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, "Value1");
  EXPECT_EQ(map.size(), 1);
}

TEST(MapTest, InsertOrAssign_UpdateExistingKey) {
  s21::Map<int, std::string> map;

  map.insert_or_assign(1, "Value1");

  auto result = map.insert_or_assign(1, "UpdatedValue");

  EXPECT_EQ(result.second, false);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, "UpdatedValue");
  EXPECT_EQ(map.size(), 1);
}
TEST(MapTest, Merge) {
  s21::Map<int, int> s21_map1 = {{1, 100}, {2, 200}};
  s21::Map<int, int> s21_map2 = {{3, 300}, {4, 400}};

  std::map<int, int> std_map1 = {{1, 100}, {2, 200}};
  std::map<int, int> std_map2 = {{3, 300}, {4, 400}};

  s21_map1.merge(s21_map2);
  std_map1.merge(std_map2);

  EXPECT_EQ(s21_map1.size(), std_map1.size());
  for (const auto &pair : std_map1) {
    EXPECT_EQ(s21_map1.at(pair.first), pair.second);
  }
}

// Проверка работы метода swap
TEST(MapTest, Swap) {
  s21::Map<int, int> s21_map1 = {{1, 100}};
  s21::Map<int, int> s21_map2 = {{2, 200}};

  std::map<int, int> std_map1 = {{1, 100}};
  std::map<int, int> std_map2 = {{2, 200}};

  s21_map1.swap(s21_map2);
  std_map1.swap(std_map2);

  EXPECT_EQ(s21_map1.size(), std_map2.size());
  EXPECT_EQ(s21_map2.size(), std_map1.size());

  for (const auto &pair : std_map1) {
    EXPECT_EQ(s21_map1.at(pair.first), pair.second);
  }
  for (const auto &pair : std_map2) {
    EXPECT_EQ(s21_map2.at(pair.first), pair.second);
  }
}
// Проверка метода insert_many
TEST(MapTest, InsertMany) {
  s21::Map<int, int> s21_map;
  std::map<int, int> std_map;

  s21_map.insert_many(std::make_pair(1, 100), std::make_pair(2, 200));
  std_map.insert(std::make_pair(1, 100));
  std_map.insert(std::make_pair(2, 200));

  EXPECT_EQ(s21_map.size(), std_map.size());
  for (const auto &pair : std_map) {
    EXPECT_EQ(s21_map.at(pair.first), pair.second);
  }
}
s21::NodeMap<int, int> *createNode(int key, int value,
                                   s21::NodeMap<int, int> *left = nullptr,
                                   s21::NodeMap<int, int> *right = nullptr,
                                   s21::NodeMap<int, int> *parent = nullptr) {
  s21::NodeMap<int, int> *node =
      new s21::NodeMap<int, int>(std::make_pair(key, value));

  node->left = left;
  node->right = right;
  node->parent = parent;
  return node;
}

class MapIteratorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Создаем тестовое дерево
    root = createNode(2, 200);
    left = createNode(1, 100, nullptr, nullptr, root);
    right = createNode(3, 300, nullptr, nullptr, root);
    root->left = left;
    root->right = right;

    iter = s21::MapIterator<int, int>(root);
    leftIter = s21::MapIterator<int, int>(left);
    rightIter = s21::MapIterator<int, int>(right);
  }
  void deleteTree(s21::NodeMap<int, int> *node) {
    if (node != nullptr) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }

  void TearDown() override { deleteTree(root); }
  s21::NodeMap<int, int> *root;
  s21::NodeMap<int, int> *left;
  s21::NodeMap<int, int> *right;
  s21::MapIterator<int, int> iter;
  s21::MapIterator<int, int> leftIter;
  s21::MapIterator<int, int> rightIter;
};

TEST_F(MapIteratorTest, Increment) {
  EXPECT_EQ(iter->first, 2);
  ++iter;
  EXPECT_EQ(iter->first, 3);
}

// Тестирование постфиксного инкремента
TEST_F(MapIteratorTest, PostIncrement) {
  s21::MapIterator<int, int> temp = iter++;
  EXPECT_EQ(temp->first, 2);
  EXPECT_EQ(iter->first, 3);
}

TEST_F(MapIteratorTest, Decrement) {
  EXPECT_EQ(rightIter->first, 3);
  --rightIter;
  EXPECT_EQ(rightIter->first, 2);
}

// Тестирование постфиксного декремента
TEST_F(MapIteratorTest, PostDecrement) {
  s21::MapIterator<int, int> temp = rightIter--;
  EXPECT_EQ(temp->first, 3);
  EXPECT_EQ(rightIter->first, 2);
}

TEST_F(MapIteratorTest, DereferenceOperator) {
  EXPECT_EQ(*iter, std::make_pair(2, 200));
}

TEST_F(MapIteratorTest, Equality) { EXPECT_FALSE(iter == leftIter); }

TEST_F(MapIteratorTest, Inequality) { EXPECT_TRUE(iter != leftIter); }
class MapConstIteratorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    root = createNode(2, 200);
    left = createNode(1, 100, nullptr, nullptr, root);
    right = createNode(3, 300, nullptr, nullptr, root);
    rightR = createNode(4, 400, nullptr, nullptr, root);
    root->left = left;
    root->right = right;
    right->right = rightR;
    iter = s21::MapConstIterator<int, int>(root);
    leftIter = s21::MapConstIterator<int, int>(left);
    rightIter = s21::MapConstIterator<int, int>(right);
    rightRIter = s21::MapConstIterator<int, int>(rightR);
  }
  void deleteTree(s21::NodeMap<int, int> *node) {
    if (node != nullptr) {
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }
  }

  void TearDown() override { deleteTree(root); }
  s21::NodeMap<int, int> *root;
  s21::NodeMap<int, int> *left;
  s21::NodeMap<int, int> *right;
  s21::NodeMap<int, int> *rightR;

  s21::MapConstIterator<int, int> iter;
  s21::MapConstIterator<int, int> leftIter;
  s21::MapConstIterator<int, int> rightIter;
  s21::MapConstIterator<int, int> rightRIter;
};
TEST_F(MapConstIteratorTest, Increment) {
  EXPECT_EQ(iter->first, 2);
  ++iter;
  EXPECT_EQ(iter->first, 3);
}

TEST_F(MapConstIteratorTest, PostIncrement) {
  s21::MapConstIterator<int, int> temp = iter++;
  EXPECT_EQ(temp->first, 2);
  EXPECT_EQ(iter->first, 3);
}

TEST_F(MapConstIteratorTest, Decrement) {
  EXPECT_EQ(rightIter->first, 3);
  --rightIter;
  EXPECT_EQ(rightIter->first, 2);
}

TEST_F(MapConstIteratorTest, PostDecrement) {
  s21::MapConstIterator<int, int> temp = rightIter--;
  EXPECT_EQ(temp->first, 3);
  EXPECT_EQ(rightIter->first, 2);
}

TEST_F(MapConstIteratorTest, DereferenceOperator) {
  EXPECT_EQ(*iter, std::make_pair(2, 200));
}

TEST_F(MapConstIteratorTest, IncrementBeyondEnd) {
  rightRIter++;
  ++iter;
  ++iter;
  EXPECT_EQ(iter->first, 4);
}

TEST_F(MapConstIteratorTest, DecrementBeyondBegin) {
  --rightIter;
  --rightIter;
  EXPECT_EQ(rightIter->first, 1);
}

TEST_F(MapConstIteratorTest, Equality) { EXPECT_FALSE(iter == leftIter); }

TEST_F(MapConstIteratorTest, Inequality) { EXPECT_TRUE(iter != leftIter); }