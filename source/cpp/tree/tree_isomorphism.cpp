#pragma once
#include <bits/stdc++.h>
namespace notebook::tree {
  using namespace std;
//NOTEBOOK_BEGIN
  // Shared interning dictionary gives exact rooted IDs (not randomized hashes).
  struct TreeIsomorphism {
    map<vector<int>, int> ids;
    vector<int> centers(const vector<vector<int>>& g) const {
      int n = g.size();
      if (n < 2) return n ? vector<int> {0}
      :vector<int> {}; vector<int> degree(n), leaves;
      for(int u=0; u<n; ++u)if((degree[u]=g[u].size())<=1)leaves.push_back(u);
      int remaining = n;
      while (remaining > 2) {
        remaining -= leaves.size(); vector<int> next;
        for(int u:leaves)for(int v:g[u])if(--degree[v]==1)next.push_back(v);
        leaves.swap(next);
      }
      return leaves;
    }
    int rooted_id(const vector<vector<int>>& g, int root) {
      vector<int> parent(g.size(), -1), order {root}, id(g.size());
      for(size_t i=0;i<order.size();++i)for(int v:g[order[i]])if(v!=parent[order[i]]){
        parent[v] = order[i]; order.push_back(v);
      }
      for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int u = *it; vector<int> children;
        for (int v : g[u]) if (v != parent[u]) children.push_back(id[v]);
        sort(children.begin(), children.end());
        auto [pos,inserted]=ids.emplace(children,ids.size()+1); id[u]=pos->second;
      }
      return id[root];
    }
    bool isomorphic(const vector<vector<int>>&a,const vector<vector<int>>&b){
      if (a.size() != b.size()) return false;
      if (a.empty()) return true;
      auto ca = centers(a), cb = centers(b);
      if (ca.size() != cb.size()) return false;
      int id = rooted_id(a, ca[0]);
      for (int c : cb) if (rooted_id(b, c) == id) return true;
      return false;
    }
  };
//NOTEBOOK_END
}
