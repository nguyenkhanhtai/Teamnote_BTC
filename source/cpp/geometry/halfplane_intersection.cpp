#pragma once
#include <bits/stdc++.h>
#include "primitive_geometry.cpp"
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto polygon = halfplane_intersection(lines,1000000.L);
  //      lines: vector<Line>; keeps left side, clips to bounding square.
  // Left side of each directed line, clipped to [-bound,bound]^2.
  // Empty or lower-dimensional intersections return empty. Choose bound explicitly.
  long double halfplane_angle(Line l) {
    long double a=atan2l(l.d.y,l.d.x); return a<0?a+2*acosl(-1.L):a;
  }
  bool halfplane_angle_less(Line a,Line b) { return halfplane_angle(a)<halfplane_angle(b); }
  bool outside(Line l,Point p) { return cross(l.d,p-l.p)<-EPS; }
  vector<Point>halfplane_intersection(vector<Line>lines,long double bound){
    assert(bound > 0);
    lines.insert(lines.end(), {
      {
        {-bound, -bound}, {1, 0}
      },{ {bound,-bound},{0,1} },{ {bound,bound},{-1,0} },{ {-bound,bound},{0,-1} }
    });
    sort(lines.begin(),lines.end(),halfplane_angle_less);
    deque<Line> q;
    for (Line l : lines) {
      assert(norm2(l.d) > 0);
      while (q.size() > 1) {
        auto p = line_intersection(q[q.size() - 2], q.back());
        if (!p || outside(l, *p)) q.pop_back();
        else break;
      }
      while (q.size() > 1) {
        auto p = line_intersection(q[0], q[1]);
        if (!p || outside(l, *p)) q.pop_front();
        else break;
      }
      if (!q.empty() && abs(cross(q.back().d, l.d)) <= EPS) {
        if (dot(q.back().d, l.d) < 0) return {};
        if (outside(l, q.back().p)) q.pop_back();
        else continue;
      }
      q.push_back(l);
    }
    while (q.size() > 2) {
      auto p = line_intersection(q[q.size() - 2], q.back());
      if (!p || outside(q.front(), *p)) q.pop_back();
      else break;
    }
    while (q.size() > 2) {
      auto p = line_intersection(q[0], q[1]);
      if (!p || outside(q.back(), *p)) q.pop_front();
      else break;
    }
    if (q.size() < 3) return {};
    vector<Point> out;
    for (int i = 0; i < (int) q.size(); ++i) {
      auto p = line_intersection(q[i], q[(i + 1) % q.size()]);
      if (!p) return {};
      out.push_back(*p);
    }
    long double area = 0;
    for(int i=0;i<(int)out.size();++i)area+=cross(out[i],out[(i+1)%out.size()]);
    if (abs(area) <= EPS) return {};
    return out;
  }
//NOTEBOOK_END
}
