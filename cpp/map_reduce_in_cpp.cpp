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

int n[] = {1, 2, 3, 4};
std::cout << std::accumulate(n, n + 4, 0) << std::endl;

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
