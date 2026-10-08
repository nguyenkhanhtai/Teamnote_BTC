#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: mt19937_64 rng(123456);
  //      auto ans = banded_pick_k(vector<int>{1,2,3},2,3,rng);
  // Randomized band DP for additive pick-k; not a deterministic exact guarantee.
  // Shuffles a COPY; caller provides half-width and RNG. O(n*(width+1)) work, O(width+1) space.
  // nullopt means no feasible path stayed in the band; reaching k may still be suboptimal.
  optional<int> banded_pick_k(vector<int> values,
      int k,int width,mt19937_64& rng){
    int n = values.size(); assert(0 <= k && k <= n && width >= 0);
    if (!n) return 0;
    shuffle(values.begin(),values.end(),rng); constexpr int neg=-(1LL<<60);
    vector<int> dp(1, 0); int prev_lo = 0, prev_hi = 0;
    for (int i = 1; i <= n; ++i) {
      int center = static_cast<int>(i) * k / n;
      int lo=max<int>( {0,center-width,k-(n-i)}),hi=min( {i,k,center+width});
      if (lo > hi) return nullopt;
      vector<int> next(hi - lo + 1, neg);
      for (int j = lo; j <= hi; ++j) {
        if (prev_lo <= j && j <= prev_hi) next[j - lo] = dp[j - prev_lo];
        if(j&&prev_lo<=j-1&&j-1<=prev_hi&&dp[j-1-prev_lo]!=neg)next[j-lo]=max(next[j-lo],dp[j-1-prev_lo]+values[i-1]);
      }
      dp.swap(next); prev_lo = lo; prev_hi = hi;
    }
    return dp[k-prev_lo]==neg?nullopt:optional<int>(dp[k-prev_lo]);
  }
//NOTEBOOK_END
}
