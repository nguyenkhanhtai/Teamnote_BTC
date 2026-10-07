#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Associative merge with identity; order is preserved (noncommutative supported).
  template<typename T, typename Merge> struct SegmentTree {
    int n, base = 1; T identity; Merge merge; vector<T> tree;
    SegmentTree(const vector<T>&a,T identity,Merge merge):n(a.size()),identity(identity),merge(merge){
      while (base < n) base *= 2;
      tree.assign(2*base,identity); copy(a.begin(),a.end(),tree.begin()+base);
      for(int u=base-1; u; --u)tree[u]=merge(tree[u*2],tree[u*2+1]);
    }
    void set(int p, T value) {
      assert(0 <= p && p < n); tree[p += base] = value;
      while (p /= 2) tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }
    T fold(int l, int r) const {
      assert(0<=l&&l<=r&&r<=n); T left=identity,right=identity;
      for (l += base, r += base; l < r; l /= 2, r /= 2) {
        if (l & 1) left = merge(left, tree[l++]);
        if (r & 1) right = merge(tree[--r], right);
      }
      return merge(left, right);
    }
    // First failing position r for predicate(fold(l,r+1)); n if none.
    // predicate(identity) true, predicate monotone under appending elements.
    template<typename Predicate>int max_right(int l,Predicate predicate)const {
      assert(0 <= l && l <= n && predicate(identity));
      if (l == n) return n;
      T value = identity; int u = l + base;
      do {
        while (!(u & 1)) u /= 2;
        T candidate = merge(value, tree[u]);
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
    int n; vector<long long> tree;
    explicit RangeAddPointQuery(int n) : n(n), tree(2 * max(1, n)){}
    void add(int l, int r, long long value) {
      assert(0 <= l && l <= r && r <= n);
      for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) tree[l++] += value;
        if (r & 1) tree[--r] += value;
      }
    }
    long long get(int p) const {
      assert(0 <= p && p < n); long long value = 0;
      for (p += n; p; p /= 2) value += tree[p];
      return value;
    }
  };
//NOTEBOOK_END
}
