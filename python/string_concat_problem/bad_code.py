# line = input()
# lis = line.split()

# n = int(lis[0])
# m = int(lis[1])

from copy import deepcopy
from re import sub
from turtle import st
from typing import *


""" S = input()  # 大布料 """

# line = input()
# lis = line.split()  # 各个子串的长度

""" substr = input().split() """

# for i in range(m):
#     substr.append(input())  # 录入 m 行 子串数据

"""
leftidx = set()
rightidx = set()

for i in range(m):
    idx = S.find(substr[i])
    if idx == -1:
        print('0')
        break
    leftidx.add(idx)
    rightidx.add(idx + len(substr[i]))

leftidx.remove(0)
# rightidx.remove(len(S)) if len(s) in rightidx

if leftidx == rightidx:
    print("Leftidx == rightidx")


print("存在其他的可能性！") """

# 题目要求：
"""
给定一个长字符串 S, S 只由小写字母组成,
再给定一个字符串序列 substr, 包含 m 个字符串, 所有字符串长度的和恰好是 S 的长度
题目要求求出: 由 S 得到子字符串序列 substr 的不同方法的个数 n
"""

""" CASE 1 """
# S = 'aacaa'
# substr = ['aa','aac'] 涉及到具有包含关系的两个字串
# result = 1    只有一种剪切方式

""" CASE 2 """
# S = 'aacdcaa'
# substr = ['aa', 'cdc', 'aa'] 涉及到重复的两个字串
# result = 1    只有一种剪切方式，不考虑两个 'aa' 的位置互换带来的影响

""" CASE 3 """
# S = 'xyzxyzx'
# substr = ['zx', 'yzx', 'xy']  S 字串中'zx' 第一次出现的位置不能与 'zx' 匹配，
#                               而是与 'yzx' 匹配
# result = 1

""" CASE 4 """
S = 'aaaaaa'
substr = ['aaaa', 'aa']
# result = 2 有两种不同的剪切方式，在 index = 2 或者 4 剪切都可以，
#                       虽然得到的结果一样，但这两种方式终究是不同的

""" CASE 5 """
# S = 'xxyxxyxxyxx'
# substr = ['xxyxx', 'xxy', 'yxx']
# result = 1

startIndices = dict()

for _str in substr:
    indices: set = set()

    i = 0
    while i < len(S):
        idx = S.find(_str, i)
        if idx < 0:
            break
        indices.add(idx)
        i += 1

    startIndices[_str] = indices
    print(f'startIndices of "{_str}" is: {indices}]')

print(f'startIndices: {startIndices}')

newsubstr = sorted(substr, key=lambda s: len(startIndices[s]))

print(f'substr: {substr}')

print(f'new substr: {newsubstr}')

print('-'*50)


def seekAnswer(S: str, substr: List, startIndices: Dict):
    """
    - param1: 长字符串
    - param2: 正在搜索的字符串
    - param3: 每个字符串在`长字符串`中出现的可能位置的集合
    - Return:
    """
    ans = 0
    for _str in substr:
        for idx in startIndices[_str]:
            print(idx, end=', ')

        print()

    for idx in startIndices[substr[0]]:
        # 主要的计数变量是 targetIdx, 从 0 开始, 变化至 len(substr) - 1 结束;
        res = seek(0, list(S), substr, startIndices)
        # 当等于 len(substr) 时结束递归, 同时进行反馈, 告诉前一个栈帧, 本次的搜索结果成功!


def seek(targetIdx: int, S: List[str], substr: List[str], startIndices: Dict[str, Set[int]]) -> bool:
    """
    - param1: 想要匹配的字符串
    - param2: 长字符串
    - param3: 每个字符串在`长字符串`中出现的可能位置的集合
    - Return: 是否搜索成功?
    """
    if targetIdx == len(substr):
        global ans
        ans += 1
        print(f'targetIdx = {targetIdx}, return True')
        return True

    targetStr: str = substr[targetIdx]
    indices: Set[int] = startIndices[targetStr]  # 目标字符串对应的索引集合

    if len(indices) == 0:
        print(f'len(indices) == 0, return False')
        return False

    # 下面开始进行 for-loop, 对于集合中的每一个 idx, 我们进行一次搜索
    # 每次搜索首先要深度拷贝一份 startIndices, 防止污染 原视数据
    clone: Dict[str, Set[int]] = deepcopy(startIndices)

    print("\nIndices: ", indices)
    for idx in indices:  # 对于 targetStr 的 每一个可能的 idx 都进行一次 seek, 一次seek包括两部分: left_seek 以及 right_seek
        clone[targetStr].remove(idx)
        print(f'clone["{targetStr}"].remove({idx})\n')
        left = idx
        right = idx+len(targetStr)

        left_clone = deepcopy(clone)
        right_clone = deepcopy(clone)

        # REMOVE many idxes in some indices-sets
        print(f'idx is : {idx}, _str is:', end=' ')
        # 对于所有的 在 targetStr 序号之后的字符串, 需要在对应的 startIndices 中 删掉无效的 idx
        for _str in [substr[i] for i in range(targetIdx+1, len(substr))]: # TODO range(len(substr))
            print(f'{_str}', end=' ')  # 这一步验证获得的 _str 与期望中的一致
            _indices = clone[_str]

            # 保留合适的 _idx
            """ _indices = set(_idx for _idx in _indices if (
                _idx < left and _idx + len(_str) <= left) or (_idx >= right and _idx + len(_str) > right)) """

            _indices_left = set(_idx for _idx in _indices if (
                _idx < left and _idx + len(_str) <= left))

            _indices_right = set(_idx for _idx in _indices if (
                _idx >= right and _idx + len(_str) > right))

            left_clone[_str] = _indices_left
            right_clone[_str] = _indices_right
        print("\n")

        print(f'left_clone is:', left_clone)
        # SEEK in tow directions
        left_res: bool = seek(targetIdx+1, S[0:left], substr, left_clone)

        print(f'right_clone is:', right_clone)
        right_res: bool = seek(targetIdx+1, S[right:], substr, right_clone)

        clone[targetStr].add(idx)
        print(f'clone["{targetStr}"].add({idx})')

    print('+'*30)



if __name__ == "__main__":
    global ans
    ans = 0
    seekAnswer(S, substr, startIndices)
    print(f'\n\nans is: {ans}')
