/**
 * Author: Yanrui Hu
 * Date: 2022/07/01
 * Description: About some ways to convert string to numbers in C++.
 * Version: 0.1
 * Keywords: sscanf, stringstream, std::stoi, std::stof, atoi
 */

/**
 * 其他参考资料
 * [C++stringstream的妙用]
 *  --> https://blog.csdn.net/liuweiyuxiang/article/details/89070296
 * [stringstream的用法]
 *  --> https://zhuanlan.zhihu.com/p/44435521
 */

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;

int main() {
  { /* 最佳实践! 使用 sscanf 从一个字符串里面读取指定格式的内容! */

    char str1[] = "abcd123456";
    int num1;
    int res1 = sscanf(str1, "abcd%d", &num1);
    printf("NO.1  %d %d\n", res1, num1);  // NO.1  1 123456
  }

  { /* 一个流式风格的API, 使用 stringstream 和 >> 进行数字的获取 */

    // stringstream ss("123"); // OK! get 123
    // stringstream ss("-123"); // OK! get -123
    // stringstream ss("a123"); // ERROR! get 0
    stringstream ss("0");  // OK! get 0 . BUT! why you can believe it did get 0
                           // not because of meeting no-digit character ?
    int num2;
    ss >> num2;
    printf("NO.2  %d\n", num2);  // NO.2  0

    /* 可以看到, 对于小数也同样可以使用 */
    string str2 = "123.456";
    stringstream sss(str2);
    double num3 = 0.0;
    sss >> num3;
    printf("NO.3  %lf\n", num3);  // NO.3  123.456000
  }

  { /* std::sto* 系列的使用 */

    string str4("1234b");
    int num4 = std::stoi(
        str4);  // OK! get 1234, ignore 'b', but "a1234" will not be accepted!

    string str5("123.45678910");
    double num5 = std::stod(str5);

    string str6("123.45678910");
    float num6 = std::stof(str6);

    string str7("9876543210");
    int64_t num7 = std::stoll(str7);

    printf("NO.4  %d,  %lf,  %f, %ld\n", num4, num5, num6, num7);
    // NO.4  1234,  123.456789,  123.456787, 9876543210
  }

  { /* 补充: atoi 与 stoi*/
    // stoi 是C++ 11引入的, 没有向下的兼容性!
    // atoi（）仅适用于C风格的字符串（字符数组和字符串文字）而且最重要的一点是,
    // 它不是C语言标准的一部分, 部分平台可能没有实现这个函数;
    // stoi（）适用于 C++字符串 和 C风格的字符串 int atoi(const char * str)

    // stoi（）最多可以包含三个参数，第二个参数用于起始索引，第三个参数用于输入数字的基数。
    // int stoi (const string&  str, size_t* idx = 0, int base = 10);
    // int stoi (const wstring& str, size_t* idx = 0, int base = 10);
  }

  return 0;
}
