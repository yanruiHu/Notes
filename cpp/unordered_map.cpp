/**
 * Author: Yanrui Hu
 * Date: 2022/07/02
 * Description: About priority_queue in C++.
 * Version: 0.1
 * Keywords: STL, unordered_map
 */

/**
 * 其他参考资料:
 * [C++ STL unordered_map容器用法详解]
 * --> http://c.biancheng.net/view/7231.html
 */

/* unordered_map 容器模板的定义如下所示：

template < class Key,                        //键值对中键的类型
           class T,                          //键值对中值的类型
           class Hash = hash<Key>,           //容器内部存储键值对所用的哈希函数
           class Pred = equal_to<Key>,       //判断各个键值对键相同的规则
           class Alloc = allocator< pair<const Key,T> >  // 指定分配器对象的类型
           > class unordered_map;

以上 5 个参数中，必须显式给前 2 个参数传值, 并且除特殊情况, 最多只需要使用前 4
个参数, 各自的含义和功能如表 1 所示

前 2 个参数分别用于确定键值对中键和值的类型，也就是存储键值对的类型

用于指明容器在存储各个键值对时要使用的哈希函数，默认使用 STL 标准库提供的
hash<key> 哈希函数。注意，默认哈希函数只适用于基本数据类型（包括 string
类型），而不适用于自定义的结构体或者类。
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

int main() {
  {  // 演示一般的使用方法

    //创建空 umap 容器
    unordered_map<string, string> umap;

    cout << "umap 初始桶数: " << umap.bucket_count() << endl;
    cout << "umap 初始负载因子: " << umap.load_factor() << endl;
    cout << "umap 最大负载因子: " << umap.max_load_factor() << endl;

    //设置 umap 使用最适合存储 9 个键值对的桶数
    umap.reserve(9);
    cout << "*********************" << endl;
    cout << "umap 新桶数: " << umap.bucket_count() << endl;
    cout << "umap 新负载因子: " << umap.load_factor() << endl;

    //向 umap 容器添加 3 个键值对
    umap["Python教程"] = "http://c.biancheng.net/python/";
    umap["Java教程"] = "http://c.biancheng.net/java/";
    umap["Linux教程"] = "http://c.biancheng.net/linux/";

    //调用 bucket() 获取指定键值对位于桶的编号
    cout << "以\"Python教程\"为键的键值对，位于桶的编号为:"
         << umap.bucket("Python教程") << endl;

    //自行计算某键值对位于哪个桶
    auto fn = umap.hash_function();
    cout << "计算以\"Python教程\"为键的键值对，位于桶的编号为："
         << fn("Python教程") % (umap.bucket_count()) << endl;
  }

  {  // 创建时初始化：
    unordered_map<string, string> umap{
        {"Python教程", "http://c.biancheng.net/python/"},
        {"Java教程", "http://c.biancheng.net/java/"},
        {"Linux教程", "http://c.biancheng.net/linux/"}};

    {  // 创建时调用 “复制（拷贝）构造函数”：
      unordered_map<string, string> umap2(umap);
    }

    {
        // 除此之外，C++ 11 标准中还向 unordered_map 模板类增加了移动构造函数,
        // 这里不再赘述
    }

    {
      //传入 2 个迭代器，适用于不想全部拷贝的情况
      unordered_map<string, string> umap2(++umap.begin(), umap.end());
    }
  }

  return 0;
}

/* 全部的成员方法, 用法参见 http://c.biancheng.net/view/7231.html
在 IDE里面应该可以使用提示的~

begin()
end()
cbegin()
cend()
empty()
size()
max_size()
operator[key]
at(key)
find(key)
count(key)
equal_range(key)
emplace()
emplace_hint()
insert()
erase()
clear()
swap()
bucket_count()
max_bucket_count()
bucket_size(n)
bucket(key)
load_factor()
max_load_factor()
rehash(n)
reserve()
hash_function()

对于实现互换 2 个相同类型 unordered_map 容器的键值对,
除了可以调用该容器模板类中提供的 swap() 成员方法外, STL 标准库还提供了同名的
swap() 非成员函数。
 */
