// Author: Yanrui Hu
// Date: 2022/10/5
// Description: Add a new `dp` problem.
// Version: 0.1
// Keywords: dp, 动态规划, 灵神, "Review this!"

// From Leetcode 2430. Maximum Deletions on a String

// References:
// [LeetCode 2430]
// --> https://leetcode.cn/problems/maximum-deletions-on-a-string/

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::vector;

const int ST = __LINE__ - 1;
#define ELOG(exp) \
  (cout << ">>>" << __LINE__ - ST << ": " #exp " " << exp << endl)
#define MAX(i, j) (i >= j ? i : j)

class Solution1 {
 public:
  int deleteString(string s) {
    int n = s.size();
    vector<vector<int>> LCP(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = n - 1; j > i; j--) {
        if (s[i] == s[j]) {
          LCP[i][j] = LCP[i + 1][j + 1] + 1;
        }
      }
    }

    vector<int> dp(n, 0);
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 1; i + 2 * j <= n; j++) {
        if (LCP[i][i + j] >= j) dp[i] = max(dp[i], dp[i + j]);
      }
      dp[i] += 1;
    }
    return dp[0];
  }
};
/* 作者：Luna_
链接：https://leetcode.cn/problems/maximum-deletions-on-a-string/solution/2430-by-luna_-q1uz/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。 */

class Solution2 {
 public:
  int deleteString(string s) {
    int n = s.length();
    if (equal(s.begin() + 1, s.end(), s.begin()))  // 特判全部相同的情况
      return n;
    int lcp[n + 1][n + 1];  // lcp[i][j] 表示 s[i:] 和 s[j:] 的最长公共前缀
    memset(lcp, 0, sizeof(lcp));
    for (int i = n - 1; i >= 0; --i) {
      for (int j = n - 1; j > i; --j) {
        if (s[i] == s[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
      }
    }
    int f[n];
    memset(f, 0, sizeof(f));
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 1; i + j * 2 <= n; ++j)
        if (lcp[i][i + j] >= j)  // 说明 s[i:i+j] == s[i+j:i+j*2]
          f[i] = max(f[i], f[i + j]);
      ++f[i];
    }
    return f[0];
  }
};

/* 作者：endlesscheng
链接：https://leetcode.cn/problems/maximum-deletions-on-a-string/solution/xian-xing-dppythonjavacgo-by-endlesschen-gpx9/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。 */

class Solution3 {
 public:
  int deleteString(string s) {
    int n = s.size();

    // 特殊处理
    char base = s[0];
    int all_equal = 1;
    for (int i = 1; i < n; ++i) {
      if (base != s[i]) {
        all_equal = 0;
        break;
      }
    }
    if (all_equal) return n;

    // 计算LCP Longest-Common-Prefix 最长公共前缀
    int LCP[n + 1][n + 1];  // LCP[i][j] 表示 s[i:] 和 s[j:] 的最长公共前缀
    memset(LCP, 0, sizeof(LCP));

    for (int i = n - 1; i >= 0; --i) {
      for (int j = n - 1; j > i; --j) {
        if (s[i] == s[j]) LCP[i][j] = LCP[i + 1][j + 1] + 1;
      }
    }
    // Note: 这里 LCP只求了上三角部分，因为在后面只需要用到上三角

    int *dp = new int[n + 1];
    memset(dp, 0, sizeof(int) * (n + 1));

    for (int i = n - 1; i >= 0; --i) {
      int maxj = (n - i) / 2;
      for (int j = 1; j <= maxj; ++j) {
        if (LCP[i][i + j] >= j) {  // 说明 s[i:i+j] == s[i+j:i+j*2]
          // if (s.substr(i, j) == s.substr(i+j, j)) { // substr(start_, len_)
          dp[i] = MAX(dp[i], dp[i + j]);
        }
      }
      dp[i] += 1;
    }
    return dp[0];
  }
};
