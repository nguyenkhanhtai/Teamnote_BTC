#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: LiChao lc(-100,101); lc.add(2,3); auto y = lc.minimum(5);
  // Integer-domain minimum envelope [lo,hi); query nullopt before first insertion.
  struct LiChao {
    struct Line {
      int m, b;
      __int128 at(int x) const { return(__int128) m * x + b; }
    }; struct Node { Line line; int left=-1,right=-1; }; vector<Node>t; int root=-1;
    int lo, hi;
    int add(int u, int l, int r, Line line) {
      if (u < 0) { u = t.size(); t.push_back( {line}); return u; }
      int mid = l + (r - l) / 2;
      bool left=line.at(l)<t[u].line.at(l),middle=line.at(mid)<t[u].line.at(mid);
      if (middle) swap(line, t[u].line);
      if (r - l == 1) return u;
      if (left != middle) {
        int v = add(t[u].left, l, mid, line); t[u].left = v;
      } else { int v = add(t[u].right, mid, r, line); t[u].right = v; }
      return u;
    }
    optional<__int128>query(int u,int l,int r,int x)const {
      if (u < 0) return nullopt;
      __int128 ans = t[u].line.at(x);
      if (r - l > 1) {
        int m = l + (r - l) / 2;
        auto child=x<m?query(t[u].left,l,m,x):query(t[u].right,m,r,x);
        if (child) ans = min(ans, *child);
      }
      return ans;
    }
    LiChao(int lo, int hi) : lo(lo), hi(hi) {
      assert(lo < hi && (__int128) hi - lo <= LLONG_MAX);
    }
    void add(int m,int b){ root=add(root,lo,hi,{m,b}); }
    optional<__int128> minimum(int x) const {
      assert(lo <= x && x < hi); return query(root, lo, hi, x);
    }
  };
//NOTEBOOK_END
}
