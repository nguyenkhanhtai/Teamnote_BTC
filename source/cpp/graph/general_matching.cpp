#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto mate = general_matching({{1},{0,2},{1}});
  // Edmonds blossom; simple undirected adjacency. Returns mate[u] or -1.
  struct BlossomMatching {
    const vector<vector<int>>& adjacency;
    int n; mt19937 rng{712367};
    vector<int> match,aux,label,orig,parent; queue<int> q; int aux_time=-1;
    BlossomMatching(const vector<vector<int>>& g):adjacency(g),n(g.size()),
        match(n,-1),aux(n,-1),label(n),orig(n),parent(n,-1) {}
    int lca(int v, int u) {
      aux_time++;
      while (true) {
        if (v != -1) {
          if (aux[v] == aux_time) { return v; }
          aux[v] = aux_time;
          if(match[v]==-1){ v=-1; } else { v=orig[parent[match[v]]]; }
        }
        swap(v, u);
      }
    }
    // lca
    void blossom(int v, int u, int a) {
      while (orig[v] != a) {
        parent[v] = u; u = match[v];
        if (label[u] == 1) { label[u] = 0; q.push(u); }
        orig[v] = orig[u] = a; v = parent[u];
      }
    }
    // blossom
    void augment(int v) {
      while (v != -1) {
        int pv=parent[v]; int next_v=match[pv]; match[v]=pv; match[pv]=v;
        v = next_v;
      }
    }
    // augment
    bool bfs(int root) {
      fill(label.begin(),label.end(),-1); iota(orig.begin(),orig.end(),0);
      while (!q.empty()) { q.pop(); }
      q.push(root); label[root] = 0;
      while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adjacency[v]) {
          if (label[u] == -1) {
            label[u] = 1; parent[u] = v;
            if (match[u] == -1) { augment(u); return true; }
            label[match[u]] = 0; q.push(match[u]); continue;
          } else if (label[u] == 0 && orig[v] != orig[u]) {
            int a=lca(orig[v],orig[u]); blossom(u,v,a); blossom(v,u,a);
          }
        }
      }
      return false;
    }
    // bfs
    void greedy() {
      vector<int> order(n); iota(order.begin(), order.end(), 0);
      shuffle(order.begin(), order.end(), rng);
      for (int i : order) {
        if (match[i] == -1) {
          for (int to : adjacency[i]) {
            if (match[to] == -1) { match[i] = to; match[to] = i; break; }
          }
        }
      }
    }
    vector<int> solve() {
      greedy();
      for (int i=0;i<n;++i) if (match[i]==-1) bfs(i);
      return match;
    }
  };
  vector<int> general_matching(const vector<vector<int>>& adjacency) {
    BlossomMatching solver(adjacency); return solver.solve();
  }
//NOTEBOOK_END
}
