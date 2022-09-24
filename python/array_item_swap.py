"""
Author: Yanrui Hu
Date: 2022-04-04
Description: Test case for swaping the array items.(交换数组元素的测试)
Keywords: python-list, swap-list-item, notice-occur-order
Reason: 这是某一天和车泽宇进行讨论时整理的东西, Python 的交换比较优雅, 但是有坑
"""


# TEST 1
nums = [1,2,3,4,5]
i = 0
nums[i], nums[nums[i]] = nums[nums[i]], nums[i]

print(nums)

# TEST 2
nums = [1,2,3,4,5]
i = 0
nums[nums[i]], nums[i] = nums[i], nums[nums[i]]
print(nums)

# TEST 3
nums = [1,2,3,4,5]
i = 0
nums[nums[nums[i]]], nums[nums[i]], nums[i] = nums[i], nums[nums[i]], nums[nums[nums[i]]]
print(nums)

# TEST 4
nums = [1,2,3,4,5]
i = 0
nums[i], nums[nums[i]], nums[nums[nums[i]]] = nums[nums[nums[i]]], nums[nums[i]], nums[i]
print(nums)

# TEST 5
nums = [1,2,3,4,5]
i = 0
i ,nums[i], nums[nums[i]], nums[nums[nums[i]]] = nums[nums[nums[i]]], nums[nums[i]], nums[i], i
print(nums)


class Solution:
    def findNumberIn2DArray(self, matrix: List[List[int]], target: int) -> bool:
        if (matrix == None or len(matrix) == 0 or len(matrix[0]) == 0):
            return False
        rowmax = len(matrix)
        colmax = len(matrix[0])

        row = 0
        col = colmax - 1
        while row < rowmax and col >= 0:
            if matrix[row][col] < target:
                row += 1
            elif matrix[row][col] > target:
                col -= 1
            else:
                return True
        return False
