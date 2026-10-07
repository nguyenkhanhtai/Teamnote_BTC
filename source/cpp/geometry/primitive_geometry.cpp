#pragma once
#include <bits/stdc++.h>
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  constexpr long double EPS = 1e-12L;
  struct Point {
    long double x = 0, y = 0;
    Point operator + (Point p) const { return {x + p.x, y + p.y}; }
    Point operator - (Point p) const { return {x - p.x, y - p.y}; }
    Point operator * (long double k) const { return {x * k, y * k}; }
    Point operator / (long double k) const { return { x / k, y / k }; }
  };
  long double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  long double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
  long double norm2(Point a) { return dot(a, a); }
  Point perp(Point a) { return {-a.y, a.x}; }
  int sign(long double x) { return(x > EPS) - (x < -EPS); }
  struct Line { Point p, d; };
  optional<Point> line_intersection(Line a, Line b) {
    long double z = cross(a.d, b.d);
    if (abs(z) <= EPS) return nullopt;
    return a.p + a.d * (cross(b.p - a.p, b.d) / z);
  }
  Point projection(Point p, Line l) {
    assert(norm2(l.d)>0); return l.p+l.d*(dot(p-l.p,l.d)/norm2(l.d));
  }
  bool on_segment(Point p, Point a, Point b) {
    return sign(cross(b - a, p - a)) == 0 && dot(p - a, p - b) <= EPS;
  }
//NOTEBOOK_END
}
