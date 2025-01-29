#include <gtest/gtest.h>

#include "s21_main_test.h"

TEST(DefaultConstructorArray, Test_1) {
  auto arr1 = s21::array<int, 3>();
  auto arr2 = std::array<int, 3>();
  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(arr1.empty(), arr2.empty());
  for (size_t i = 0; i < arr1.size(); ++i) {
    ASSERT_EQ(arr1[i], arr2[i]);
  }
}

TEST(DefaultConstructorArray, Test_2) {
  auto arr1 = s21::array<double, 3>();
  auto arr2 = std::array<double, 3>();
  arr1[2] = arr2[2] = 8.9876;
  for (size_t i = 0; i < arr1.size(); ++i) {
    ASSERT_EQ(arr1[i], arr2[i]);
  }
}

TEST(InitializerListConstructorArray, Test_1) {
  s21::array<double, 3> arr1 = {0, 1, 2};
  std::array<double, 3> arr2 = {0, 1, 2};
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(arr1[i], arr2[i]);
  }
}

TEST(CopyConstructorTestArray, Test_1) {
  auto arr1 = s21::array<double, 5>();
  auto arr2 = std::array<double, 5>();
  arr1[3] = arr2[3] = 4.567;
  auto s21_res(arr1);
  auto std_res(arr2);
  for (size_t i = 0; i < std_res.size(); ++i) {
    ASSERT_EQ(s21_res[i], std_res[i]);
  }
}

TEST(CopyConstructorTestArray, Test_2) {
  auto arr1 = s21::array<double, 0>();
  auto s21_res(arr1);
  ASSERT_EQ(s21_res.size(), 0);
}

TEST(MoveConstructorTestArray, Test_1) {
  auto arr1 = s21::array<double, 5>();
  auto arr2 = std::array<double, 5>();
  arr1[3] = arr2[3] = 4.567;
  auto s21_res(std::move(arr1));
  auto std_res(std::move(arr2));
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_EQ(s21_res[i], std_res[i]);
  }
}

TEST(MoveConstructorTestArray, Test_2) {
  auto arr1 = s21::array<double, 0>();
  auto arr2 = std::array<double, 0>();
  auto s21_res(std::move(arr1));
  auto std_res(std::move(arr2));
  ASSERT_EQ(s21_res.size(), std_res.size());
}

// Operator tests

TEST(MoveOperatorTestArray, Test_1) {
  s21::array<double, 3> arr1 = {0, 1, 2};
  s21::array<double, 3> arr2 = {1, 2, 3};
  arr1 = std::move(arr2);
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(arr1[i], i + 1);
  }
}

TEST(MoveOperatorTestArray, Test_2) {
  s21::array<double, 0> s21_arr1;
  s21::array<double, 0> s21_arr2;
  s21_arr1 = std::move(s21_arr2);
  std::array<double, 0> std_arr1;
  std::array<double, 0> std_arr2;
  std_arr1 = std::move(std_arr2);
  ASSERT_EQ(s21_arr1.size(), std_arr1.size());
  ASSERT_EQ(s21_arr2.size(), std_arr2.size());
  ASSERT_EQ(s21_arr2.data(), std_arr2.data());
  ASSERT_EQ(s21_arr1.begin(), std_arr1.begin());
  ASSERT_EQ(s21_arr1.end(), std_arr1.end());
  ASSERT_ANY_THROW(s21_arr1.front());
  ASSERT_ANY_THROW(s21_arr1.back());
}

TEST(CopyOperatorTestArray, Test_1) {
  s21::array<double, 3> arr1 = {0, 1, 2};
  s21::array<double, 3> arr2 = {1, 2, 4};
  arr1 = arr2;
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(arr1[i], arr2[i]);
  }
}

TEST(CopyOperatorTestArray, Test_2) {
  s21::array<double, 0> arr1;
  s21::array<double, 0> arr2;
  arr1 = arr2;
  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(CopyConstOperatorTestArray, Test_3) {
  auto arr1 = s21::array<double, 4>();
  auto arr2 = std::array<double, 4>();
  arr1[2] = arr2[2] = 8.9876;
  const auto s21_res = arr1;
  const auto std_res = arr2;
  for (size_t i = 0; i < std_res.size(); ++i) {
    ASSERT_EQ(s21_res[i], std_res[i]);
  }
}

TEST(CopyOperatorTestArray, Test_4) {
  s21::array<double, 0> s21_arr1;
  const s21::array<double, 0> s21_arr2;
  s21_arr1 = s21_arr2;
  std::array<double, 0> std_arr1;
  std::array<double, 0> std_arr2;
  std_arr1 = std_arr2;
  ASSERT_EQ(s21_arr1.size(), std_arr1.size());
  ASSERT_EQ(s21_arr2.size(), std_arr2.size());
  ASSERT_EQ(s21_arr2.data(), std_arr2.data());
  ASSERT_EQ(s21_arr2.begin(), std_arr2.begin());
  ASSERT_EQ(s21_arr2.end(), std_arr2.end());
  ASSERT_EQ(s21_arr2.cbegin(), std_arr2.cbegin());
  ASSERT_EQ(s21_arr2.cend(), std_arr2.cend());
  ASSERT_ANY_THROW(s21_arr2.front());
  ASSERT_ANY_THROW(s21_arr2.back());
}

// Function tests

TEST(AtFunctionTestArray, Test_1) {
  auto arr = s21::array<double, 5>();
  ASSERT_ANY_THROW(arr.at(7));
}

TEST(AtConstFunctionTestArray, Test_2) {
  const auto arr = s21::array<double, 0>();
  ASSERT_ANY_THROW(arr.at(3));
}

TEST(AtConstFunctionTestArray, Test_3) {
  const auto arr = s21::array<int, 5>();
  ASSERT_EQ(arr.at(3), 0);
}

TEST(AtFunctionTestArray, Test_3) {
  s21::array<double, 3> arr1 = {0, 1, 2};
  std::array<double, 3> arr2 = {0, 1, 2};
  ASSERT_EQ(arr1.at(2), arr2.at(2));
}

TEST(AtFunctionTestArray, Test_4) {
  auto arr = s21::array<double, 0>();
  ASSERT_ANY_THROW(arr.at(7));
}

TEST(FrontFunctionTestArray, Test_1) {
  s21::array<double, 3> arr1 = {5, 1, 2};
  std::array<double, 3> arr2 = {5, 1, 2};
  ASSERT_EQ(arr1.front(), arr2.front());
}

TEST(FrontConstFunctionTestArray, Test_1) {
  const s21::array<double, 3> arr1 = {8, 1, 2};
  const std::array<double, 3> arr2 = {8, 1, 2};
  ASSERT_EQ(arr1.front(), arr2.front());
}

TEST(BackConstFunctionTestArray, Test_1) {
  const s21::array<double, 3> arr1 = {5, 1, 2};
  const std::array<double, 3> arr2 = {5, 1, 2};
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(BackFunctionTestArray, Test_1) {
  s21::array<double, 4> arr1 = {5, 1, 2, 7};
  std::array<double, 4> arr2 = {5, 1, 2, 7};
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(DataFunctionTestArray, Test_1) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
  auto ptr1 = arr1.data();
  auto ptr2 = arr2.data();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(DataFunctionTestArray, Test_2) {
  s21::array<int, 0> arr1;
  std::array<int, 0> arr2;
  auto ptr1 = arr1.data();
  auto ptr2 = arr2.data();
  EXPECT_EQ(ptr1, ptr2);
}

TEST(DataConstFunctionTestArray, Test_3) {
  const s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  const std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
  const auto ptr1 = arr1.data();
  const auto ptr2 = arr2.data();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(DataConstFunctionTestArray, Test_4) {
  const s21::array<int, 0> arr1;
  const auto ptr1 = arr1.data();
  std::array<int, 0> arr2;
  const auto ptr2 = arr2.data();
  EXPECT_EQ(ptr1, ptr2);
}

TEST(BeginFunctionTestArray, Test_1) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  ASSERT_EQ(*it1, *it2);
}

TEST(BeginConstFunctionTestArray, Test_1) {
  const s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  const std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  ASSERT_EQ(*it1, *it2);
}

TEST(BeginFunctionTestArray, Test_3) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
  auto it1 = arr1.cbegin();
  auto it2 = arr2.cbegin();
  ASSERT_EQ(*it1, *it2);
}

TEST(EndFunctionTestArray, Test_1) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
  auto it1 = arr1.end();
  --it1;
  auto it2 = arr2.end();
  --it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(EndConstFunctionTestArray, Test_2) {
  const s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  const std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
  auto it1 = arr1.end();
  --it1;
  auto it2 = arr2.end();
  --it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(CEndFunctionTestArray, Test_3) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  auto it1 = arr1.cend();
  --it1;
  auto it2 = arr2.cend();
  --it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(EmptyFunctionTestArray, Test_1) {
  auto arr1 = s21::array<int, 4>();
  auto arr2 = std::array<int, 4>();
  bool res1 = arr1.empty();
  bool res2 = arr2.empty();
  ASSERT_EQ(res1, res2);
}

TEST(EmptyFunctionTestArray, Test_2) {
  auto arr1 = s21::array<int, 0>();
  auto arr2 = std::array<int, 0>();
  bool res1 = arr1.empty();
  bool res2 = arr2.empty();
  ASSERT_EQ(res1, res2);
}

TEST(SizeFunctionTestArray, Test_1) {
  auto arr1 = s21::array<int, 6>();
  auto arr2 = std::array<int, 6>();
  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(MaxSizeFunctionTestArray, Test_1) {
  auto arr1 = s21::array<int, 6>();
  auto arr2 = std::array<int, 6>();
  ASSERT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(MaxSizeFunctionTestArray, Test_2) {
  auto arr1 = s21::array<int, 0>();
  auto arr2 = std::array<int, 0>();
  ASSERT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(SwapFunctionTestArray, Test_1) {
  s21::array<int, 4> arr1 = {0, 1, 2, 3};
  s21::array<int, 4> arr2 = {3, 2, 1, 0};
  arr1.swap(arr2);
  std::array<int, 4> arr3 = {0, 1, 2, 3};
  std::array<int, 4> arr4 = {3, 2, 1, 0};
  arr3.swap(arr4);
  for (size_t i = 0; i < arr1.size(); ++i) {
    ASSERT_EQ(arr1[i], arr3[i]);
  }
  for (size_t i = 0; i < arr2.size(); ++i) {
    ASSERT_EQ(arr2[i], arr4[i]);
  }
}

TEST(SwapFunctionTestArray, Test_2) {
  s21::array<int, 0> arr1;
  s21::array<int, 0> arr2;
  arr1.swap(arr2);
  std::array<int, 0> arr3;
  std::array<int, 0> arr4;
  arr3.swap(arr4);
  ASSERT_EQ(arr1.size(), arr3.size());
  ASSERT_EQ(arr2.size(), arr4.size());
}

TEST(FillFunctionTestArray, Test_1) {
  s21::array<int, 4> arr1 = {0, 1, 2, 3};
  std::array<int, 4> arr2 = {2, 3, 6, 9};
  arr1.fill(3);
  arr2.fill(3);
  for (size_t i = 0; i < arr1.size(); ++i) {
    ASSERT_EQ(arr1[i], arr2[i]);
  }
}

TEST(FillFunctionTestArray, Test_2) {
  s21::array<int, 0> arr1;
  std::array<int, 0> arr2;
  ASSERT_EQ(arr1.size(), arr2.size());
  arr1.fill(3);
  arr2.fill(3);
  ASSERT_EQ(arr1.size(), arr2.size());
}