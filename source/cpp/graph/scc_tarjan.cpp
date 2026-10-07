#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  struct SCCResult { vector<int>component; vector<vector<int>>vertices; };
  // O(V+E). IDs assigned sink-first: every condensation edge has ID[from]>ID[to].
  SCCResult strongly_connected_components(const vector<vector<int>>& g){
    int n=g.size(),timer=0; vector<int>number(n,-1),low(n),stack; vector<bool>active(n);
    SCCResult result { vector<int>(n, -1), {} };
    auto dfs = [&](auto&& self, int u)->void {
      number[u] = low[u] = timer++; stack.push_back(u); active[u] = true;
      for (int v : g[u]) {
        if (number[v] < 0) {
          self(self, v); low[u] = min(low[u], low[v]);
        } else if (active[v]) low[u] = min(low[u], number[v]);
      }
      if (low[u] == number[u]) {
        result.vertices.push_back( {}); int id=result.vertices.size()-1;
        for (;;) {
          int v=stack.back(); stack.pop_back(); active[v]=false; result.component[v]=id;
          result.vertices.back().push_back(v);
          if (v == u) break;
        }
      }
    };
    for (int u = 0; u < n; ++u) if (number[u] < 0) dfs(dfs, u);
    return result;
  }
//NOTEBOOK_END
}
