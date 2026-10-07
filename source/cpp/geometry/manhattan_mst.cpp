#pragma once
#include <bits/stdc++.h>
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  struct ManhattanEdge { int u, v; long long weight; };
  // Coordinates, sums/differences, distances and total weight must fit long long.
  vector<ManhattanEdge>manhattan_candidates(vector<pair<long long,long long>>p){
    auto original=p; int n=p.size(); vector<int>ids(n); iota(ids.begin(),ids.end(),0);
    vector<ManhattanEdge> edges;
    for (int direction = 0; direction < 4; ++direction) {
      sort(ids.begin(), ids.end(), [&](int i, int j) {
        return p[i].first + p[i].second < p[j].first + p[j].second;
      }); map<long long, int> sweep;
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
  pair<long long,vector<ManhattanEdge>>manhattan_mst(const vector<pair<long long,long long>>&p){
    auto e = manhattan_candidates(p);
    sort(e.begin(),e.end(),[](auto a,auto b){ return a.weight<b.weight; });
    vector<int>parent(p.size()),size(p.size(),1); iota(parent.begin(),parent.end(),0);
    function<int(int)> find = [&](int u) {
      return parent[u] == u ? u : parent[u] = find(parent[u]);
    }; long long total = 0; vector<ManhattanEdge> tree;
    for (auto edge : e) {
      int a = find(edge.u), b = find(edge.v);
      if (a == b) continue;
      if (size[a] < size[b]) swap(a, b);
      parent[b]=a; size[a]+=size[b]; total+=edge.weight; tree.push_back(edge);
    }
    return {total, tree};
  }
//NOTEBOOK_END
}
