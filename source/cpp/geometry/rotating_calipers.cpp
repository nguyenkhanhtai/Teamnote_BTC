#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto d2 = diameter_squared({{0,0},{2,0},{0,2}});
  // Strict CCW convex hull; emits supporting vertex pairs (duplicates permitted).
  vector<pair<int, int>> antipodal_pairs(const vector<Point>& p) {
    int n = p.size(); vector<pair<int, int>> out;
    if (n < 2) return out;
    if (n == 2) return {
      {0, 1}
    }; int j = 1;
    for (int i = 0; i < n; ++i) {
      int k=(i+1)%n;
      while (cross(p[k]-p[i],p[(j + 1) % n]-p[i]) > cross(p[k]-p[i],p[j]-p[i]) + EPS) j = (j + 1) % n;
      out.push_back( {i, j}); out.push_back( {k, j});
      if (abs(cross(p[k]-p[i],p[(j + 1) % n]-p[i]) - cross(p[k]-p[i],p[j]-p[i])) <= EPS) {
        out.push_back( {i,(j+1)%n}); out.push_back( {k,(j+1)%n});
      }
    }
    return out;
  }
  long double diameter_squared(const vector<Point>& h) {
    long double ans = 0;
    for(auto[i,j]:antipodal_pairs(h))ans=max(ans,norm2(h[i]-h[j]));
    return ans;
  }
//NOTEBOOK_END
}
