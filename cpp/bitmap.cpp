// Author: Yanrui Hu
// Date: 2022/9/22
// Description: Add a new data structure.
// Version: 0.1
// Keywords: bitmap, 位图, "Review this!"

// From Leetcode 698. 划分为k个相等的子集

// References:
// [C++ 位图及位图的实现]
// --> https://blog.csdn.net/qq_44443986/article/details/117359908

#include <glog/logging.h>

#include <cstddef>
#include <ios>
#include <vector>

#define ELOG(exp) (LOG(INFO) << #exp ": " << std::boolalpha<< exp)

using std::vector;

/* 提供初始化容量大小，查找，标记与取消标记的功能 */
class BitMap {
 public:
  //位图的内存大小和数据范围有关
  explicit BitMap(size_t range)
      : _bit(range / 32 + 1)  // 因为 int 是 32位的
  {}

  void set(const size_t num) {
    //计算数组中的下标
    int idx = num / 32;
    //计算num在对应下标整数中的下标位置
    int bitIdx = num % 32;
    //将对应的比特位置1
    _bit[idx] |= 1 << bitIdx;  // a |= 1 << k 将int型变量a的第k位 置1
  }

  bool find(const size_t num) {
    int idx = num / 32;
    int bitIdx = num % 32;
    return (_bit[idx] >> bitIdx) & 1;  // a >> k & 1 获取int型变量a的 第k位
  }

  void reset(const size_t num) {
    int idx = num / 32;
    int bitIdx = num % 32;
    _bit[idx] &= ~(1 << bitIdx);  // a &= ~(1 << k) 将int型变量a的第k位 置0
  }

 private:
  vector<int> _bit;
};

void test() {
  BitMap bit(512); // 512 除以32 得到 16，可以整除，所以 bit内部的 idx 最大可以是16
  bit.set(1);
  bit.set(13);

  bit.set(14);
  ELOG(bit.find(14)); // 应该可以找到

  bit.reset(14);
  ELOG(bit.find(14)); // 应该找不到了


  bit.set(520);  // 520 / 32 == 16； 520 % 32 == 8
  // 虽然 520 看似超过了 所谓的最大范围512，但其实考虑 BitMap的内部实现，我们可以发现
  // 当 range == 512 时， _bit 可以存储 17 个int整数, 最大的范围其实是 17 * 32 == 544
  ELOG(bit.find(520));

  ELOG(bit.find(15));

}

int main() {
  test();
  return 0;
}
