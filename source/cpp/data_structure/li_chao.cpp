#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Integer-domain minimum envelope [lo,hi); query nullopt before first insertion.
  struct LiChao {
    struct Line {
      long long m, b;
      __int128 at(long long x) const { return(__int128) m * x + b; }
    }; struct Node { Line line; int left=-1,right=-1; }; vector<Node>t; int root=-1;
    long long lo, hi;
    int add(int u, long long l, long long r, Line line) {
      if (u < 0) { u = t.size(); t.push_back( {line}); return u; }
      long long mid = l + (r - l) / 2;
      bool left=line.at(l)<t[u].line.at(l),middle=line.at(mid)<t[u].line.at(mid);
      if (middle) swap(line, t[u].line);
      if (r - l == 1) return u;
      if (left != middle) {
        int v = add(t[u].left, l, mid, line); t[u].left = v;
      } else { int v = add(t[u].right, mid, r, line); t[u].right = v; }
      return u;
    }
    optional<__int128>query(int u,long long l,long long r,long long x)const {
      if (u < 0) return nullopt;
      __int128 ans = t[u].line.at(x);
      if (r - l > 1) {
        long long m = l + (r - l) / 2;
        auto child=x<m?query(t[u].left,l,m,x):query(t[u].right,m,r,x);
        if (child) ans = min(ans, *child);
      }
      return ans;
    }
    LiChao(long long lo, long long hi) : lo(lo), hi(hi) {
      assert(lo < hi && (__int128) hi - lo <= LLONG_MAX);
    }
    void add(long long m,long long b){ root=add(root,lo,hi,{m,b}); }
    optional<__int128> minimum(long long x) const {
      assert(lo <= x && x < hi); return query(root, lo, hi, x);
    }
  };
//NOTEBOOK_END
}
