#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Sparse point-add / range-sum on integer domain [lo,hi); O(log(domain)) operations.
  struct SparseRangeSum {
    struct Node { int left=-1,right=-1; long long sum=0; }; vector<Node>t {1};
    long long lo, hi;
    int child(int u, bool right) {
      int v = right ? t[u].right : t[u].left;
      if (v < 0) {
        v = t.size(); t.emplace_back();
        if (right) t[u].right = v;
        else t[u].left = v;
      }
      return v;
    }
    void add(int u, long long l, long long r, long long p, long long x) {
      t[u].sum += x;
      if (r - l == 1) return;
      long long m = l + (r - l) / 2;
      if (p < m) add(child(u, false), l, m, p, x);
      else add(child(u, true), m, r, p, x);
    }
    long long query(int u,long long l,long long r,long long a,long long b)const {
      if (u < 0 || b <= l || r <= a) return 0;
      if (a <= l && r <= b) return t[u].sum;
      long long m=l+(r-l)/2; return query(t[u].left,l,m,a,b)+query(t[u].right,m,r,a,b);
    }
    SparseRangeSum(long long lo, long long hi) : lo(lo), hi(hi) {
      assert(lo < hi && (__int128) hi - lo <= LLONG_MAX);
    }
    void add(long long p,long long x){ assert(lo<=p&&p<hi); add(0,lo,hi,p,x); }
    long long sum(long long l, long long r) const {
      assert(lo <= l && l <= r && r <= hi); return query(0, lo, hi, l, r);
    }
    size_t node_count() const { return t.size(); }
  };
//NOTEBOOK_END
}
