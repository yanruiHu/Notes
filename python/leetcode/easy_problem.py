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
        def checkOnesSegment(self, s: str) -> bool:
        """ 1784. 检查二进制字符串字段 """
        lidx = s.find('1')
        ridx = s.rfind('1')
        while s[lidx+1] == '1':
            lidx += 1

        return ridx == lidx
        # return '01' not in s #  最快速的方式！！！


    def minDistance(self, word1: str, word2: str) -> int:
        """ 72. 编辑距离 """
        m = len(word1)
        n = len(word2)
        # dp = [[0] * (n+1) for i in range(m+1)]
        dp = np.zeros((m+1, n+1), dtype=np.int)  # 这是另一种创建二维列表的方式

        for i in range(1, m + 1):
            dp[i][0] = i
        for j in range(1, n + 1):
            dp[0][j] = j
        info(f"dp: {dp}")

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
                    info(f'dp[{i}][{j}]: {dp[i][j]}')
                else:
                    dp[i][j] = min(
                        dp[i - 1][j] + 1,
                        dp[i][j - 1] + 1,
                        dp[i - 1][j - 1] + 1
                    )
                    info(f'dp[{i}][{j}]: {dp[i][j]}')

        return dp[m][n]


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
