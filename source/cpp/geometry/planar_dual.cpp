#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto dual = planar_dual(points,edges);
  //      points: vector<Point>; edges: vector<pair<int,int>>.
  struct PlanarDual {
    vector<vector<int>>face_darts; vector<int>face_of; vector<pair<int,int>>dual_edges;
    int outer_face = -1;
  };
  // Connected straight-line embedding, no crossings/overlapping rays/self-loops.
  // Bridges yield loops in the dual. Isolated single vertex has one empty face.
  PlanarDual planar_dual(const vector<Point>&p,const vector<pair<int,int>>&edges){
    int n = p.size(), m = edges.size(); PlanarDual out;
    if(!m){ if(n){ out.face_darts.push_back( {}); out.outer_face=0; } return out; }
    vector<vector<int>>adj(n); vector<int>from(2*m),to(2*m),pos(2*m),next(2*m);
    for (int i = 0; i < m; ++i) {
      auto[u,v]=edges[i]; assert(u!=v); from[2*i]=to[2*i+1]=u; to[2*i]=from[2*i+1]=v;
      adj[u].push_back(2 * i); adj[v].push_back(2 * i + 1);
    }
    struct AngleOrder {
      const vector<Point>& p; const vector<int>& to; int u;
      static bool upper(Point a) { return a.y>0 || (a.y==0 && a.x>=0); }
      bool operator()(int a,int b) const {
        Point x=p[to[a]]-p[u],y=p[to[b]]-p[u];
        if (upper(x)!=upper(y)) return upper(x)>upper(y);
        return cross(x,y)>0;
      }
    };
    for (int u = 0; u < n; ++u) {
      sort(adj[u].begin(),adj[u].end(),AngleOrder{p,to,u});
      for (int j = 0; j < (int) adj[u].size(); ++j) pos[adj[u][j]] = j;
    }
    for (int d = 0; d < 2 * m; ++d) {
      int v=to[d],k=adj[v].size(); next[d]=adj[v][(pos[d^1]+k-1)%k];
    }
    out.face_of.assign(2 * m, -1);
    long double minimum = numeric_limits<long double>::infinity();
    for (int d = 0; d < 2 * m; ++d) if (out.face_of[d] < 0) {
      int id=out.face_darts.size(); vector<int>face; long double area=0; int v=d;
      do {
        out.face_of[v]=id; face.push_back(v); area+=cross(p[from[v]],p[to[v]]); v=next[v];
      }
      while (v != d);
      out.face_darts.push_back(move(face));
      if (area < minimum) minimum = area, out.outer_face = id;
    }
    for(int i=0;i<m;++i)out.dual_edges.push_back( {out.face_of[2*i],out.face_of[2*i+1]});
    return out;
  }
//NOTEBOOK_END
}
