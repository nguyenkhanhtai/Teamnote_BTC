#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: mt19937_64 rng(123456);
  //      auto c = smallest_enclosing_circle({{0,0},{2,0},{0,2}},rng);
  struct Circle { Point center; long double radius; };
  Circle diameter_circle(Point a, Point b) {
    Point c = (a + b) / 2; return {c, sqrtl(norm2(a - c))};
  }
  bool contains(Circle c, Point p) {
    return norm2(p-c.center)<=c.radius*c.radius+EPS*max(1.L,c.radius*c.radius);
  }
  Circle circle_through(Point a, Point b, Point c) {
    Point u = b - a, v = c - a; long double d = 2 * cross(u, v);
    if (abs(d) <= EPS) {
      Circle ans = diameter_circle(a, b);
      for(auto x:{diameter_circle(a,c),diameter_circle(b,c)})if(x.radius>ans.radius)ans=x;
      return ans;
    }
    Point o=a+Point {v.y*norm2(u)-u.y*norm2(v),u.x*norm2(v)-v.x*norm2(u)}
    /d; return {o, sqrtl(norm2(o - a))};
  }
  Circle smallest_enclosing_circle(vector<Point> p, mt19937_64 & rng) {
    shuffle(p.begin(), p.end(), rng); Circle c { {0, 0}, -1 };
    for(int i=0; i<(int)p.size(); ++i)if(c.radius<0||!contains(c,p[i])){
      c = {p[i], 0};
      for (int j = 0; j < i; ++j) if (!contains(c, p[j])) {
        c = diameter_circle(p[i], p[j]);
        for(int k=0;k<j;++k)if(!contains(c,p[k]))c=circle_through(p[i],p[j],p[k]);
      }
    }
    if (p.empty()) c.radius = 0;
    return c;
  }
//NOTEBOOK_END
}
