#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto dp = monotone_partition_dp(n,cost); // cost(j,i): long long
  // dp[i]=min_{j<i}(dp[j]+cost(j,i)), dp[0]=initial.
  // Requires single crossing: a newer candidate wins a suffix of future indices.
  vector<long long> monotone_partition_dp(int n,
      function<long long(int,int)> cost,long long initial=0){
    struct Candidate { int j,l,r; }; deque<Candidate>q; vector<long long>dp(n+1);
    dp[0] = initial;
    if (n) q.push_back( {0, 1, n});

    for (int i = 1; i <= n; ++i) {
      while (q.front().r < i) q.pop_front();
      dp[i] = (dp[q.front().j]+cost(q.front().j,i));
      if (i == n) break;
      if (q.front().r == i) q.pop_front();
      else q.front().l = i + 1;
      while(!q.empty()&&(dp[i]+cost(i,q.back().l))<=(dp[q.back().j]+cost(q.back().j,q.back().l)))q.pop_back();
      if (q.empty()) { q.push_back( {i, i + 1, n}); continue; }
      int l = q.back().l, r = q.back().r + 1;
      while (l < r) {
        int mid = (l + r) / 2;
        if ((dp[i] + cost(i,mid)) <= (dp[q.back().j]+cost(q.back().j,mid))) r = mid;
        else l = mid + 1;
      }
      if (l <= n) { q.back().r = l - 1; q.push_back( {i, l, n}); }
    }
    return dp;
  }
//NOTEBOOK_END
}
