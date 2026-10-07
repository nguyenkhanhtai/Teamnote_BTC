#pragma once
#include <bits/stdc++.h>
#include "max_flow_dinic.cpp"
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  struct CutTreeEdge { int u, v; long long capacity; };
  // Undirected nonnegative capacities; min edge on tree path gives pairwise min-cut.
  vector<CutTreeEdge> gomory_hu(int n, const vector<CutTreeEdge>& edges){
    vector<int> parent(n, 0); vector<long long> value(n);
    for (int s = 1; s < n; ++s) {
      int t = parent[s]; Dinic flow(n);
      for (auto e : edges) {
        flow.add_edge(e.u,e.v,e.capacity); flow.add_edge(e.v,e.u,e.capacity);
      }
      long long cut=flow.max_flow(s,t); auto side=flow.source_side(s);
      for(int i=s+1; i<n; ++i)if(parent[i]==t&&side[i])parent[i]=s;
      if (t != 0 && side[parent[t]]) {
        parent[s]=parent[t]; parent[t]=s; value[s]=value[t]; value[t]=cut;
      } else value[s] = cut;
    }
    vector<CutTreeEdge> tree;
    for (int u = 1; u < n; ++u) tree.push_back( {u, parent[u], value[u]});
    return tree;
  }
//NOTEBOOK_END
}
