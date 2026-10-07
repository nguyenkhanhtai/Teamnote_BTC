#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Capacities nonnegative; no reachable negative-cost cycle in residual graph.
  // Bellman-Ford initializes potentials; Dijkstra for each augmentation.
  struct MinCostFlow {
    struct Edge { int to,rev; long long cap,cost; }; vector<vector<Edge>>g;
    struct Result { long long flow, cost; };
    explicit MinCostFlow(int n) : g(n) {}
    void add_edge(int u, int v, long long cap, long long cost) {
      assert(cap >= 0); int a = g[u].size(), b = g[v].size();
      g[u].push_back( {v,b+(u==v),cap,cost}); g[v].push_back( {u,a,0,-cost});
    }
    Result send(int s, int t, long long limit) {
      assert(s!=t&&limit>=0); int n=g.size(); constexpr long long inf=1LL<<60;
      vector<long long> potential(n, inf); potential[s] = 0;
      for (int iter = 0; iter < n; ++iter) {
        bool changed = false;
        for(int u=0;u<n;++u)if(potential[u]<inf)for(auto&e:g[u])if(e.cap&&potential[e.to]>potential[u]+e.cost){
          potential[e.to] = potential[u] + e.cost; changed = true;
        }
        if (!changed) break;
        if (iter == n - 1) throw invalid_argument("negative cost cycle");
      }
      for (auto& x : potential) if (x == inf) x = 0;
      Result result {0, 0};
      while (result.flow < limit) {
        vector<long long>dist(n,inf); vector<int>pv(n),pe(n); dist[s]=0;
        priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>>q;
        q.push( {0, s});
        while (!q.empty()) {
          auto [d, u] = q.top(); q.pop();
          if (d != dist[u]) continue;
          for (int i = 0; i < int(g[u].size()); ++i) {
            auto& e = g[u][i];
            if (!e.cap) continue;
            long long nd = d + e.cost + potential[u] - potential[e.to];
            if (nd < dist[e.to]) {
              dist[e.to]=nd; pv[e.to]=u; pe[e.to]=i; q.push( {nd,e.to});
            }
          }
        }
        if (dist[t] == inf) break;
        for(int u=0; u<n; ++u)if(dist[u]<inf)potential[u]+=dist[u];
        long long f = limit - result.flow, cost = 0;
        for(int v=t; v!=s; v=pv[v])f=min(f,g[pv[v]][pe[v]].cap);
        for (int v = t; v != s; v = pv[v]) {
          auto&e=g[pv[v]][pe[v]]; cost+=e.cost; e.cap-=f; g[v][e.rev].cap+=f;
        }
        result.flow += f; result.cost += f * cost;
      }
      return result;
    }
  };
//NOTEBOOK_END
}
