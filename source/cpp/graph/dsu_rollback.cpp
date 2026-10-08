#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: RollbackDSU dsu(3); auto snap = dsu.snapshot();
  //      dsu.unite(0,1); dsu.rollback(snap);
  // No path compression; O(log n) find. Roll back to a snapshot, including no-op unions.
  struct RollbackDSU {
    vector<int>parent,size; struct Change { int child,root,old_size; };
    vector<Change> history; int components;
    RollbackDSU(int n) : parent(n), size(n, 1), components(n) {
      iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) const {
      while (parent[u] != u) u = parent[u];
      return u;
    }
    size_t snapshot() const { return history.size(); }
    bool unite(int u, int v) {
      u = find(u); v = find(v);
      if (u == v) return false;
      if (size[u] < size[v]) swap(u, v);
      history.push_back( {v,u,size[u]}); parent[v]=u; size[u]+=size[v]; --components;
      return true;
    }
    void rollback(size_t snapshot) {
      assert(snapshot <= history.size());
      while (history.size() > snapshot) {
        auto c=history.back(); history.pop_back(); parent[c.child]=c.child;
        size[c.root] = c.old_size; ++components;
      }
    }
  };
//NOTEBOOK_END
}
