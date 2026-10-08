#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: PersistentRangeSum pst(3); int root = pst.add(0,1,5);
  //      auto s = pst.sum(root,0,3); // root 0: all zeros
  // Immutable point-add versions; root 0 is the all-zero array. Ranges [l,r).
  struct PersistentRangeSum {
    struct Node { int left=0,right=0; long long sum=0; }; vector<Node>t {1}; int n;
    int update(int root, int l, int r, int p, long long x) {
      int u = t.size(); t.push_back(t[root]); t[u].sum += x;
      if (r - l > 1) {
        int m = (l + r) / 2;
        if (p < m) {
          int v = update(t[u].left, l, m, p, x); t[u].left = v;
        } else { int v = update(t[u].right, m, r, p, x); t[u].right = v; }
      }
      return u;
    }
    long long query(int u, int l, int r, int a, int b) const {
      if (!u || b <= l || r <= a) return 0;
      if (a <= l && r <= b) return t[u].sum;
      int m=(l+r)/2; return query(t[u].left,l,m,a,b)+query(t[u].right,m,r,a,b);
    }
    PersistentRangeSum(int n) : n(n) { assert(n >= 0); }
    int add(int root, int p, long long x) {
      assert(0<=root&&root<(int)t.size()&&0<=p&&p<n); return update(root,0,n,p,x);
    }
    long long sum(int root, int l, int r) const {
      assert(0<=root&&root<(int)t.size()&&0<=l&&l<=r&&r<=n); return query(root,0,n,l,r);
    }
  };
//NOTEBOOK_END
}
