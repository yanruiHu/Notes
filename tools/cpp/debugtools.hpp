// Author: Yanrui Hu
// Date: 2022/9/15
// Description: Implement some debug tools by myself.
// Version: 0.1
// Keywords: 'print vector', debug, 'macro metaprogramming', 'enjoy it!'

// Using the macro `#` operator to get the variable's name.
// Using the unicode-table to pretty-print the vectors. It's magic!

// `printVec` and `print2Dvec` are older and can not print the vec's name.
// New macros are recommended, such as `PUTV` and `OUTV`.

// glog is very useful when you desire the 'line number' and 'execution time'.

// More references:
// [C/C++ 宏编程的艺术]
// --> https://zhuanlan.zhihu.com/p/152354031
// [C语言printf指定宽度的格式化输出]
// --> https://zhuanlan.zhihu.com/p/206738818
// [printf 官方文档]
// --> https://cplusplus.com/reference/cstdio/printf/
// [C语言数据输出大汇总以及轻量进阶] [有关 C语言 printf 函数的高级格式控制 %-]
// --> http://c.biancheng.net/view/1793.html

#ifndef __DEBUG_TOOLS__
#define __DEBUG_TOOLS__

#include <glog/logging.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

namespace tools {

template <typename T>
void printVec(const std::vector<T>& vec);

template <typename T>
void print2DVec(const std::vector<std::vector<T>>& vec);

template <typename T>
void putV(const std::vector<T>& vec, const char* name);

#define LO LOG(INFO)

#define CO(content) (std::cout << content << std::endl)

#define COV(variable) (std::cout << #variable ": " << variable << std::endl)

#define LOV(variable) (LOG(INFO) << #variable ": " << variable)

#define STRINGLIZE(ivalue) (printf(#ivalue " is: %d\n", ivalue))

#define PUTI(i64val) \
  (printf("%d: $" #i64val ": %ld \n", __LINE__, int64_t(i64val)))

#define STRLIZE(variable_name) (#variable_name)

#define AID(variable) variable, STRLIZE(variable)

#define OUTV(vec) putV(vec, #vec)

#define PUTV(vec)                                          \
  do {                                                     \
    printf("\u250E%-15.15s\u2512\n", #vec ":");            \
    printf("\u2503%s%-9lu\u2503\n", "size: ", vec.size()); \
    for (auto& i : vec) {                                  \
      CO("\u2503" << setw(14) << i << ",\u2503");          \
    }                                                      \
    printf("\u2516%15.15s\u251A\n", " ");                  \
  } while (0)

template <typename T>
void putV(const std::vector<T>& vec, const char* name) {
  printf("\u250E%-15.15s\u2512\n", name);
  printf("\u2503%s%-9lu\u2503\n", "size: ", vec.size());
  for (auto& i : vec) {
    CO("\u2503" << std::setw(14) << i << ",\u2503");
  }
  printf("\u2516%15.15s\u251A\n", " ");
}

// Specially for some Leetcode's problems.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

// TODO(baboon): Just reluctant to delete
/* class Solution {
 public:
  TreeNode* constructMaximumBinaryTree(std::vector<int>& nums) {
    return construct(nums.begin(), nums.end());
  }

  TreeNode* construct(std::vector<int>::iterator left,
                      std::vector<int>::iterator right) {
    if (left == right) return nullptr;

    auto max = max_element(left, right);

    auto lTree = construct(left, max);
    auto rTree = construct(max + 1, right);

    return new TreeNode(*max, lTree, rTree);
  }
}; */

template <typename T>
void printVec(const std::vector<T>& vec) {
  printf("\n-----PrintVec BEGIN----- \n");
  for (auto& it : vec) {
    std::cout << it << " ";
  }
  printf("\n-----PrintVec END----- \n");
}

template <typename T>
void print2DVec(const std::vector<std::vector<T>>& vec2) {
  printf("\n-----Print2DVec BEGIN----- \n");
  int i = 0;
  for (auto& vec : vec2) {
    printf("The %dth line:\n", i++);
    for (auto& it : vec) {
      std::cout << it << " ";
    }
    printf("\n");
  }
  printf("-----Print2DVec END----- \n\n");
}
}  // namespace tools

#endif
