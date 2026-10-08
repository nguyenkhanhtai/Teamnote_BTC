#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: int where = point_in_convex({{0,0},{2,0},{0,2}},{1,0});
  // -1 outside, 0 boundary, 1 inside; strict CCW polygon.
  int point_in_convex(const vector<Point>& p, Point q) {
    int n = p.size();
    if (!n) return-1;
    if (n == 1) return norm2(q - p[0]) <= EPS * EPS ? 0 : -1;
    if (n == 2) return on_segment(q, p[0], p[1]) ? 0 : -1;
    int a=sign(cross(p[1]-p[0],q-p[0])),b=sign(cross(p.back()-p[0],q-p[0]));
    if (a < 0 || b > 0) return-1;
    if (!a) return on_segment(q, p[0], p[1]) ? 0 : -1;
    if (!b) return on_segment(q, p[0], p.back()) ? 0 : -1;
    int l = 1, r = n - 1;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (cross(p[m] - p[0], q - p[0]) >= 0) l = m;
      else r = m;
    }
    return sign(cross(p[r] - p[l], q - p[l]));
  }
//NOTEBOOK_END
}
