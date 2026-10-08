#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: MonotoneMinQueue q; q.push(0,5); q.expire(0);
  // Push strictly increasing indices; expire indices < first_valid.
  struct MonotoneMinQueue {
    deque<pair<int, int>> q;
    void push(int index, int value) {
      while (!q.empty() && q.back().second >= value) q.pop_back();
      q.push_back( {index, value});
    }
    void expire(int first_valid) {
      while (!q.empty() && q.front().first < first_valid) q.pop_front();
    }
    bool empty() const { return q.empty(); }
    const int&minimum()const { assert(!q.empty()); return q.front().second; }
  };
//NOTEBOOK_END
}
