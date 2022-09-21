from typing import List, Set


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
# substr = ['aa', 'cdc', 'aa'] # 涉及到重复的两个字串
# result = 1    只有一种剪切方式，不考虑两个 'aa' 的位置互换带来的影响

""" CASE 3 """
# S = 'xyzxyzx'
# substr = ['zx', 'yzx', 'xy'] # S 字串中'zx' 第一次出现的位置不能与 'zx' 匹配，
#                               而是与 'yzx' 匹配
# result = 1

""" CASE 4 """
# S = 'aaaaaa'
# substr = ['aaaa', 'aa']
# result = 2 有两种不同的剪切方式，在 index = 2 或者 4 剪切都可以，
#                       虽然得到的结果一样，但这两种方式终究是不同的

""" CASE 5 """
S = 'xxyxxyxxyxx'
substr = ['xxyxx', 'xxy', 'yxx']
# result = 1


res_set: Set = set()
g_list: List[int] = list()


def sol(S: str, substr: List[str], i: int) -> bool:
    if i < 0 or i >= len(substr):
        return False

    start = 0
    l = len(substr[i])
    while True:
        idx = S.find(substr[i], start)  # get index

        if idx == -1:
            return False

        g_list.append(idx)
        new_S = S[:idx] + S[idx:idx+l].upper() + S[idx+l:]  # convert
        # new_S 与 S 相互独立

        if i == endIdx:
            res_set.add(tuple(sorted(g_list)))
            g_list.pop()
            return True

        sol(new_S, substr, i+1)

        g_list.pop()
        start += 1


if __name__ == '__main__':
    endIdx = len(substr) - 1
    sol(S, substr, 0)
    print(res_set)
    print(f'Answer is: {len(res_set)}')

# 下面的部分只是为了观察一个特性

# li1 = [1111, 2222, 333, 4, 55555, -6, -7.1, -8, 9999, 10]
# li2 = [-8, 9999, 10, 1111, -7.1, -6, 55555, 4, 333, 2222]

# sorted(li1) == sorted(li2) # True
# tuple(set(li1)) == tuple(set(li2))

# 可以使用全排列进行实验。我猜测这只是编译器实现的巧合而已。标准中应该没有这一条规则……
