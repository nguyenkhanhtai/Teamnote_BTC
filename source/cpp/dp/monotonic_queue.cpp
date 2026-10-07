#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Push strictly increasing indices; expire indices < first_valid.
  template<typename T> struct MonotoneMinQueue {
    deque<pair<int, T>> q;
    void push(int index, T value) {
      while (!q.empty() && q.back().second >= value) q.pop_back();
      q.push_back( {index, value});
    }
    void expire(int first_valid) {
      while (!q.empty() && q.front().first < first_valid) q.pop_front();
    }
    bool empty() const { return q.empty(); }
    const T&minimum()const { assert(!q.empty()); return q.front().second; }
  };
//NOTEBOOK_END
}
