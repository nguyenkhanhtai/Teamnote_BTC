#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: SlopeTrick f; f.add_abs(3); auto ans = f.minimum();
  // f starts at 0. Represents convex piecewise-linear f, slopes integral.
  struct SlopeTrick {
    priority_queue<int> left;
    priority_queue<int,vector<int>,greater<int>>right;
    int lshift = 0, rshift = 0, value = 0;
    int minimum() const { return value; }
    // Minimizers [left endpoint,right endpoint]; missing endpoints mean infinity.
    pair<optional<int>, optional<int>> minimizers() const {
      return {
        left.empty()?nullopt:optional<int>(left.top()+lshift),right.empty()?nullopt:optional<int>(right.top()+rshift)
      };
    }
    void add_x_minus_a(int a) {
      if (!left.empty() && left.top() + lshift > a) {
        int x=left.top()+lshift; left.pop(); value+=x-a; left.push(a-lshift);
        right.push(x - rshift);
      } else right.push(a - rshift);
    }
    void add_a_minus_x(int a) {
      if (!right.empty() && right.top() + rshift < a) {
        int x=right.top()+rshift; right.pop(); value+=a-x; right.push(a-rshift);
        left.push(x - lshift);
      } else left.push(a - lshift);
    }
    void add_abs(int a) { add_x_minus_a(a); add_a_minus_x(a); }
    void add_constant(int c) { value += c; }
    void prefix_min() { right = {}; }
    // g(x)=min_{y<=x}f(y).
    void suffix_min() { left = {}; }
    // g(x)=min_{x-b<=y<=x+a} f(y), a,b>=0.
    void window_min(int a, int b) {
      assert(a >= 0 && b >= 0); lshift -= a; rshift += b;
    }
  };
//NOTEBOOK_END
}
