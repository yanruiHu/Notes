"""
Author: Yanrui Hu
Date: 2022-10-1
Description: Some hard problems' solutions from leetcode.
Keyword: leetcode, hard, example
Reason:
为了熟记一些套路！
Version: 0.0.1
"""

class Solution:
    def threeEqualParts(self, arr: List[int]) -> List[int]:
      """
      927. Three Equal Parts
      一题一解：计数 + 三指针（简洁代码）
      """
        def find(x):
            s = 0
            for i, v in enumerate(arr):
                s += v
                if s == x:
                    return i

        n = len(arr)
        cnt, mod = divmod(sum(arr), 3)
        if mod:
            return [-1, -1]
        if cnt == 0:
            return [0, n - 1]

        i, j, k = find(1), find(cnt + 1), find(cnt * 2 + 1)
        while k < n and arr[i] == arr[j] == arr[k]:
            i, j, k = i + 1, j + 1, k + 1
        return [i - 1, j] if k == n else [-1, -1]
"""
作者：lcbin
链接：https://leetcode.cn/problems/three-equal-parts/solution/by-lcbin-7ir1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。 """
