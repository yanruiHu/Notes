// Author: Yanrui Hu
// Date: 2022/10/13
// Description: About the monotonous stack problem.
// Version: 0.1
// Keywords: 'monotonous stack'
// Reference: https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
      // 768. 最多能完成排序的块 II
        stack<int> st;
        for (auto &num : arr) {
            if (st.empty() || num >= st.top()) {
                st.emplace(num);
            } else {
                int mx = st.top();
                st.pop();
                while (!st.empty() && st.top() > num) {
                    st.pop();
                }
                st.emplace(mx);
            }
        }
        return st.size();
    }
};

/* 作者：力扣官方题解
链接：https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/solutions/1741851/zui-duo-neng-wan-cheng-pai-xu-de-kuai-ii-w5c6/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。 */
