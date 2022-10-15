// Author: Yanrui Hu
// Date: 2022/10/15
// Description: About vector<string> in C language.
// Keywords: review, malloc, char **
// Version: 0.1
// Refenence: https://leetcode.cn/problems/build-an-array-with-stack-operations/

#include <malloc.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **buildArray(int *target, int targetSize, int n, int *returnSize) {
  const int limit = targetSize;
  char **ans = (char **)malloc(sizeof(char *) * 2 * n);

  /* for (int j = 0; j < 2 * limit; ++j) {
      ans[j] = (char *) malloc(sizeof(char) * 5);
  } */

  int idx = 0;
  int j = 0;
  for (int i = 1; i <= n; ++i) {
    if (limit == idx) break;

    ans[j] = (char *)malloc(sizeof(char) * 5);
    strcpy(ans[j++], "Push");
    if (target[idx] == i) {
      ++idx;
    } else {
      ans[j] = (char *)malloc(sizeof(char) * 5);
      strcpy(ans[j++], "Pop");
    }
  }
  *returnSize = j;
  return ans;
}
