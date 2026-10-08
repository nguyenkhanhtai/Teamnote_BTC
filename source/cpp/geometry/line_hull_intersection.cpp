#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: LineHullIntersection idx({{0,0},{2,0},{0,2}});
  //      auto hits = idx.intersect(Line{{0,1},{1,0}});
  // O(n) preprocessing, O(log n) query. Strict CCW hull, n>=3.
  struct LineHullIntersection {
    vector<Point> p; vector<pair<long double, int>> normals;
    int extreme(Point d) const {
      long double a = atan2l(d.y, d.x);
      auto it=lower_bound(normals.begin(),normals.end(),pair<long double,int>{a,INT_MIN}); return it == normals.end() ? normals[0].second : it->second;
    }
    LineHullIntersection(vector<Point> h) : p(move(h)) {
      assert(p.size() >= 3);
      for (int i = 0; i < (int) p.size(); ++i) {
        Point e = p[(i + 1) % p.size()] - p[i], out = {e.y, -e.x};
        normals.push_back( {atan2l(out.y, out.x), i});
      }
      auto it = min_element(normals.begin(), normals.end());
      rotate(normals.begin(), it, normals.end());
    }
    long double side(Line l,int i) const { return cross(l.d,p[i]-l.p); }
    vector<Point> intersect(Line l) const {
      assert(norm2(l.d) > 0); Point normal = perp(l.d);
      int hi = extreme(normal), lo = extreme(normal * -1), n = p.size();

      if (side(l,hi) < -EPS || side(l,lo) > EPS) return {};
      // A supporting line may touch a vertex or coincide with one whole edge.
      if (abs(side(l,hi)) <= EPS || abs(side(l,lo)) <= EPS) {
        int u = abs(side(l,hi)) <= EPS ? hi : lo; vector<Point> hits {p[u]};
        int neighbors[] = {(u+n-1)%n, (u+1)%n};
        for(int v : neighbors)if(abs(side(l,v))<=EPS)hits.push_back(p[v]);
        return hits;
      }
      vector<Point> out;
      pair<int,int> arcs[] = {{lo, hi}, {hi, lo}};
      for (auto ends : arcs) {
        int a=ends.first,b=ends.second,steps=(b-a+n)%n,L=0,R=steps;
        long double initial = side(l,a);
        if (abs(initial) <= EPS) { out.push_back(p[a]); continue; }
        while (R - L > 1) {
          int m = (L + R) / 2; long double v = side(l,(a + m) % n);
          if ((v > 0) == (initial > 0)) L = m;
          else R = m;
        }
        Point x=p[(a+L)%n],y=p[(a+R)%n]; auto hit=line_intersection(l,{x,y-x});
        if (hit) out.push_back(*hit);
        else if (abs(side(l,(a + R) % n)) <= EPS) out.push_back(y);
      }
      if(out.size()==2&&norm2(out[0]-out[1])<=EPS*EPS)out.pop_back();
      return out;
    }
  };
//NOTEBOOK_END
}
