"""
Author: Yanrui Hu
Date: 2022-08-xx
Description: An implementation of `cons`, `car`, `cdr`
Keywords: SICP, pairs, "abstrac data type", Magic
Reason:
下面的这些代码，是在MIT 6.001 SICP 公开课上学到的思想
cons, car, cdr 这三个的内部实现可以是很奇特的
对于使用者来说，只需要知道他们遵守的协议 (protocal), 也就是用法就足够了
"""

from math import gcd


def cons(a, b):
    """ 实现一个pair的 constructor """
    def XXX(pick):
        if pick == 985:
            return a
        elif pick == 211:
            return b

    return XXX


def car(rat):
    """ 实现 pair 的selector, 获取第1个元素 """
    return rat(985)


def cdr(rat):
    """ 实现 pair 的selector, 获取第2个元素 """
    return rat(211)


def make_rat(numerator, denominator):
    g = gcd(numerator, denominator)  # 最大公约数
    return cons((numerator // g), (denominator // g))


def numer(rat_num):
    """ 实现有理数的 selector, 获取分子 """
    return car(rat_num)


def denom(rat_num):
    """ 实现有理数的 selector, 获取分母 """
    return cdr(rat_num)


if __name__ == '__main__':
    r1 = make_rat(30, 4)
    print(type(r1))
    a1 = numer(r1)
    b1 = denom(r1)
    print(f'r1的分子: {a1}, r1的分母: {b1}')
