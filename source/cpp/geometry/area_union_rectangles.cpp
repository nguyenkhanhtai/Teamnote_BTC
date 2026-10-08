#pragma once
#include <bits/stdc++.h>
namespace notebook::geometry {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto area = rectangle_union_area({{0,0,2,3}});
  struct Rectangle { int x1, y1, x2, y2; };
  __int128 rectangle_union_area(const vector<Rectangle>& rects) {
    struct Event { int x,y1,y2; int delta;
      bool operator<(const Event& other) const { return x<other.x; }
    }; vector<Event>e; vector<int>ys;
    for (auto r : rects) {
      assert(r.x1 <= r.x2 && r.y1 <= r.y2);
      if (r.x1 == r.x2 || r.y1 == r.y2) continue;
      e.push_back( {r.x1,r.y1,r.y2,1}); e.push_back( {r.x2,r.y1,r.y2,-1});
      ys.push_back(r.y1); ys.push_back(r.y2);
    }
    if (e.empty()) return 0;
    sort(ys.begin(),ys.end()); ys.erase(unique(ys.begin(),ys.end()),ys.end());
    sort(e.begin(),e.end()); int n=ys.size()-1;
    vector<int> cover(4 * n); vector<__int128> len(4 * n);
    struct CoverageTree {
      vector<int>& cover; vector<__int128>& len; const vector<int>& ys;
      void update(int u,int l,int r,int a,int b,int d) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) cover[u] += d;
        else { int m=(l+r)/2; update(u*2,l,m,a,b,d); update(u*2+1,m,r,a,b,d); }
        len[u]=cover[u]?(__int128)ys[r]-ys[l]:r-l==1?0:len[u*2]+len[u*2+1];
    }
    } helper{cover,len,ys}; __int128 ans = 0; int prev = e[0].x;
    for (auto v : e) {
      ans += len[1] * ((__int128) v.x - prev);
      helper.update(1,0,n,lower_bound(ys.begin(),ys.end(),v.y1)-ys.begin(),lower_bound(ys.begin(),ys.end(),v.y2)-ys.begin(),v.delta);
      prev = v.x;
    }
    return ans;
  }
//NOTEBOOK_END
}
