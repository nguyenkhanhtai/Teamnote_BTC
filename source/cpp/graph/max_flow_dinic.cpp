#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: Dinic flow(3); flow.add_edge(0,1,5); flow.add_edge(1,2,5);
  //      auto f = flow.max_flow(0,2);
  // Directed residual network. add_edge returns forward edge ID; self-loops supported.
  struct Dinic {
    struct Edge { int from,to; long long capacity,flow; }; vector<Edge>edges;
    vector<vector<int>> adj; vector<int> level, next;
    long long dfs(int u, int sink, long long pushed) {
      if (u == sink) return pushed;
      for (int& i = next[u]; i < int(adj[u].size()); ++i) {
        int id = adj[u][i]; auto& e = edges[id];
        if (level[e.to] != level[u] + 1 || e.flow == e.capacity) continue;
        long long f = dfs(e.to, sink, min(pushed, e.capacity - e.flow));
        if (f) { e.flow += f; edges[id ^ 1].flow -= f; return f; }
      }
      return 0;
    }
    Dinic(int n) : adj(n), level(n), next(n) {}
    int add_edge(int u, int v, long long capacity) {
      assert(capacity >= 0); int id = edges.size(); adj[u].push_back(id);
      adj[v].push_back(id + 1); edges.push_back( {u, v, capacity, 0});
      edges.push_back( {v, u, 0, 0}); return id;
    }
    long long max_flow(int source, int sink, long long limit = LLONG_MAX){
      assert(source != sink); long long total = 0;
      while (total < limit) {
        fill(level.begin(),level.end(),-1); queue<int>q; q.push(source); level[source]=0;
        while (!q.empty()) {
          int u = q.front(); q.pop();
          for (int id : adj[u]) {
            auto& e = edges[id];
            if (level[e.to] < 0 && e.flow < e.capacity) {
              level[e.to] = level[u] + 1; q.push(e.to);
            }
          }
        }
        if (level[sink] < 0) break;
        fill(next.begin(), next.end(), 0);
        while (total < limit) {
          long long f = dfs(source, sink, limit - total);
          if (!f) break;
          total += f;
        }
      }
      return total;
      // additional flow; mutates residual network.
    }
    vector<bool> source_side(int source) const {
      vector<bool>seen(adj.size()); queue<int>q; q.push(source); seen[source]=true;
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int id : adj[u]) {
          auto& e = edges[id];
          if(!seen[e.to]&&e.flow<e.capacity){ seen[e.to]=true; q.push(e.to); }
        }
      }
      return seen;
    }
  };
//NOTEBOOK_END
}
