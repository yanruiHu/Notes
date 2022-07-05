/**
 * Author: Yanrui Hu
 * Date: 2022/07/03
 * Description: About some ways to convert numbers to string in C++.
 * Version: 0.1
 * Keywords: sprintf, stringstream, std::to_string
 */

/**
 * 其他参考资料
 *
 * [C++stringstream的妙用]
 * --> https://blog.csdn.net/liuweiyuxiang/article/details/89070296
 * [stringstream的用法]
 * --> https://zhuanlan.zhihu.com/p/44435521
 *
 *
 * [流操作算子] 有两篇,都差不多
 * [C++ 格式化输出（输出格式）完全攻略]
 * --> http://c.biancheng.net/view/275.html
 * [C++ cout格式化输出（超级详细）]
 * --> http://c.biancheng.net/view/7578.html
 *
 * [C语言数据输出大汇总以及轻量进阶] [有关 C语言 printf 函数的高级格式控制 %-]
 * --> http://c.biancheng.net/view/1793.html
 *
 * [printf 官方文档]
 * --> https://cplusplus.com/reference/cstdio/printf/
 */

#include <iomanip>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;

int main() {
  { /* 最佳实践! 使用 sprintf 向一个字符数组输出数字, 浮点数默认会有补齐六位零
     * 所以最好使用 %m.nlf的形式
     */

    char str1[20];
    double num1 = 12345.6789;
    sprintf(str1, "%lf", num1);
    printf("NO.1  %s\n", str1);  // NO.1  12345.678900

    sprintf(str1, "%5.4lf", num1);
    printf("NO.1  %s\n", str1);  // NO.1  12345.6789
  }

  { /* 使用 to_string() */
    // 浮点数会附带小数点后六位，不足补零，不推荐浮点数使用
    double num2 = 12345.6789;
    string str2 = std::to_string(num2);
    printf("NO.2  %s\n", str2.c_str());  // NO.2  12345.678900
  }

  /** 使用 stringstream 可以是浮点数,
   * 使用"流操纵算子"可以控制数字输入时在内部转换成的字符串的格式, 如
   * ss << std::fixed << std::setprecision(6);
   * 可以设置以普通小数形式输出浮点数, 且保留六位小数.
   */

  { /* 使用 stringstream 与 str() */
    double num3 = 12345.6789;
    stringstream ss;
    ss << std::fixed << std::setprecision(6);  // 这个好多教程不提！挺坑人的！
    ss << num3;
    string str3 = ss.str();  // stringstream 的 str() 方法可以获取 stringstream
                             // 内部的字符串, 如果传入参数"", 则会清空
                             // stringstream 里面的内容
    printf("NO.3  %s\n", str3.c_str());
    // NO.3  12345.678900 ( 如果没有进行 fixed 和
    // setprecision(6) 的设置， 这一步的结果将是 12345.7 !!! )
  }

  { /* 使用 stringstream 与 流提取运算符 */
    double num4 = 12345.6789;
    stringstream ss;
    // ss << std::scientific << std::setprecision(6);
    // 注意! 必须在设置好 ss的格式以后再把数字输出到 ss |
    ss << num4;  // <----------------------------- << 是流插入运算符,
                 // 用来把数字输出到 ss
    string str4;
    ss >> str4;  // <----------------------------- >> 是流提取运算符, 用来从 ss
                 // 中提取数字
    printf("NO.4  %s\n", str4.c_str());
    // NO.4  1.234568e+04 ( 如果没有进行 fixed 和
    // setprecision(6) 的设置， 这一步的结果将是 12345.7 !!!)
  }

  return 0;
}

/*

printf() 格式控制符的完整形式如下：

  %[flag][width][.precision]type

  [] 表示此处的内容可有可无，是可以省略的。

 */
