#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: LineContainer lc; lc.add(2,3); auto y = lc.maximum(5);
  // Arbitrary slopes and x, maximum queries. Integer intersections use int128.
  struct LineContainer {
    struct Line {
      long long m, b; mutable __int128 end;
      bool operator<(const Line& other) const { return m < other.m; }
      bool operator<(__int128 x) const { return end < x; }
    }; multiset<Line,less<>>h; static constexpr __int128 INF=(__int128)1<<126;
    static __int128 floor_div(__int128 a, __int128 b) {
      __int128 q = a / b;
      if (a % b && ((a < 0) != (b < 0))) --q;
      return q;
    }
    bool intersect(multiset<Line,less<>>::iterator x,multiset<Line,less<>>::iterator y){
      if (y == h.end()) { x->end = INF; return false; }
      if (x->m == y->m) x->end = x->b > y->b ? INF : -INF;
      else x->end=floor_div((__int128)y->b-x->b,(__int128)x->m-y->m);
      return x->end >= y->end;
    }
    void add(long long m, long long b) {
      auto z = h.insert( {m, b, 0}), y = z++, x = y;
      while (intersect(y, z)) z = h.erase(z);
      if(x!=h.begin()&&intersect(--x,y))intersect(x,y=h.erase(y));
      while((y=x)!=h.begin()&&(--x)->end>=y->end)intersect(x,h.erase(y));
    }
    optional<__int128> maximum(long long x) const {
      if (h.empty()) return nullopt;
      auto line=h.lower_bound((__int128)x); return(__int128)line->m*x+line->b;
    }
  };
//NOTEBOOK_END
}
