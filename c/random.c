// Author: Yanrui Hu
// Date: 2022/10/10
// Description: Generate 6 random numbers that differently to each other.
// Keywords: 面试题, 随机数生成器
// Version: 0.1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MIN = 0;
int MAX = 0x3f3f3f3f;

void set_rdm_range(int min_, int max_) {
  MIN = min_;
  MAX = max_;
}
void gen_6_rdm_nums(int arr[]) {
  srand((unsigned)time(NULL));
  for (int i = 0; i < 6; ++i) {
    arr[i] = rand() % (MAX - MIN + 1) + MIN;
    for (int j = 0; j < i; ++j) {
      if (arr[i] == arr[j]) {
        --i;
        break;
      }
    }
  }
}

int main() {
  int arr[6];
  set_rdm_range(0, 20);
  gen_6_rdm_nums(arr);

  for (int i = 0; i < 6; ++i) {
    printf("%d, ", arr[i]);
  }
  puts("");
  return 0;
}
