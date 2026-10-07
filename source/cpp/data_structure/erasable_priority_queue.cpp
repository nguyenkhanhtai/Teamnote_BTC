#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // erase removes one occurrence if present. O(log n) insert/erase/pop amortized.
  template<typename T,typename Compare=less<T>>struct ErasablePriorityQueue {
    priority_queue<T,vector<T>,Compare>q,deleted; map<T,size_t,Compare>counts;
    size_t live = 0;
    void flush() {
      while (!deleted.empty() && !q.empty() && q.top() == deleted.top()) {
        q.pop(); deleted.pop();
      }
    }
    explicit ErasablePriorityQueue(Compare cmp=Compare {}):q(cmp),deleted(cmp),counts(cmp){}
    size_t size() const { return live; }
    bool empty() const { return live == 0; }
    void insert(const T& x) { q.push(x); ++counts[x]; ++live; }
    bool erase(const T& x) {
      auto it = counts.find(x);
      if (it == counts.end()) return false;
      if (!--it->second) counts.erase(it);
      deleted.push(x); --live; flush(); return true;
    }
    const T& top() { flush(); assert(live); return q.top(); }
    void pop() {
      T value = top(); q.pop(); auto it = counts.find(value);
      if (!--it->second) counts.erase(it);
      --live; flush();
    }
  };
//NOTEBOOK_END
}
