#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // CCW hull without duplicate/collinear vertices; exact sort, tolerant orientation.
  vector<Point> convex_hull(vector<Point> p) {
    sort(p.begin(),p.end(),[](Point a,Point b){ return tie(a.x,a.y)<tie(b.x,b.y); });
    p.erase(unique(p.begin(), p.end(), [](Point a, Point b) {
      return a.x == b.x && a.y == b.y;
    }), p.end());
    if (p.size() < 3) return p;
    vector<Point> h;
    for (Point v : p) {
      while(h.size()>1&&cross(h.back()-h[h.size()-2],v-h.back())<=EPS)h.pop_back();
      h.push_back(v);
    }
    size_t lower = h.size();
    for (int i = (int) p.size() - 2; i >= 0; --i) {
      Point v = p[i];
      while(h.size()>lower&&cross(h.back()-h[h.size()-2],v-h.back())<=EPS)h.pop_back();
      h.push_back(v);
    }
    h.pop_back(); return h;
  }
//NOTEBOOK_END
}
