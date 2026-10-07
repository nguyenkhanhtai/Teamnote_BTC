#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // dp[i]=min_{j<i}(dp[j]+cost(j,i)), dp[0]=initial.
  // Requires single crossing: a newer candidate wins a suffix of future indices.
  template<typename Cost>vector<long long>monotone_partition_dp(int n,Cost cost,long long initial=0){
    struct Candidate { int j,l,r; }; deque<Candidate>q; vector<long long>dp(n+1);
    dp[0] = initial;
    if (n) q.push_back( {0, 1, n});
    auto eval = [&](int j, int i) { return dp[j] + cost(j, i); };
    for (int i = 1; i <= n; ++i) {
      while (q.front().r < i) q.pop_front();
      dp[i] = eval(q.front().j, i);
      if (i == n) break;
      if (q.front().r == i) q.pop_front();
      else q.front().l = i + 1;
      while(!q.empty()&&eval(i,q.back().l)<=eval(q.back().j,q.back().l))q.pop_back();
      if (q.empty()) { q.push_back( {i, i + 1, n}); continue; }
      int l = q.back().l, r = q.back().r + 1;
      while (l < r) {
        int mid = (l + r) / 2;
        if (eval(i, mid) <= eval(q.back().j, mid)) r = mid;
        else l = mid + 1;
      }
      if (l <= n) { q.back().r = l - 1; q.push_back( {i, l, n}); }
    }
    return dp;
  }
//NOTEBOOK_END
}
