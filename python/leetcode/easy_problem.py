"""
Author: Yanrui Hu
Date: 2022-10-1
Description: Some easy problems' solutions from leetcode.
Keyword: leetcode, easy, example
Reason:
为了熟记一些套路！
Version: 0.0.1
"""

class Solution:
    def reformatNumber(self, number: str) -> str:
        '''1694. 重新格式化电话号码'''
        new_num_lis = [ch for ch in number if ch != '-' and ch != ' ']
        cnt = 0
        n = len(new_num_lis)
        cnt, rest = divmod(n, 3)

        if rest == 1:
            cnt -= 1
            rest += 3
        # rest may be 0, 2, 4
        res = []
        for i in range(0, cnt):
            res.append("".join(new_num_lis[i*3:i*3+3]))

        if rest == 4:
            res.append("".join(new_num_lis[n-4:n-2]))
            rest -= 2

        if rest == 2:
            res.append("".join(new_num_lis[n-2:]))

        return "-".join(res)
