#pragma once
#include <bits/stdc++.h>
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto [cost,edges] = manhattan_mst({{0,0},{2,3}});
  struct ManhattanEdge { int u, v; int weight;
    bool operator<(const ManhattanEdge& other) const { return weight<other.weight; }
  };
  // Coordinates, sums/differences, distances and total weight must fit int.
  vector<ManhattanEdge>manhattan_candidates(vector<pair<int,int>>p){
    auto original=p; int n=p.size(); vector<int>ids(n); iota(ids.begin(),ids.end(),0);
    vector<ManhattanEdge> edges;
    for (int direction = 0; direction < 4; ++direction) {
      vector<pair<int,int>> order;
      for (int id:ids) order.push_back({p[id].first+p[id].second,id});
      sort(order.begin(),order.end());
      for (int i=0;i<n;++i) ids[i]=order[i].second;
      map<int, int> sweep;
      for (int i : ids) {
        auto[x, y] = p[i];
        for (auto it = sweep.lower_bound(-y); it != sweep.end();) {
          int j = it->second; auto[u, v] = p[j];
          if (x - u < y - v) break;
          edges.push_back( {
            i,j,llabs(original[i].first-original[j].first)+llabs(original[i].second-original[j].second)
          }); it = sweep.erase(it);
        }
        sweep[-y] = i;
      }
      for (auto& [x, y] : p) if (direction & 1) x = -x;
      else swap(x, y);
    }
    return edges;
  }
  pair<int,vector<ManhattanEdge>>manhattan_mst(const vector<pair<int,int>>&p){
    auto e = manhattan_candidates(p);
    sort(e.begin(),e.end());
    vector<int>parent(p.size()),size(p.size(),1); iota(parent.begin(),parent.end(),0);
    struct DSUFind {
      vector<int>& parent;
      int find(int u) { return parent[u]==u?u:parent[u]=find(parent[u]); }
    } dsu{parent}; int total = 0; vector<ManhattanEdge> tree;
    for (auto edge : e) {
      int a = dsu.find(edge.u), b = dsu.find(edge.v);
      if (a == b) continue;
      if (size[a] < size[b]) swap(a, b);
      parent[b]=a; size[a]+=size[b]; total+=edge.weight; tree.push_back(edge);
    }
    return {total, tree};
  }
//NOTEBOOK_END
}
