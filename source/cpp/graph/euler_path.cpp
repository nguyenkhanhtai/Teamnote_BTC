#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto trail = euler_trail(3,{{0,1},{1,2}},false);
  struct EulerTrail { vector<int> vertices, edge_ids; };
  // Directed or undirected multigraph, self-loops allowed. nullopt if no complete trail.
  optional<EulerTrail>euler_trail(int n,const vector<pair<int,int>>&edges,bool directed=false,optional<int>requested_start=nullopt){
    if(n==0)return edges.empty()?optional<EulerTrail>(EulerTrail {}):nullopt;
    vector<vector<pair<int, int>>> g(n); vector<int> in(n), out(n);
    for (int id = 0; id < static_cast<int>(edges.size()); ++id) {
      auto [u,v]=edges[id]; g[u].push_back( {v,id}); ++out[u]; ++in[v];
      if (!directed) { g[v].push_back( {u, id}); ++out[v]; ++in[u]; }
    }
    int forced = -1, ends = 0;
    if (directed) {
      int sinks = 0;
      for (int u = 0; u < n; ++u) {
        if (out[u] - in[u] == 1) {
          forced = u; ++ends;
        } else if (in[u] - out[u] == 1) ++sinks;
        else if (in[u] != out[u]) return nullopt;
      }
      if (ends != sinks || ends > 1) return nullopt;
    } else for (int u = 0; u < n; ++u) if (out[u] & 1) {
      ++ends; forced = u;
    }
    if (!directed && ends != 0 && ends != 2) return nullopt;
    int start = requested_start.value_or(forced >= 0 ? forced : 0);
    if(!requested_start&&forced<0)for(int u=0; u<n; ++u)if(out[u]){
      start = u; break;
    }
    if (start < 0 || start >= n) return nullopt;
    if (directed && forced >= 0 && start != forced) return nullopt;
    if (!directed && ends && !(out[start] & 1)) return nullopt;
    vector<int> next(n); vector<bool> used(edges.size());
    vector<pair<int, int>> stack { {start, -1} }; EulerTrail answer;
    while (!stack.empty()) {
      int u = stack.back().first;
      while(next[u]<static_cast<int>(g[u].size())&&used[g[u][next[u]].second])++next[u];
      if (next[u] == static_cast<int>(g[u].size())) {
        auto [v,id]=stack.back(); stack.pop_back(); answer.vertices.push_back(v);
        if (id >= 0) answer.edge_ids.push_back(id);
      }else { auto [v,id]=g[u][next[u]++]; used[id]=true; stack.push_back( {v,id}); }
    }
    if (answer.edge_ids.size() != edges.size()) return nullopt;
    reverse(answer.vertices.begin(), answer.vertices.end());
    reverse(answer.edge_ids.begin(),answer.edge_ids.end()); return answer;
  }
//NOTEBOOK_END
}
