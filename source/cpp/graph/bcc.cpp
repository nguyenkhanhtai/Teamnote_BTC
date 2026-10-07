#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  struct BiconnectedResult {
    vector<int>bridges; vector<bool>articulation; vector<vector<int>>edge_blocks;
  };
  // Undirected multigraph; IDs are positions in edges. Self-loops form singleton blocks.
  BiconnectedResult biconnected_components(int n,const vector<pair<int,int>>&edges){
    vector<vector<pair<int, int>>> g(n);
    BiconnectedResult result { {}, vector<bool>(n), {} };
    for (int id = 0; id < int(edges.size()); ++id) {
      auto [u, v] = edges[id];
      if (u == v) { result.edge_blocks.push_back( {id}); continue; }
      g[u].push_back( {v, id}); g[v].push_back( {u, id});
    }
    vector<int> tin(n, -1), low(n), stack; int timer = 0;
    auto dfs = [&](auto&& self, int u, int parent_edge)->void {
      tin[u] = low[u] = timer++; int children = 0;
      for (auto [v, id] : g[u]) if (id != parent_edge) {
        if (tin[v] < 0) {
          ++children; stack.push_back(id); self(self,v,id); low[u]=min(low[u],low[v]);
          if (low[v] > tin[u]) result.bridges.push_back(id);
          if (low[v] >= tin[u]) {
            if (parent_edge >= 0) result.articulation[u] = true;
            result.edge_blocks.push_back( {}); int e;
            do {
              e=stack.back(); stack.pop_back(); result.edge_blocks.back().push_back(e);
            }
            while (e != id);
          }
        } else if(tin[v]<tin[u]){ stack.push_back(id); low[u]=min(low[u],tin[v]); }
      }
      if (parent_edge < 0) result.articulation[u] = children > 1;
    };
    for (int u = 0; u < n; ++u) if (tin[u] < 0) dfs(dfs, u, -1);
    return result;
  }
//NOTEBOOK_END
}
