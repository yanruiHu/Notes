#include "基环树.hpp"

#include <memory.h>

inline void BaseRingTree::init(const vector<int>& edges) {
  reach1 = {};
  reach2 = {};
  size = edges.size();
  mark1 = new char[size];
  mark2 = new char[size];
  bzero(mark1, size);
  bzero(mark2, size);
  node1x = -1;
  node2x = -1;
  intersectPoint1 = -1;
  intersectPoint2 = -1;
  larger1 = -1;
  larger2 = -1;
}

// 依次访问 node1 的后继节点
inline void BaseRingTree::visit1(const vector<int>& edges, int node1) {
  int distance = 0;
  // mark1[node1] = 1; // 设置为已访问
  node1Access(node1);
  if (mark1[node1] == 1) {
    reach1.emplace(node1, distance);  // 只有初次访问时才添加到 map 中
  }

  for (int i = edges[node1]; i != -1; i = edges[i]) {
    node1Access(i);
    if (mark1[i] == 1) {
      reach1.emplace(i, ++distance);
    } else if (mark1[i] == 2) {  // 此节点是环的一部分
      setNode1x(i);
      ring1Access(edges, i);
    }
  }
}

// 依次访问 node2 的后继节点
inline void BaseRingTree::visit2(const vector<int>& edges, int node2) {
  int distance = 0;
  node2Access(node2);
  if (mark2[node2] == 1) {
    reach2.emplace(node2, distance);  // 只有初次访问时才添加到 map 中
  }

  for (int i = edges[node2]; i != -1; i = edges[i]) {
    node2Access(i);
    if (mark2[i] == 1) {
      reach2.emplace(i, ++distance);
    } else if (mark2[i] == 2) {  // 此节点是环的一部分
      setNode2x(i);
      ring2Access(edges, i);
    }
  }
}

// 设定 node1x
inline void BaseRingTree::setNode1x(int i) { node1x = i; }

// 访问 node1 的后继节点
inline void BaseRingTree::node1Access(int i) { ++mark1[i]; }

// 访问 node1 能够到达的环上的节点
inline void BaseRingTree::ring1Access(const vector<int>& edges, int i) {
  int p = edges[i];
  while (p != i) {
    node1Access(p);
    p = edges[p];
  }
}

// 设定 node2x
inline void BaseRingTree::setNode2x(int i) { node2x = i; }

// 访问 node2 的后继节点
inline void BaseRingTree::node2Access(int i) { ++mark2[i]; }

// 访问 node2 能够到达的环上的节点
inline void BaseRingTree::ring2Access(const vector<int>& edges, int i) {
  int p = edges[i];
  while (p != i) {
    node2Access(p);
    p = edges[p];
  }
}

bool BaseRingTree::node1Reach(int i) { return reach1.find(i) != reach1.end(); }

bool BaseRingTree::node2Reach(int i) { return reach2.find(i) != reach2.end(); }

int BaseRingTree::disNode1xToNode2x() {
  if (node1x == -1 || node2x == -1) {
    return -1;
  }
  if (!node1Reach(node2x) || !node2Reach(node1x)) {
    return -1;
  }
  return reach1[node2x] - reach1[node1x];
}

int BaseRingTree::disNode2xToNode1x() {
  if (node1x == -1 || node2x == -1) {
    return -1;
  }
  if (!node1Reach(node2x) || !node2Reach(node1x)) {
    return -1;
  }
  return reach2[node1x] - reach1[node2x];
}

// 从 source 出发 是否能够到达 target
bool BaseRingTree::canReach(const vector<int>& edges, int source, int target) {
  if (source == target) {
    return true;
  }
  int p = edges[source];
  while (p != -1 && p != source) {
    if (p == target) {
      return true;
    }
    p = edges[p];
  }
  return false;
}

// 当 node1x 和 node2x 在一个环上时，其中一个点一定是题目所求的交叉点
// 通过比较 disNode1xToNode2x 和 disNode2xToNode1x 来确定交叉点
int BaseRingTree::getIntersectPoint() {
  if (node1x == -1 || node2x == -1) {
    return -1;
  }
  int dis1 = disNode1xToNode2x();
  int dis2 = disNode2xToNode1x();
  if (dis1 == -1 || dis2 == -1) {
    return -1;
  }
  if (dis1 > dis2) {
    return node1x;
  } else if (dis1 < dis2) {
    return node2x;
  } else {
    return std::min(node1x, node2x);
  }
}

int BaseRingTree::closestMeetingNode(vector<int>& edges, int node1, int node2) {
  if (node1 == node2) {  // 如果两个节点是同一个节点，相遇点就是这个节点
    return node1;
  }
  if (edges[node1] == -1 &&
      edges[node2] == -1) {  // 如果两个节点都没有后继节点，那么相遇点不存在
    return -1;
  }
  init(edges);
  visit1(edges, node1);
  visit2(edges, node2);

  if (node1Reach(node2) && node2Reach(node1)) {  //两个节点都在同一个环上
    return getIntersectPoint();
  }

  if (node1Reach(node2)) {
    if (node1x == -1 ||
        !canReach(
            edges, node1x,
            node2)) {  // 没有成环，或者 node1x 不能到达 node2(node2 不在环上)
      return node2;
    } else {
      return getIntersectPoint();
    }
  }
  if (node2Reach(node1)) {
    if (node2x == -1 ||
        !canReach(
            edges, node2x,
            node1)) {  // 没有成环，或者 node2x 不能到达 node1(node1 不在环上)
      return node1;
    } else {
      return getIntersectPoint();
    }
  }

  if (node1x != -1 && !node2Reach(node1x)) {
    return -1;
  }
  if (node2x != -1 && !node1Reach(node2x)) {
    return -1;
  }

  return -1;
}
