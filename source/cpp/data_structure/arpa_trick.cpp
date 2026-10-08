#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto ids = range_max_indices({3,1},{{0,2}});
  // Offline maximum indices; queries [l,r) nonempty; ties choose rightmost.
  vector<int>range_max_indices(const vector<long long>&a,const vector<pair<int,int>>&queries){
    int n = a.size(); vector<vector<pair<int, int>>> ending(n);
    for (int i = 0; i < int(queries.size()); ++i) {
      auto [l,r]=queries[i]; assert(0<=l&&l<r&&r<=n); ending[r-1].push_back( {l,i});
    }
    vector<int> parent(n), stack, answer(queries.size());
    iota(parent.begin(), parent.end(), 0);
    struct DSUFind {
      vector<int>& parent;
      int find(int u) {
      int v = u;
      while (parent[v] != v) v = parent[v];
      while(parent[u]!=u){ int next=parent[u]; parent[u]=v; u=next; }
      return v;
    }
    } dsu{parent};
    for (int r = 0; r < n; ++r) {
      while (!stack.empty() && a[stack.back()] <= a[r]) {
        parent[stack.back()] = r; stack.pop_back();
      }
      stack.push_back(r);
      for (auto [l, id] : ending[r]) answer[id] = dsu.find(l);
    }
    return answer;
  }
//NOTEBOOK_END
}
