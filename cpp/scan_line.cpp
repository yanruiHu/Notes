// Author: Yanrui Hu
// Date: 2022/9/16
// Description: Add a new question type.
// Version: 0.1
// Keywords: 扫描线, "Review this!"

// From Leetcode 850 矩形面积 II

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <numeric>
#include <utility>
#include <vector>

using std::pair;
using std::tuple;
using std::vector;

class Solution {
 private:
  vector<tuple<int, int>>* _lines;

  void filter(vector<int>& poses, int a, int b) {
    if (poses[0] <= a && b <= poses[2]) {
      _lines->emplace_back(poses[1], poses[3]);
    }
  }

 public:
  int rectangleArea(vector<vector<int>>& rectangles) {
    const int n = rectangles.size();
    vector<int> pos(2 * n);
    int i = 0;
    for (auto& it : rectangles) {
      pos[i++] = it[0];
      pos[i++] = it[2];
    }
    std::sort(pos.begin(), pos.end());

    std::int64_t ans = 0;

    const int n2 = 2 * n;
    for (int i = 1; i < n2; ++i) {
      int a = pos[i - 1];
      int b = pos[i];
      int width = b - a;

      if (width == 0) continue;

      vector<tuple<int, int>> lines;
      _lines = &lines;

      for_each(rectangles.begin(), rectangles.end(), this->filter);

      sort(lines.begin(), lines.end());
    }
  }
};
