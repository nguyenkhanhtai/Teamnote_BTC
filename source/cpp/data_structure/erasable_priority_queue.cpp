#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: ErasablePriorityQueue q; q.insert(3); // max-heap
  // erase removes one occurrence if present. O(log n) insert/erase/pop amortized.
  struct ErasablePriorityQueue {
    priority_queue<int> q,deleted; map<int,size_t> counts;
    size_t live = 0;
    void flush() {
      while (!deleted.empty() && !q.empty() && q.top() == deleted.top()) {
        q.pop(); deleted.pop();
      }
    }
    // Max-heap; negate keys for a min-heap.
    size_t size() const { return live; }
    bool empty() const { return live == 0; }
    void insert(const int& x) { q.push(x); ++counts[x]; ++live; }
    bool erase(const int& x) {
      auto it = counts.find(x);
      if (it == counts.end()) return false;
      if (!--it->second) counts.erase(it);
      deleted.push(x); --live; flush(); return true;
    }
    const int& top() { flush(); assert(live); return q.top(); }
    void pop() {
      int value = top(); q.pop(); auto it = counts.find(value);
      if (!--it->second) counts.erase(it);
      --live; flush();
    }
  };
//NOTEBOOK_END
}
