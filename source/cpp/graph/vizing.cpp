#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Simple undirected graph; returns edge colors 0..Delta. O(n^2) storage.
  vector<int> vizing_coloring(int N, const vector<pair<int, int>>& edges){
    vector<pair<int, int>> E;
    for(auto [u,v]:edges){ assert(u!=v); E.push_back( {u+1,v+1}); }
    vector<vector<int>>C(N+1,vector<int>(N+2)),G(N+1,vector<int>(N+1));
    vector<int> X(N + 1); int a;
    auto update = [&](int u) {
      for (X[u] = 1; C[u][X[u]]; X[u]++);
    };
    auto color = [&](int u, int v, int c) {
      int p = G[u][v];
      if (p == c) return p;
      G[u][v]=G[v][u]=c; C[u][c]=v; C[v][c]=u; C[u][p]=C[v][p]=0;
      if ( p ) X[u] = X[v] = p;
      else update(u), update(v);
      return p;
    };
    // end of function : color
    auto flip = [&](int u, int c1, int c2) {
      int p = C[u][c1]; swap(C[u][c1], C[u][c2]);
      if ( p ) G[u][p] = G[p][u] = c2;
      if ( !C[u][c1] ) X[u] = c1;
      if ( !C[u][c2] ) X[u] = c2;
      return p;
    };
    // end of function : flip
    for (int i = 1; i <= N; i++) X[i] = 1;
    for (int t = 0; t < (int) E.size(); t++) {
      int u=E[t].first,v0=E[t].second,v=v0,c0=X[u],c=c0,d; vector<pair<int,int>>L;
      vector<int> vst(N + 2);
      while (!G[u][v0]) {
        L.emplace_back(v, d = X[v]);
        if(!C[v][c])for(a=(int)L.size()-1; a>=0; a--)c=color(u,L[a].first,c);
        else if(!C[u][d])for(a=(int)L.size()-1;a>=0;a--)color(u,L[a].first,L[a].second);
        else if ( vst[d] ) break;
        else vst[d] = 1, v = C[u][d];
      }
      if ( !G[u][v0] ) {
        for (; v; v = flip(v, c, d), swap(c, d));
        if (C[u][c0]) {
          for (a = (int) L.size() - 2; a >= 0 && L[a].second != c; a--);
          for (; a >= 0; a--) color(u, L[a].first, L[a].second);
        } else t--;
      }
    }
    vector<int> result;
    for (auto [u, v] : E) result.push_back(G[u][v] - 1);
    return result;
  }
//NOTEBOOK_END
}
