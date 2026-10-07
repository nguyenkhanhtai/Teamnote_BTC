#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // next[i]=min_{j<i}(previous[j]+cost(j,i)); cost describes [j,i).
  // Requires nondecreasing optimal j as i increases. O(n log n) cost calls.
  template<typename Cost>vector<long long>divide_conquer_layer(const vector<long long>&previous,Cost cost,long long inf=1LL<<60){
    int n = previous.size() - 1; vector<long long> next(n + 1, inf);
    auto solve = [&](auto&& self, int l, int r, int lo, int hi)->void {
      if (l > r) return;
      int mid = (l + r) / 2, best = lo;
      for (int j = lo; j <= min(mid - 1, hi); ++j) if (previous[j] < inf){
        long long value = previous[j] + cost(j, mid);
        if (value < next[mid]) { next[mid] = value; best = j; }
      }
      self(self, l, mid - 1, lo, best); self(self, mid + 1, r, best, hi);
    };
    if (n) solve(solve, 1, n, 0, n - 1);
    return next;
  }
  // Interval DP: split [l,r) into two nonempty intervals and add cost(l,r).
  // Requires Knuth inequalities; O(n^2) time/space. Singleton cost is zero.
  template<typename Cost> long long knuth_partition(int n, Cost cost) {
    if (!n) return 0;
    vector<vector<long long>> dp(n, vector<long long>(n));
    vector<vector<int>> opt(n, vector<int>(n));
    for (int i = 0; i < n; ++i) opt[i][i] = i;
    for (int len = 2; len <= n; ++len) for (int l = 0; l + len <= n; ++l){
      int r = l + len - 1; dp[l][r] = 1LL << 60;
      for (int k = opt[l][r - 1]; k <= min(r - 1, opt[l + 1][r]); ++k) {
        long long value = dp[l][k] + dp[k + 1][r] + cost(l, r + 1);
        if (value < dp[l][r]) { dp[l][r] = value; opt[l][r] = k; }
      }
    }
    return dp[0][n - 1];
  }
//NOTEBOOK_END
}
