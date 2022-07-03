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
 */

#include <iostream>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;

int main() {
  { /* 最佳实践! 使用 sprintf 向一个字符数组输出数字, 浮点数会有补齐六位零 */

    char str1[20];
    double num1 = 12345.6789;
    sprintf(str1, "%lf", num1);
    printf("NO.1  %s\n", str1); // NO.1  12345.678900
  }

  { /* 使用 to_string() */
    // 浮点数会附带小数点后六位，不足补零，不推荐浮点数使用
    double num2 = 12345.6789;
    string str2 = std::to_string(num2);
    printf("NO.2  %s\n", str2.c_str()); // NO.2  12345.678900
  }

  // 使用 stringstream 可以是浮点数
  { /* 使用 stringstream 与 str() */
    double num3 = 12345.6789;
    stringstream ss;
    ss << num3;
    string str3 = ss.str();
    printf("NO.3  %s\n", str3.c_str());
  }

  { /* 使用 stringstream 与 流提取运算符 */
    double num4 = 12345.6789;
    stringstream ss;
    ss << num4;
    string str4;
    ss >> str4;
    printf("NO.4  %s\n", str4.c_str());
  }

  return 0;
}
