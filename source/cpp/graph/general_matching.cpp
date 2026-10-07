#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Edmonds blossom; simple undirected adjacency. Returns mate[u] or -1.
  vector<int> general_matching(const vector<vector<int>>& adjacency) {
    int n=adjacency.size(); std::mt19937 rng(712367); vector<int>match(n,-1);
    vector<int> aux(n, -1); vector<int> label(n); vector<int> orig(n);
    vector<int> parent(n, -1); queue<int> q; int aux_time = -1;
    auto lca = [&](int v, int u) {
      aux_time++;
      while (true) {
        if (v != -1) {
          if (aux[v] == aux_time) { return v; }
          aux[v] = aux_time;
          if(match[v]==-1){ v=-1; } else { v=orig[parent[match[v]]]; }
        }
        swap(v, u);
      }
    };
    // lca
    auto blossom = [&](int v, int u, int a) {
      while (orig[v] != a) {
        parent[v] = u; u = match[v];
        if (label[u] == 1) { label[u] = 0; q.push(u); }
        orig[v] = orig[u] = a; v = parent[u];
      }
    };
    // blossom
    auto augment = [&](int v) {
      while (v != -1) {
        int pv=parent[v]; int next_v=match[pv]; match[v]=pv; match[pv]=v;
        v = next_v;
      }
    };
    // augment
    auto bfs = [&](int root) {
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
    };
    // bfs
    auto greedy = [&]() {
      vector<int> order(n); iota(order.begin(), order.end(), 0);
      shuffle(order.begin(), order.end(), rng);
      for (int i : order) {
        if (match[i] == -1) {
          for (int to : adjacency[i]) {
            if (match[to] == -1) { match[i] = to; match[to] = i; break; }
          }
        }
      }
    }; greedy();
    for (int i = 0; i < n; i++) { if (match[i] == -1) { bfs(i); } }
    return match;
  }
//NOTEBOOK_END
}
