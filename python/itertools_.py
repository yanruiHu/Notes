"""
Author: Yanrui Hu
Date: 2022-9-30
Description: About the permutations and combinations in `itertools` module.
Keywords: itertools, permutations, combinations, product, utility, convenience
Reason:
这些代码在做Leetcode题目时可以提速
Reference: https://zhuanlan.zhihu.com/p/473353113
"""

from itertools import product
from itertools import combinations
from itertools import permutations
from itertools import combinations_with_replacement


# 使用两个序列进行排列组合
for e in product('AB', 'CD'):
    print(''.join(e), end=', ') # AC, AD, BC, BD,
print('\n---------')

# 使用一个序列、重复2次进行全排列
for e in product('AB', repeat=2):
    print(''.join(e), end=', ') # AA, AB, BA, BB,
print('\n---------')

# 从序列中取2个元素进行排列
for e in permutations('ABCD', 2):
    print(''.join(e), end=', ') # AB, AC, AD, BA, BC, BD, CA, CB, CD, DA, DB, DC,
print('\n---------')

# 从序列中取2个元素进行组合、元素不允许重复
for e in combinations('ABCD', 2):
    print(''.join(e), end=', ') # AB, AC, AD, BC, BD, CD,
print('\n---------')

# 从序列中取2个元素进行组合、元素允许重复
for e in combinations_with_replacement('ABCD', 2):
    print(''.join(e), end=', ') # AA, AB, AC, AD, BB, BC, BD, CC, CD, DD,
print('\n---------')

# C(5, 2) 的实现
combins = [c for c in combinations(range(5), 2)]

# A(5, 2) 的实现
permuts = [p for p in permutations(range(5), 2)]

# Tips: 使用 iterator 或者  generator 可以提高性能
