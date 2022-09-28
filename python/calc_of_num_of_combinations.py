"""
Author: Yanrui Hu
Date: 2022-09-xx
Description: Two implementations of C(n, m)
Keywords: `combination numbers`, Magic
Reason:
下面的这些代码，是在做力扣题目时整理的，特别感谢cjh的帮助
"""


from collections import defaultdict
import collections
import functools
from typing import List


p = int(1e9+7)

# 第一种 C(n, m) 实现方式


@functools.lru_cache(maxsize=2**20)
def C(n: int, m: int) -> int:
    """ 在 (mod p) 意义上, 组合数C(n, m) """
    assert n >= 0 and m >= 0
    if m > n:
        return 0
    if m == 0:
        return 1
    return (C(n - 1, m - 1) + C(n - 1, m)) % p


class Solution:
    def longestNiceSubarray(self, nums: List[int]) -> int:
        """ https://leetcode.cn/problems/longest-nice-subarray/ """
        l = 0
        t = [0 for _ in range(32)]
        ans = 1
        for i in range(len(nums)):
            for j in range(32):
                if (nums[i] >> j) & 1 == 1:
                    t[j] = t[j] + 1
            while len([0 for j in t if j > 1]) != 0:
                for j in range(32):
                    if (nums[l] >> j) & 1 == 1:
                        t[j] = t[j] - 1
                l = l + 1
            ans = max(ans, i - l + 1)
        return ans


class SolutionA:

    def numberOfWays(self, startPos: int, endPos: int, k: int) -> int:
        d = abs(endPos - startPos)
        if (k - d) & 1 == 1:
            return 0
        return C(k, (d + k) / 2)


@functools.lru_cache(maxsize=2**20)
def inv(n: int) -> int:
    """ 在 (mod p) 意义上, n 的除法逆元 """
    return pow(n, p - 2, p)


@functools.lru_cache(maxsize=2**20)
def factorial(a: int) -> int:
    """ 在 (mod p) 意义上, a 的阶乘 a! """
    assert a >= 0
    if a == 0:
        return 1
    return a * factorial(a - 1) % p


@functools.lru_cache(maxsize=2**20)
def inv_f(n: int) -> int:
    """ 在 (mod p) 意义上, n的阶乘的乘法逆元"""
    return inv(factorial(n))


# 第二种 C(n, m) 实现方式

@functools.lru_cache(maxsize=2**20)
def C(n: int, m: int) -> int:
    """ 在 (mod p) 意义上, 组合数C(n, m) """
    assert n >= 0 and m >= 0
    if m > n:
        return 0
    if m == 0:
        return 1
    # return (C(n - 1, m - 1) + C(n - 1, m)) % p
    return factorial(n) * inv_f(m) % p * inv_f(n - m) % p


class Solution:
    def countNicePairs(self, nums: List[int]) -> int:
        """ 计算好的Pair """
        def rev(a: int) -> int:
            """ 翻转一个数字, 如 "1230" --> "321" """
            x = a
            ans = 0
            while x != 0:
                pre, last = divmod(x, 10)
                ans *= 10
                ans += last
                x = pre
            return ans
        key_count = defaultdict(int)  # 从字典里面取值的时候, 每一个键都保证有值, 默认值是调用无参工厂函数得到的
        for i, v in enumerate(nums):
            key = v - rev(v)
            # print(key_count[key])
            key_count[key] += 1
            # print("AFTRE", key_count[key])

        total: int = 0
        for count in key_count.values():
            total += C(count, 2)  # 这一步可以优化的, C(n, 2) = (n-1) * n // 2
            if total >= p:
                # _, total = divmod(total, p)
                total %= p

        return int(total)


if __name__ == '__main__':
    pass
