// Copyer: Yanrui Hu
// Date: 2022/9/19
// Description: About the `Trie`.
// Version: 0.1
// KeyWords: Trie, cpp, data-structure, 字典树

// 这是某位大佬的算法模板库
// Trie: 字典树

#include <cstdint>
namespace OY {
struct TrieLowerMapping {
  static constexpr int range() { return 26; }
  int operator()(char __c) const { return __c - 'a'; }
};

struct TrieDefaultInfo {
  bool m_isEnd = false;
};

// 使用模板参数定义新的结构：字典树 Trie
template <typename _Mapping = TrieLowerMapping,
          typename _Info = TrieDefaultInfo, uint32_t _PoolSize = 1000000>
struct Trie {
  struct TrieNode;
  static inline _Mapping s_map = _Mapping();
  static inline TrieNode s_parent[_PoolSize];
  static inline TrieNode s_child[_PoolSize][_Mapping::range()];
  static inline _Info s_info[_PoolSize];
  static inline uint32_t s_cursor = 1;

  // 字典树上的一个节点 TrieNode
  struct TrieNode {
    uint32_t index;
    TrieNode() = default;
    explicit TrieNode(uint32_t index) : index(index) {}
    static constexpr TrieNode newNode(TrieNode parent) {
      s_parent[s_cursor] = parent;
      return s_cursor++;
    }
    static constexpr TrieNode newNode(TrieNode parent, uint32_t i) {
      s_parent[s_cursor] = parent;
      s_child[parent.index][i] = s_cursor;
      return s_cursor++;
    }
    constexpr TrieNode &parent() { return s_parent[index]; }
    constexpr TrieNode &child(uint32_t i) { return s_child[index][i]; }
    constexpr TrieNode &child(uint32_t i) const { return s_child[index][i]; }
    constexpr TrieNode &childGet(uint32_t i) {
      if (!s_child[index][i]) s_child[index][i] = newNode(*this, i);
      return s_child[index][i];
    }
    template <typename _Iterator>
    constexpr TrieNode insert(_Iterator first, _Iterator last) {
      if (first == last)
        return *this;
      else
        return childGet(s_map(*first)).insert(first + 1, last);
    }
    template <typename _Sequence>
    constexpr TrieNode insert(_Sequence &sequence) {
      return insert(sequence.begin(), sequence.end());
    }
    template <typename _Iterator>
    constexpr TrieNode find(_Iterator first, _Iterator last) const {
      if (first == last)
        return *this;
      else if (child(s_map(*first)))
        return child(s_map(*first)).find(first + 1, last);
      else
        return 0;
    }
    template <typename _Sequence>
    constexpr TrieNode find(_Sequence &sequence) const {
      return find(sequence.begin(), sequence.end());
    }
    constexpr _Info *operator->() const { return s_info + index; }
    constexpr _Info &operator*() { return s_info[index]; }
    constexpr explicit operator bool() const { return index; }
    constexpr operator uint32_t() const { return index; }
  };

  TrieNode m_root;
  Trie() : m_root(s_cursor++) {}
  template <typename _Iterator>
  TrieNode insert(_Iterator __first, _Iterator __last) {
    return m_root.insert(__first, __last);
  }
  template <typename _Sequence>
  TrieNode insert(const _Sequence &__sequence) {
    return m_root.insert(__sequence.begin(), __sequence.end());
  }
  template <typename _Iterator>
  TrieNode find(_Iterator __first, _Iterator __last) const {
    return m_root.find(__first, __last);
  }
  template <typename _Sequence>
  TrieNode find(const _Sequence &__sequence) const {
    return m_root.find(__sequence.begin(), __sequence.end());
  }
};

template <typename _Mapping = TrieLowerMapping,
          typename _Info = TrieDefaultInfo, uint32_t _PoolSize = 1000000>
Trie() -> Trie<_Mapping, _Info, _PoolSize>;
}  // namespace OY

/*作者：oldyan
链接：https://leetcode.cn/problems/k-divisible-elements-subarrays/solution/c28mszi-dian-shu-qu-zhong-by-oldyan-7j21/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/
