#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // f starts at 0. Represents convex piecewise-linear f, slopes integral.
  struct SlopeTrick {
    priority_queue<long long> left;
    priority_queue<long long,vector<long long>,greater<long long>>right;
    long long lshift = 0, rshift = 0, value = 0;
    long long minimum() const { return value; }
    // Minimizers [left endpoint,right endpoint]; missing endpoints mean infinity.
    pair<optional<long long>, optional<long long>> minimizers() const {
      return {
        left.empty()?nullopt:optional<long long>(left.top()+lshift),right.empty()?nullopt:optional<long long>(right.top()+rshift)
      };
    }
    void add_x_minus_a(long long a) {
      if (!left.empty() && left.top() + lshift > a) {
        long long x=left.top()+lshift; left.pop(); value+=x-a; left.push(a-lshift);
        right.push(x - rshift);
      } else right.push(a - rshift);
    }
    void add_a_minus_x(long long a) {
      if (!right.empty() && right.top() + rshift < a) {
        long long x=right.top()+rshift; right.pop(); value+=a-x; right.push(a-rshift);
        left.push(x - lshift);
      } else left.push(a - lshift);
    }
    void add_abs(long long a) { add_x_minus_a(a); add_a_minus_x(a); }
    void add_constant(long long c) { value += c; }
    void prefix_min() { right = {}; }
    // g(x)=min_{y<=x}f(y).
    void suffix_min() { left = {}; }
    // g(x)=min_{x-b<=y<=x+a} f(y), a,b>=0.
    void window_min(long long a, long long b) {
      assert(a >= 0 && b >= 0); lshift -= a; rshift += b;
    }
  };
//NOTEBOOK_END
}
