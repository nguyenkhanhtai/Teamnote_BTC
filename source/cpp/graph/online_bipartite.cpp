#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Append undirected edges; is_bipartite(u) tests the current component.
  struct BipartiteDSU {
    vector<int> parent, size, parity; vector<bool> good;
    pair<int, int> find(int u) {
      if (parent[u] == u) return {u, 0};
      auto [root, p] = find(parent[u]); parity[u] ^= p; parent[u] = root;
      return {root, parity[u]};
    }
    explicit BipartiteDSU(int n):parent(n),size(n,1),parity(n),good(n,true){
      iota(parent.begin(), parent.end(), 0);
    }
    bool add_edge(int u, int v) {
      auto [a, x] = find(u); auto [b, y] = find(v);
      if (a == b) {
        if (x == y) good[a] = false;
        return good[a];
      }
      if (size[a] < size[b]) { swap(a, b); swap(x, y); }
      parent[b]=a; parity[b]=x^y^1; size[a]+=size[b]; good[a]=good[a]&&good[b];
      return good[a];
    }
    bool is_bipartite(int u) { return good[find(u).first]; }
  };
//NOTEBOOK_END
}
