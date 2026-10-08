#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: WaveletTree wt({3,1,2}); auto x = wt.kth(0,3,0);
  // Immutable array; ranges [l,r), k is zero-based. O(log sigma) queries.
  struct WaveletTree {
    struct Node { int lo,hi,left=-1,right=-1; vector<int>pref; }; vector<Node>nodes;
    vector<long long> values; int n;
    int build(vector<int> a, int lo, int hi) {
      int id = nodes.size(); nodes.push_back( { lo, hi, -1, -1, {0} });
      if (hi - lo <= 1 || a.empty()) return id;
      int mid = (lo + hi) / 2; vector<int> left, right;
      for (int x : a) {
        nodes[id].pref.push_back(nodes[id].pref.back() + (x < mid));
        (x < mid ? left : right).push_back(x);
      }
      int l=build(move(left),lo,mid),r=build(move(right),mid,hi); nodes[id].left=l;
      nodes[id].right = r; return id;
    }
    int less(int id, int l, int r, int rank) const {
      const auto& t = nodes[id];
      if (l == r || rank <= t.lo) return 0;
      if (t.hi <= rank) return r - l;
      int a = t.pref[l], b = t.pref[r];
      return less(t.left, a, b, rank) + less(t.right, l - a, r - b, rank);
    }
    WaveletTree(const vector<long long>&a):values(a),n(a.size()){
      sort(values.begin(), values.end());
      values.erase(unique(values.begin(),values.end()),values.end()); vector<int>ranks;
      for(auto x:a)ranks.push_back(lower_bound(values.begin(),values.end(),x)-values.begin());
      build(move(ranks), 0, max(1, int(values.size())));
    }
    long long kth(int l, int r, int k) const {
      assert(0<=l&&l<=r&&r<=n&&0<=k&&k<r-l); int id=0;
      while (nodes[id].hi - nodes[id].lo > 1) {
        const auto& t = nodes[id]; int a = t.pref[l], b = t.pref[r];
        if(k<b-a){ l=a; r=b; id=t.left; } else { k-=b-a; l-=a; r-=b; id=t.right; }
      }
      return values[nodes[id].lo];
    }
    int count(int l, int r, long long low, long long high) const {
      assert(0 <= l && l <= r && r <= n);
      if (low > high) return 0;
      int a=lower_bound(values.begin(),values.end(),low)-values.begin();
      int b=upper_bound(values.begin(),values.end(),high)-values.begin();
      return less(0, l, r, b) - less(0, l, r, a);
    }
  };
//NOTEBOOK_END
}
