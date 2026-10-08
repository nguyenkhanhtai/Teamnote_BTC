#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: int where = point_in_polygon({{0,0},{2,0},{0,2}},{1,0});
  int point_in_polygon(const vector<Point>& p, Point q) {
    bool inside = false;
    for (int i = 0, n = p.size(); i < n; ++i) {
      Point a = p[i], b = p[(i + 1) % n];
      if (on_segment(q, a, b)) return 0;
      if ((a.y > q.y) != (b.y > q.y)) {
        long double x = a.x + (b.x - a.x) * (q.y - a.y) / (b.y - a.y);
        if (x > q.x) inside = !inside;
      }
    }
    return inside ? 1 : -1;
  }
//NOTEBOOK_END
}
