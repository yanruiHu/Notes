# 字典树
# Leetcode 2146
# https://leetcode.cn/problems/sum-of-prefix-scores-of-strings/
class Node:
	__slots__ = 'son', 'score', 'ids'

	def __init__(self):
		self.son = defaultdict(Node)
		self.score = 0
		self.ids = []


class Solution:
	def sumPrefixScores(self, words: List[str]) -> List[int]:
		"""
		1. trie 可以视作一颗多叉树（26叉树）
		字符串 word 的分数等于以 word 作为前缀的 words[i] 的数目
		2. 经过 x （x 也是一个前缀）的字符串的个数
		3. 时间复杂度：节点个数至多为所有字符串的长度之和
		"""
		root = Node()
		for i, word in enumerate(words):
			cur = root
			for c in word:
				# if cur.son[c] == null: cur.son[c] = new Node()
				cur = cur.son[c]
				cur.score += 1
			cur.ids.append(i)

		# words[i] 的每个非空前缀的分数总和
		# 在trie上DFS, 走到字符串末尾时的路径分数之和
		ans = [0] * len(words)
		def dfs(node, sum):
			if node is None: return
			sum += node.score
			for i in node.ids:
				ans[i] = sum
			for child in node.son.values():
				dfs(child, sum)

		def(root, 0)
		return ans
