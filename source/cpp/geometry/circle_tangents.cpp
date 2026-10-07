#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Tangency points on circles; nullopt means infinitely many (identical circles).
  optional<vector<pair<Point,Point>>>circle_tangents(Point a,long double ra,Point b,long double rb){
    assert(ra >= 0 && rb >= 0); Point d = b - a; long double z = norm2(d);
    if (z <= EPS * EPS) {
      if (abs(ra - rb) <= EPS) return nullopt;
      return vector<pair<Point, Point>> {};
    }
    vector<pair<Point, Point>> out;
    for (int s : {-1, 1}) {
      long double r = ra - s * rb, h = z - r * r;
      if (h < -EPS) continue;
      h = sqrtl(max(0.L, h));
      for (int side : {-1, 1}) {
        if (side == 1 && h <= EPS) continue;
        Point n=(d*r+perp(d)*(h*side))/z; pair<Point,Point>t {a+n*ra,b+n*(s*rb)};
        bool dup = false;
        for(auto old:out)if(norm2(old.first-t.first)+norm2(old.second-t.second)<=EPS*EPS)dup=true;
        if (!dup) out.push_back(t);
      }
    }
    return out;
  }
//NOTEBOOK_END
}
