#pragma once
#include <bits/stdc++.h>
#include "convex_hull.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Strict CCW convex polygons. Degenerate hulls use the explicit fallback.
  vector<Point> minkowski_sum(vector<Point> a, vector<Point> b) {
    if (a.empty() || b.empty()) return {};
    if (a.size() < 3 || b.size() < 3) {
      vector<Point> s;
      for (auto x : a) for (auto y : b) s.push_back(x + y);
      return convex_hull(s);
    }
    auto rotate_min = [](vector<Point>& p) {
      auto it = min_element(p.begin(), p.end(), [](Point x, Point y) {
        return tie(x.y, x.x) < tie(y.y, y.x);
      }); rotate(p.begin(), it, p.end());
    }; rotate_min(a); rotate_min(b); int n=a.size(),m=b.size(),i=0,j=0;
    Point cur = a[0] + b[0]; vector<Point> out {cur};
    while (i < n || j < m) {
      Point u = a[(i + 1) % n] - a[i % n], v = b[(j + 1) % m] - b[j % m];
      int c = i == n ? -1 : j == m ? 1 : sign(cross(u, v));
      if (c >= 0 && i < n) { cur = cur + u; ++i; }
      if (c <= 0 && j < m) { cur = cur + v; ++j; }
      out.push_back(cur);
    }
    out.pop_back(); return out;
  }
//NOTEBOOK_END
}
