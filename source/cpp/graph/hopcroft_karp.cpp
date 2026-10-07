#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Left vertices [0,L), right [0,R). solve() returns maximum cardinality.
  struct HopcroftKarp {
    vector<vector<int>> g; vector<int> distance; int shortest;
    bool augment(int u) {
      for (int v : g[u]) {
        int next = right[v];
        if((next<0&&distance[u]+1==shortest)||(next>=0&&distance[next]==distance[u]+1&&augment(next))){
          left[u] = v; right[v] = u; return true;
        }
      }
      distance[u] = -1; return false;
    }
    vector<int> left, right;
    HopcroftKarp(int L,int R):g(L),distance(L),left(L,-1),right(R,-1){}
    void add_edge(int u, int v) { g[u].push_back(v); }
    int solve() {
      int count=count_if(left.begin(),left.end(),[](int x){ return x>=0; });
      for (;;) {
        fill(distance.begin(),distance.end(),-1); queue<int>q; shortest=INT_MAX;
        for (int u = 0; u < int(g.size()); ++u) if (left[u] < 0) {
          distance[u] = 0; q.push(u);
        }
        while (!q.empty()) {
          int u = q.front(); q.pop();
          if (distance[u] + 1 > shortest) continue;
          for (int v : g[u]) if (right[v] < 0) shortest = distance[u] + 1;
          else if (distance[right[v]] < 0) {
            distance[right[v]] = distance[u] + 1; q.push(right[v]);
          }
        }
        if (shortest == INT_MAX) break;
        for(int u=0; u<int(g.size()); ++u)if(left[u]<0&&augment(u))++count;
      }
      return count;
    }
    // Call after solve(); returns {left IDs,right IDs} in a minimum vertex cover.
    pair<vector<int>, vector<int>> min_vertex_cover() const {
      vector<bool> l(left.size()), r(right.size()); queue<int> q;
      for (int u = 0; u < int(left.size()); ++u) if (left[u] < 0) {
        l[u] = true; q.push(u);
      }
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (left[u] != v && !r[v]) {
          r[v] = true; int next = right[v];
          if (next >= 0 && !l[next]) { l[next] = true; q.push(next); }
        }
      }
      pair<vector<int>, vector<int>> answer;
      for(int u=0; u<int(l.size()); ++u)if(!l[u])answer.first.push_back(u);
      for(int v=0; v<int(r.size()); ++v)if(r[v])answer.second.push_back(v);
      return answer;
    }
  };
//NOTEBOOK_END
}
