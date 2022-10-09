"""
Author: Yanrui Hu
Date: 2022-10-1
Description: Some medium problems' solutions from leetcode.
Keyword: leetcode, medium, example
Reason:
为了熟记一些套路！
Version: 0.0.1
"""

class Solution:
    def canTransform(self, start: str, end: str) -> bool:
        """ 777. 在LR字符串中交换相邻字符 """
        # cnt1of_x = start.count('X')
        # cnt2of_x = end.count('X')
        #
        # if cnt1of_x != cnt2of_x:
        #     return False

        # lis1 = [ch for ch in start if ch != 'X']
        # lis2 = [ch for ch in end   if ch != 'X']
        # if lis1 != lis2:
        #     return False

        n = len(start)
        i, j = 0, 0
        while 1:
            while i < n and start[i] == 'X':
                i += 1
            while j < n and end[j] == 'X':
                j += 1

            if i >= n and j >= n:
                return True
            if i >= n or j >= n or start[i] != end[j]:
                return False
            if start[i] == 'L' and i < j:
                return False
            if start[i] == 'R' and i > j:
                return False
            i += 1
            j += 1


    def scoreOfParentheses(self, s: str) -> int:
        """ 856. Score of Parentheses """
        st = [0]
        for c in s:
            if c == '(':
                st.append(0)
            else:
                v = st.pop()
                st[-1] += max(2 * v, 1)
        return st[-1]
