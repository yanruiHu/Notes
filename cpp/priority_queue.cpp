/**
 * Author: Yanrui Hu
 * Date: 2022/07/02
 * Description: About priority_queue in C++.
 * Version: 0.1
 * Keywords: STL, priority_queue
 */

/**
 * 其他参考资料:
 * http://c.biancheng.net/view/480.html   C++ priority_queue(STL priority_queue)用法详解
 * http://c.biancheng.net/view/486.html   C++优先级队列存储智能指针详解
 * http://c.biancheng.net/view/7010.html  STL priority_queue底层实现（深度剖析）
 */

/* 优先级队列priority_queue()是STL中的一种容器适配器，需导入#include<queue>以使用。它具备以下特点：

一端进一端出
非先进先出的规则，而是按照优先级来排序，每次取出队列中优先级最大的元素
和队列基本操作相同:

top 访问队头元素
empty 队列是否为空
size 返回队列内元素个数
push 插入元素到队尾 (并排序)
emplace 原地构造一个元素并插入队列
pop 弹出队头元素
swap 交换内容 */

#include <functional>
#include <iostream>
#include <queue>
#include <ratio>
#include <utility>
#include <vector>

using std::cout;
using std::equal_to;
using std::greater;
using std::greater_equal;
using std::less;
using std::less_equal;
using std::not_equal_to;
using std::pair;
using std::priority_queue;
using std::ratio_greater_equal;
using std::vector;

int main() {
  priority_queue<int> que;  // top 是队列中最大的元素, 出队的顺序是降序;
  /* 默认的情况下:
  priority_queue<_Tp, std::vector<_Tp>, std::less<_Tp>> */

  /* priority_queue<Type, Container, Functional>
    Type 就是数据类型，Container
    就是容器类型（Container必须是用数组实现的容器，比如vector,deque等等，但不能用
    list。STL里面默认用的是vector），Functional 就是比较的方式。

    当需要用自定义的数据类型时才需要传入这三个参数，使用基本数据类型时，只需要传入数据类型，默认是大顶堆。
  */
  priority_queue<int, vector<int>, greater<> > que2;  // 出队的顺序是升序

  /* greater和less是std实现的两个仿函数（就是使一个类的使用看上去像一个函数。
   *  其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了）
   */

  // 下面这种写法不能使用! 自己在IDE里查看报错信息就知道了
  // for (auto& i : que) {
  // }
  // que.begin() // 不存在的

  {  // 常用的对优先队列操作的方法
    que.emplace(1);
    que.emplace(2);
    que.emplace(3);
    if (!que.empty()) {
      auto top = que.top();  // top()返回一个 const_reference
      que.pop();
    }
  }

  {  // 用pair做优先队列元素的例子
    priority_queue<pair<int, int> > que3;
    pair<int, int> p1(1, 2);
    pair<int, int> p2(1, 3);
    pair<int, int> p3(2, 5);
    que3.push(p3);
    que3.push(p2);
    que3.push(p1);
    while (!que3.empty()) {
      cout << que3.top().first << ' ' << que3.top().second << '\n';
      que3.pop();
    }
  }

  {  //用自定义类型做优先队列元素的例子
    {  //方法1

      struct tmp1  //运算符重载 < (因为 默认的less进行比较时使用的就是小于号)
      {
        int x;
        explicit tmp1(int a) { x = a; }
        bool operator<(const tmp1& a) const {
          return x < a.x;  //大顶堆
        }
      };

      priority_queue<tmp1> que4;
      tmp1 a(1);
      tmp1 b(2);
      tmp1 c(3);
      que4.push(b);
      que4.push(c);
      que4.push(a);
    }

    {  //方法2

      struct tmp1  //运算符重载 < (因为 默认的less进行比较时使用的就是小于号)
      {
        int x;
        explicit tmp1(int a) { x = a; }
      };
      struct tmp2  //重写仿函数 (内部重载了括号运算符的 class 或者 struct )
      {
        bool operator()(tmp1 a, tmp1 b) {
          return a.x < b.x;  //大顶堆
        }
      };

    priority_queue<tmp1, vector<tmp1>, tmp2> que5;
    tmp1 a(1);
      tmp1 b(2);
      tmp1 c(3);
    que5.push(b);
    que5.push(c);
    que5.push(a);
    }

  }

  {  // swap 进行队列交换

    priority_queue<int> p;  //优先队列声明
    priority_queue<int> q;  //优先队列声明
    p.push(1);              // 插入 '1' 到 p.
    p.push(2);              // 插入 '2' 到 p.
    p.push(3);              // 插入 '3' 到 p.
    p.push(4);              // 插入 '4' 到 p.
    q.push(5);              // 插入 '5' 到 q.
    q.push(6);              // 插入 '6' 到 q.
    q.push(7);              // 插入 '7' 到 q.
    q.push(8);              // 插入 '8' 到 q.
    p.swap(q);
    std::cout << "p队列元素是 : " << std::endl;
    while (!p.empty()) {
      std::cout << p.top() << std::endl;
      p.pop();
    }
    std::cout << "q优先队列元素是 :" << std::endl;
    while (!q.empty()) {
      std::cout << q.top() << std::endl;
      q.pop();
    }
  }

  return 0;
}
