// Author: Yanrui Hu
// Date: 2022/10/4
// Description: Add `map`,'filter` and `reduce` in cpp.
// Version: 0.1
// Keywords: map, reduce, filter, transform, accumulate, copy_if

// References:
// [造轮子之C++中的map,filter,reduce]
// --> https://blog.csdn.net/cracker_zhou/article/details/70832923

#include <list>
using namespace std;

// C++ 中的 accumulate 第一个和第二个参数是输入的范围，第三个参数是 initial
// 使用 + 运算符进行累加操作

// 函数原型 1，使用加法运算符
// template <class InputIterator, class T>
// T accumulate (InputIterator first, InputIterator last, T init);

// 函数原型 2, 自定义运算
// template <class InputIterator, class T, class BinaryOperation>
// T accumulate (InputIterator first, InputIterator last, T init,
// BinaryOperation binary_op);
/* EXAMPLE */

// int n[] = {1, 2, 3, 4};
// std::cout << std::accumulate(n, n + 4, 0) << std::endl;
// 不带运算函数参数的std::accumulate对应的是Python 中的sum函数

// Python 中的 reduce 第一个参数是 function, 然后是一个 iterable, 最后有一个可选的 initial
// def add(x, y):
//     return x+y

// from functools import reduce
// reduce(add, [1,2,3,4])

template <typename Func, typename Container>
auto reduce(Func f, Container& container) -> decltype(Container::value_type()) {
  typedef typename Container::value_type ReturnType;
  ReturnType result = ReturnType();
  if (container.begin() != container.end()) {
    typename Container::const_iterator it;
    it = container.begin();
    for (result = *(it++); it != container.end(); ++it) {
      result = f(result, *it);
    }
  }
  return result;
}

template <typename Func, typename Container>
auto map(Func func, Container& container)
    -> std::list<decltype(func(Container::value_type))> {
  typedef std::list<decltype(func(Container::value_type()))> ReturnType;
  ReturnType result = ReturnType();
  for (typename Container::value_type value : container) {
    result.push_back(func(value));
  }
  return result;
}

template <typename Func, typename Container>
auto filter(Func func, Container& container)
    -> std::list<decltype(Container::value_type())> {
  typedef std::list<decltype(Container::value_type())> ReturnType;
  ReturnType result = ReturnType();
  for (typename Container::value_type value : container) {
    if (func(value)) {
      result.push_back(value);
    }
  }
  return result;
}
