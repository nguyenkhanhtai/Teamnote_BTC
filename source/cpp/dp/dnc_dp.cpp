#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto next = divide_conquer_layer(previous,cost);
  //      auto ans = knuth_partition(n,cost); // cost(l,r): int
  // next[i]=min_{j<i}(previous[j]+cost(j,i)); cost describes [j,i).
  // Requires nondecreasing optimal j as i increases. O(n log n) cost calls.
  vector<int> divide_conquer_layer(const vector<int>& previous,
      function<int(int,int)> cost,int inf=1LL<<60){
    int n = previous.size() - 1; vector<int> next(n + 1, inf);
    struct LayerSolver {
      const vector<int>& previous; vector<int>& next;
      function<int(int,int)> cost; int inf;
      void solve(int l,int r,int lo,int hi) {
        if (l > r) return;
        int mid = (l + r) / 2, best = lo;
        for (int j = lo; j <= min(mid - 1, hi); ++j) if (previous[j] < inf){
          int value = previous[j] + cost(j, mid);
          if (value < next[mid]) { next[mid] = value; best = j; }
        }
        solve(l, mid - 1, lo, best); solve(mid + 1, r, best, hi);
    }
    } helper{previous,next,cost,inf};
    if (n) helper.solve(1, n, 0, n - 1);
    return next;
  }
  // Interval DP: split [l,r) into two nonempty intervals and add cost(l,r).
  // Requires Knuth inequalities; O(n^2) time/space. Singleton cost is zero.
  int knuth_partition(int n,function<int(int,int)> cost) {
    if (!n) return 0;
    vector<vector<int>> dp(n, vector<int>(n));
    vector<vector<int>> opt(n, vector<int>(n));
    for (int i = 0; i < n; ++i) opt[i][i] = i;
    for (int len = 2; len <= n; ++len) for (int l = 0; l + len <= n; ++l){
      int r = l + len - 1; dp[l][r] = 1LL << 60;
      for (int k = opt[l][r - 1]; k <= min(r - 1, opt[l + 1][r]); ++k) {
        int value = dp[l][k] + dp[k + 1][r] + cost(l, r + 1);
        if (value < dp[l][r]) { dp[l][r] = value; opt[l][r] = k; }
      }
    }
    return dp[0][n - 1];
  }
//NOTEBOOK_END
}
