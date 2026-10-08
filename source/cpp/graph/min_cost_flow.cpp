#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: MinCostFlow flow(3); flow.add_edge(0,1,5,2);
  //      auto ans = flow.send(0,1,3); // ans.flow, ans.cost
  // Capacities nonnegative; no reachable negative-cost cycle in residual graph.
  // Bellman-Ford initializes potentials; Dijkstra for each augmentation.
  struct MinCostFlow {
    struct Edge { int to,rev; int cap,cost; }; vector<vector<Edge>>g;
    struct Result { int flow, cost; };
    MinCostFlow(int n) : g(n) {}
    void add_edge(int u, int v, int cap, int cost) {
      assert(cap >= 0); int a = g[u].size(), b = g[v].size();
      g[u].push_back( {v,b+(u==v),cap,cost}); g[v].push_back( {u,a,0,-cost});
    }
    Result send(int s, int t, int limit) {
      assert(s!=t&&limit>=0); int n=g.size(); constexpr int inf=1LL<<60;
      vector<int> potential(n, inf); potential[s] = 0;
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
        vector<int>dist(n,inf); vector<int>pv(n),pe(n); dist[s]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
        q.push( {0, s});
        while (!q.empty()) {
          auto [d, u] = q.top(); q.pop();
          if (d != dist[u]) continue;
          for (int i = 0; i < static_cast<int>(g[u].size()); ++i) {
            auto& e = g[u][i];
            if (!e.cap) continue;
            int nd = d + e.cost + potential[u] - potential[e.to];
            if (nd < dist[e.to]) {
              dist[e.to]=nd; pv[e.to]=u; pe[e.to]=i; q.push( {nd,e.to});
            }
          }
        }
        if (dist[t] == inf) break;
        for(int u=0; u<n; ++u)if(dist[u]<inf)potential[u]+=dist[u];
        int f = limit - result.flow, cost = 0;
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
