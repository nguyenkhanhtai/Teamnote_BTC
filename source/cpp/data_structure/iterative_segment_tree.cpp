#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: int mergeSum(int a,int b) { return a+b; }
  //      SegmentTree st({1,2,3},0,mergeSum); auto s = st.fold(0,3);
  //      RangeAddPointQuery lazy(3); lazy.add(0,2,4);
  // Associative merge with identity; order is preserved (noncommutative supported).
  struct SegmentTree {
    int n, base = 1; int identity; function<int(int,int)> merge; vector<int> tree;
    SegmentTree(const vector<int>&a,int identity,function<int(int,int)> merge):n(a.size()),identity(identity),merge(merge){
      while (base < n) base *= 2;
      tree.assign(2*base,identity); copy(a.begin(),a.end(),tree.begin()+base);
      for(int u=base-1; u; --u)tree[u]=merge(tree[u*2],tree[u*2+1]);
    }
    void set(int p, int value) {
      assert(0 <= p && p < n); tree[p += base] = value;
      while (p /= 2) tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }
    int fold(int l, int r) const {
      assert(0<=l&&l<=r&&r<=n); int left=identity,right=identity;
      for (l += base, r += base; l < r; l /= 2, r /= 2) {
        if (l & 1) left = merge(left, tree[l++]);
        if (r & 1) right = merge(tree[--r], right);
      }
      return merge(left, right);
    }
    // First failing position r for predicate(fold(l,r+1)); n if none.
    // predicate(identity) true, predicate monotone under appending elements.
    int max_right(int l,function<bool(int)> predicate)const {
      assert(0 <= l && l <= n && predicate(identity));
      if (l == n) return n;
      int value = identity; int u = l + base;
      do {
        while (!(u & 1)) u /= 2;
        int candidate = merge(value, tree[u]);
        if (!predicate(candidate)) {
          while (u < base) {
            u *= 2; candidate = merge(value, tree[u]);
            if (predicate(candidate)) { value = candidate; ++u; }
          }
          return min(n, u - base);
        }
        value = candidate; ++u;
      }
      while ((u & -u) != u);
      return n;
    }
  };
  struct RangeAddPointQuery {
    int n; vector<int> tree;
    RangeAddPointQuery(int n) : n(n), tree(2 * max<int>(1, n)){}
    void add(int l, int r, int value) {
      assert(0 <= l && l <= r && r <= n);
      for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) tree[l++] += value;
        if (r & 1) tree[--r] += value;
      }
    }
    int get(int p) const {
      assert(0 <= p && p < n); int value = 0;
      for (p += n; p; p /= 2) value += tree[p];
      return value;
    }
  };
//NOTEBOOK_END
}
