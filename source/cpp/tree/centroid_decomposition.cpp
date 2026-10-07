#pragma once
#include <bits/stdc++.h>
namespace notebook::tree {
  using namespace std;
//NOTEBOOK_BEGIN
  // Builds centroid parent forest for a tree; original adjacency is unchanged.
  // on_centroid(c,parent,blocked) may process the current component.
  struct CentroidDecomposition {
    vector<int> parent;
    template<typename Process>CentroidDecomposition(const vector<vector<int>>&g,Process on_centroid):parent(g.size(),-1){
      int n = g.size();
      if (!n) return;
      vector<bool> blocked(n); vector<int> p(n), size(n);
      vector<pair<int, int>> tasks { {0, -1} };
      while (!tasks.empty()) {
        auto [entry,ancestor]=tasks.back(); tasks.pop_back(); vector<int>order {entry};
        p[entry] = -1;
        for(size_t i=0;i<order.size();++i)for(int v:g[order[i]])if(!blocked[v]&&v!=p[order[i]]){
          p[v] = order[i]; order.push_back(v);
        }
        int total = order.size(), c = entry;
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
          int u = *it; size[u] = 1; int largest = 0;
          for (int v : g[u]) if (!blocked[v] && p[v] == u) {
            size[u] += size[v]; largest = max(largest, size[v]);
          }
          if (max(largest, total - size[u]) <= total / 2) c = u;
        }
        parent[c]=ancestor; blocked[c]=true; on_centroid(c,ancestor,blocked);
        for (int v : g[c]) if (!blocked[v]) tasks.push_back( {v, c});
      }
    }
  };
//NOTEBOOK_END
}
