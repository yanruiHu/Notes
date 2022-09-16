'''
Author: Yanrui Hu
Date: 2022/9/16
Description: About numpy's usage.
Version: 0.1
Keywords: scan_line, python, "haven't seen"

'''

# Leetcode 850 矩形面积 II
# Keywords: 扫描线

"""
You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner.

Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.

Return the total area. Since the answer may be too large, return it modulo 109 + 7.

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/rectangle-area-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""

class Solution:
    def rectangleArea(self, rectangles: List[List[int]]) -> int:
        pos = []
        for poses in rectangles:
            pos.extend([poses[0], poses[2]])
        pos.sort()
        ans = 0
        for i in range(1, len(pos)):
            a, b = pos[i-1], pos[i]
            width = b - a
            if width == 0:
                continue
            lines = [(poses[1], poses[3]) for poses in rectangles if poses[0] <= a and b <= poses[2]]
            lines.sort() # 这一步我们得到了很多属于矩形的高度区间
            # 下一步是计算这些高度区间的`积分`, 也就是覆盖的长度和
            height, l, r = 0, -1, -1
            for cur in lines:
                if cur[0] > r:
                    height += r-l
                    l, r = cur
                elif cur[1] > r:
                    r = cur[1] # 扩展右边界，这个妙啊

            height += r-l
            ans += height * width

        return ans % int(1e9+7)
