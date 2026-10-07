#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Nonnegative undirected weights; at most 20 terminals (practically <=12).
  // Returns nullopt when disconnected, zero for no terminals.
  optional<long long>steiner_tree(const vector<vector<pair<int,long long>>>&g,const vector<int>&terminals){
    int n = g.size(), k = terminals.size();
    if (!k) return 0;
    assert(k <= 20); constexpr long long inf = 1LL << 60;
    vector<vector<long long>> dp(1 << k, vector<long long>(n, inf));
    for (int i = 0; i < k; ++i) dp[1 << i][terminals[i]] = 0;
    for (int mask = 1; mask < (1 << k); ++mask) {
      for(int sub=(mask-1)&mask;sub;sub=(sub-1)&mask)if(sub<(mask^sub))for(int u=0;u<n;++u)dp[mask][u]=min(dp[mask][u],dp[sub][u]+dp[mask^sub][u]);
      priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>>q;
      for(int u=0; u<n; ++u)if(dp[mask][u]<inf)q.push( {dp[mask][u],u});
      while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d != dp[mask][u]) continue;
        for (auto [v, w] : g[u]) if (d + w < dp[mask][v]) {
          dp[mask][v] = d + w; q.push( {d + w, v});
        }
      }
    }
    long long answer = *min_element(dp.back().begin(), dp.back().end());
    return answer == inf ? nullopt : optional<long long>(answer);
  }
//NOTEBOOK_END
}
