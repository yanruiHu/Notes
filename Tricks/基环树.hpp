#ifndef __BASE_RING_TREE__
#define __BASE_RING_TREE__

#include <map>
#include <vector>

using std::map;
using std::vector;

class BaseRingTree {
 private:
  map<int, int>
      reach1;  // (idx, distance) 节点1 能够抵达的节点编号 及其对应的距离
  map<int, int>
      reach2;  // (idx, distance) 节点2 能够抵达的节点编号 及其对应的距离
  char* mark1;  // 对节点是否在节点1前进路线上的标记， 0: 未访问 1: 已访问 2:
                // 在环上
  char* mark2;  // 对节点是否在节点2前进路线上的标记， 0: 未访问 1: 已访问 2:
                // 在环上
  int size;     // 节点数量
  int node1x;   // 节点1 对应的树枝(可能) 与环的交点
  int node2x;   // 节点2 对应的树枝(可能) 与环的交点
  int intersectPoint1;  // 交叉点1
  int intersectPoint2;  // 交叉点2
  int larger1;          // 交叉点1 对应的两个距离中的较大值
  int larger2;          // 交叉点2 对应的两个距离中的较大值

  // 初始化数据 [side-effect]
  inline void init(const vector<int>& edges);

  // 依次访问 node1 的后继节点 [side-effect]
  inline void visit1(const vector<int>& edges, int node1);

  // 依次访问 node2 的后继节点 [side-effect]
  inline void visit2(const vector<int>& edges, int node2);

  // 设定 node1x [side-effect]
  inline void setNode1x(int i);

  // 访问 node1 的后继节点 [side-effect]
  inline void node1Access(int i);

  // 访问 node1 能够到达的环上的节点 [side-effect]
  inline void ring1Access(const vector<int>& edges, int i);

  // 设定 node2x [side-effect]
  inline void setNode2x(int i);

  // 访问 node2 的后继节点 [side-effect]
  inline void node2Access(int i);

  // 访问 node2 能够到达的环上的节点 [side-effect]
  inline void ring2Access(const vector<int>& edges, int i);

  // 从 node1 出发是否可以访问到 i 节点 [NOSE]
  bool node1Reach(int i);

  // 从 node2 出发是否可以访问到 i 节点 [NOSE]
  bool node2Reach(int i);

  // 从 node1x 到 node2x 的距离 [NOSE]
  int disNode1xToNode2x();

  // 从 node2x 到 node1x 的距离 [NOSE]
  int disNode2xToNode1x();

  // 从 source 出发 是否能够到达 target [NOSE]
  bool canReach(const vector<int>& edges, int source, int target);

  // 获取交叉点的序号 [NOSE]
  // 当 node1x 和 node2x 在一个环上时，其中一个点一定是题目所求的交叉点
  // 通过比较 disNode1xToNode2x 和 disNode2xToNode1x 来确定交叉点
  int getIntersectPoint();

 public:
  // 找到最佳的相遇点，返回相遇点的编号，如果没有相遇点，返回-1；
  // 如果有多个答案，返回 最小 的节点编号
  // 最佳相遇点：
  //   1. node1 和 node2 都可以抵达
  //   2. node1 和 node2 到此点的距离尽量都最小
  //   3. 在 2. 的基础上，最小化两个距离之中的较大值
  int closestMeetingNode(vector<int>& edges, int node1, int node2);
};

#endif
