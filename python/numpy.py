'''
Author: Yanrui Hu
Date: 2022/7/9
Description: About numpy's usage.
Version: 0.1
Keywords: numpy, python

'''
"""其他参考资料
[Python创建二维数组的正确姿势]
--> https://zhuanlan.zhihu.com/p/88197389

[NumPy教程（快速入门版）]
--> http://c.biancheng.net/numpy/

[NumPy 中文官网]
--> https://www.numpy.org.cn/
"""


import numpy as np


def usage01():
  # 创建 ndarray 的第一种方式是利用 array 方式

  # 创建一维数组
  nd_one = np.array([1, 2, 3])
  # 创建二维数组
  nd_two = np.array([[1, 2, 3], [4, 5, 6]])

  print(nd_one)
  print(nd_two)
  print('nd_two.shape =', nd_one.shape)
  print('nd_two.shape =', nd_two.shape)

  >>> 运行结果：

  [1 2 3]
  [[1 2 3]
  [4 5 6]]
  nd_two.shape = (3,)
  nd_two.shape = (2, 3)

def usage02_1():
  # 使用arange 或 linspace 创建连续数组

  # arange() 类似Python内置函数的 range()
  # arange(初始值, 终值, 步长) 不包含终值
  x0 = np.arange(1, 11, 2)
  print(x0)

  # 创建一个 5x3 的数组
  x1 = np.arange(15).reshape((5, 3))
  print(x1)

  # linspace()线性等分向量
  # linspace(初始值, 终值, 元素个数) 包含终值
  x2 = np.linspace(1, 11, 6)
  print(x2)

  >>> 运行结果：

  [1 3 5 7 9]

  [[ 0  1  2]
  [ 3  4  5]
  [ 6  7  8]
  [ 9 10 11]
  [12 13 14]]

  [  1.   3.   5.   7.   9.  11.]


def usage02_2():
  # 使用 zeros()，ones()，full() 创建数组

  # 创建一个 3x4 的数组且所有值全为 0
  x3 = np.zeros((3, 4), dtype=int)
  print(x3)
  # 创建一个 3x4 的数组且所有元素值全为 1
  x4 = np.ones((3, 4), dtype=int)
  print(x4)
  # 创建一个 3x4 的数组，然后将所有元素的值填充为 2
  x5 = np.full((3, 4), 2, dtype=int)
  print(x5)

  >>> 运行结果：

  [[0 0 0 0]
  [0 0 0 0]
  [0 0 0 0]]

  [[1 1 1 1]
  [1 1 1 1]
  [1 1 1 1]]

  [[2 2 2 2]
  [2 2 2 2]
  [2 2 2 2]]


def usage02_3():
  # 使用 eye() 创建单位矩阵
  # eye() 创建的数组特点是行数和列数都是一样.
  # 因为它创建出来的是单位矩阵，单位矩阵是正形矩阵，对角线的值均为 1, 其他位置的值为 0

  # 创建 3x3 的单位矩阵
  x6 = np.eye(3, dtype=int)
  print(x6)

  >>> 运行结果：

  [[1 0 0]
  [0 1 0]
  [0 0 1]]


def usage02_4():
  # 使用 diag() 创建对角矩阵
  # diag() 是创建一个 NxN 的对角矩阵，对角矩阵是对角线上的主对角线之外的元素皆为 0 的矩阵。

  x7 = np.diag([1, 2, 3])
  print(x7)

  >>> 运行结果：

  [[1 0 0]
  [0 2 0]
  [0 0 3]]


def usage02_5():
  # 使用 random 创建随机数组

  # 创建 2x2 数组且所有值是随机填充
  x9 = np.random.random((2, 2))
  print(x9)

  # 创建一个值在 [0, 10) 区间的 3x3 的随机整数
  x10 = np.random.randint(0, 10, (3, 3))
  print(x10)

  >>> 运行结果：

  [[ 0.77233522  0.41516417]
  [ 0.22350126  0.31611254]]

  [[0 6 5]
  [7 6 4]
  [5 5 9]]



if __name__ == "__main__":
