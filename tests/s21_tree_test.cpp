#include "../container/s21_tree.h"

#include "s21_main_test.h"
// Тест вставки элемента
TEST(TreeTest, InsertAndSearch) {
  s21::Tree<int, std::string> tree;

  tree.insert({1, "one"});
  s21::NodeMap<int, std::string>* node = tree.search(1);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->val.first, 1);
  EXPECT_EQ(node->val.second, "one");

  // Вставка существующего элемента, значение должно обновиться
  tree.insert({1, "uno"});
  node = tree.search(1);
  EXPECT_EQ(node->val.second, "uno");
}

// Тест поиска элемента
TEST(TreeTest, Search) {
  s21::Tree<int, std::string> tree;
  tree.insert({10, "ten"});
  tree.insert({20, "twenty"});
  tree.insert({5, "five"});

  EXPECT_NE(tree.search(10), nullptr);
  EXPECT_NE(tree.search(20), nullptr);
  EXPECT_NE(tree.search(5), nullptr);
  EXPECT_EQ(tree.search(15), nullptr);  // Не существует
}

// Тест удаления элемента
TEST(TreeTest, Remove) {
  s21::Tree<int, std::string> tree;
  tree.insert({30, "thirty"});
  tree.insert({20, "twenty"});
  tree.insert({40, "forty"});

  tree.remove(20);
  EXPECT_EQ(tree.search(20), nullptr);

  EXPECT_NE(tree.search(30), nullptr);
  EXPECT_NE(tree.search(40), nullptr);

  // Удаление корневого элемента

  tree.remove(30);

  EXPECT_EQ(tree.search(30), nullptr);
  EXPECT_NE(tree.search(40), nullptr);
}

// Тест обхода дерева в симметричном порядке
TEST(TreeTest, InOrderTraversal) {
  s21::Tree<int, std::string> tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});
  tree.insert({3, "three"});

  testing::internal::CaptureStdout();
  tree.inOrderTraversal(tree.getRoot());
  std::string output_str = testing::internal::GetCapturedStdout();

  // Ожидаемый результат обхода: "1 2 3"
  EXPECT_EQ(output_str, "1 2 3 ");
}

// Тест печати уровня дерева
TEST(TreeTest, PrintLevelOrder) {
  s21::Tree<int, std::string> tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});
  tree.insert({3, "three"});

  testing::internal::CaptureStdout();
  tree.printLevelOrder();
  std::string output_str = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output_str, "2 1 3 ");
}

// Тест на нахождение предшественника
TEST(TreeTest, Predecessor) {
  s21::Tree<int, std::string> tree;
  tree.insert({10, "ten"});
  tree.insert({5, "five"});
  tree.insert({15, "fifteen"});

  s21::NodeMap<int, std::string>* node = tree.search(15);
  s21::NodeMap<int, std::string>* predecessor = tree.predecessor(node);

  ASSERT_NE(predecessor, nullptr);
  EXPECT_EQ(predecessor->val.first, 10);
}

// Тест на нахождение преемника
TEST(TreeTest, Successor) {
  s21::Tree<int, std::string> tree;
  tree.insert({10, "ten"});
  tree.insert({5, "five"});
  tree.insert({15, "fifteen"});

  s21::NodeMap<int, std::string>* node = tree.search(10);
  s21::NodeMap<int, std::string>* successor = tree.successor(node);

  ASSERT_NE(successor, nullptr);
  EXPECT_EQ(successor->val.first, 15);
}

// Тест печати структуры дерева
TEST(TreeTest, PrintTreeStructure) {
  s21::Tree<int, std::string> tree;
  tree.insert({3, "three"});
  tree.insert({1, "one"});
  tree.insert({4, "four"});
  tree.insert({2, "two"});

  testing::internal::CaptureStdout();
  tree.printTreeStructure(tree.getRoot());
  std::string output_str = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output_str, "    4\n3\n        2\n    1\n");
}
TEST(TreeTest, FixDoubleBlack) {
  s21::Tree<int, std::string> tree;

  // Вставка элементов
  tree.insert({10, "ten"});
  tree.insert({20, "twenty"});
  tree.insert({30, "thirty"});
  tree.insert({15, "fifteen"});

  tree.remove(20);

  s21::NodeMap<int, std::string>* root = tree.getRoot();

  ASSERT_NE(root, nullptr);
  EXPECT_NE(root->left, nullptr);
  EXPECT_NE(root->right, nullptr);
}
TEST(TreeTest, RightRotate) {
  s21::Tree<int, std::string> tree;

  // Вставка элементов так, чтобы возникла необходимость в правом вращении
  tree.insert({10, "ten"});
  tree.insert({20, "twenty"});
  tree.insert({30, "thirty"});  // Это вызовет правое вращение на корневом узле

  s21::NodeMap<int, std::string>* root = tree.getRoot();

  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->val.first, 20);
  EXPECT_NE(root->left, nullptr);
  EXPECT_EQ(root->left->val.first, 10);
  EXPECT_NE(root->right, nullptr);
  EXPECT_EQ(root->right->val.first, 30);
}
// Тест вставки нескольких элементов
TEST(TreeTest, InsertMany) {
  s21::Tree<int, std::string> tree;

  std::vector<std::pair<int, std::string>> elements = {
      {5, "five"}, {3, "three"}, {7, "seven"}, {2, "two"}, {4, "four"}};

  for (const auto& element : elements) {
    tree.insert(element);
  }

  for (const auto& element : elements) {
    s21::NodeMap<int, std::string>* node = tree.search(element.first);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->val.first, element.first);
    EXPECT_EQ(node->val.second, element.second);
  }
}

// Тест удаления узла с одним ребенком
TEST(TreeTest, RemoveNodeWithOneChild) {
  s21::Tree<int, std::string> tree;
  tree.insert({10, "ten"});
  tree.insert({5, "five"});
  tree.insert({15, "fifteen"});
  tree.insert(
      {6, "six"});  // Добавляем узел, который имеет только одного ребенка

  tree.remove(5);
  EXPECT_EQ(tree.search(5), nullptr);
  EXPECT_NE(tree.search(10), nullptr);
  EXPECT_NE(tree.search(15), nullptr);
  EXPECT_NE(tree.search(6), nullptr);
}

// Тест удаления корня с двумя детьми
TEST(TreeTest, RemoveRootWithTwoChildren) {
  s21::Tree<int, std::string> tree;
  tree.insert({10, "ten"});
  tree.insert({5, "five"});
  tree.insert({15, "fifteen"});
  tree.insert({7, "seven"});
  tree.insert({12, "twelve"});

  tree.remove(10);
  EXPECT_EQ(tree.search(10), nullptr);
  EXPECT_NE(tree.search(5), nullptr);
  EXPECT_NE(tree.search(15), nullptr);
  EXPECT_NE(tree.search(7), nullptr);
  EXPECT_NE(tree.search(12), nullptr);
}

// Тест удаления узла, который не существует
TEST(TreeTest, RemoveNonExistentNode) {
  s21::Tree<int, std::string> tree;
  tree.insert({10, "ten"});
  tree.insert({20, "twenty"});

  tree.remove(30);  // Удаление несуществующего узла
  EXPECT_NE(tree.search(10), nullptr);
  EXPECT_NE(tree.search(20), nullptr);
}

// Тест обхода дерева с предшественником и преемником
TEST(TreeTest, PredecessorAndSuccessor) {
  s21::Tree<int, std::string> tree;
  tree.insert({10, "ten"});
  tree.insert({5, "five"});
  tree.insert({15, "fifteen"});
  tree.insert({12, "twelve"});

  s21::NodeMap<int, std::string>* node = tree.search(15);
  s21::NodeMap<int, std::string>* predecessor = tree.predecessor(node);
  s21::NodeMap<int, std::string>* successor = tree.successor(node);

  EXPECT_NE(predecessor, nullptr);
  EXPECT_EQ(predecessor->val.first, 12);

  EXPECT_EQ(successor, nullptr);
}