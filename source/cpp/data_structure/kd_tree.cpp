#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Balanced static k-d tree. Worst-case nearest/range query O(n).
  template<size_t D> struct KDTree {
    static_assert(D > 0); using Point = array<double, D>;
    struct Node { int id,left=-1,right=-1; Point low,high; }; vector<Point>points;
    vector<Node> t; int root;
    int build(vector<int>& ids, int l, int r, int depth) {
      if (l == r) return-1;
      int m = (l + r) / 2, axis = depth % D;
      nth_element(ids.begin()+l,ids.begin()+m,ids.begin()+r,[&](int a,int b){
        return points[a][axis] < points[b][axis];
      }); int u=t.size(); t.push_back( {ids[m],-1,-1,points[ids[m]],points[ids[m]]});
      int a=build(ids,l,m,depth+1),b=build(ids,m+1,r,depth+1); t[u].left=a; t[u].right=b;
      for (int v : {a, b}) if (v >= 0) for (size_t d = 0; d < D; ++d) {
        t[u].low[d] = min(t[u].low[d], t[v].low[d]);
        t[u].high[d] = max(t[u].high[d], t[v].high[d]);
      }
      return u;
    }
    double lower_bound(int u, const Point& q) const {
      if (u < 0) return numeric_limits<double>::infinity();
      double ans = 0;
      for (size_t d = 0; d < D; ++d) {
        double z=max( {0.,t[u].low[d]-q[d],q[d]-t[u].high[d]}); ans+=z*z;
      }
      return ans;
    }
    explicit KDTree(vector<Point> p) : points(move(p)) {
      vector<int> ids(points.size()); iota(ids.begin(), ids.end(), 0);
      root = build(ids, 0, ids.size(), 0);
    }
    optional<pair<int,double>>nearest(const Point&q,int excluded=-1)const {
      int best = -1; double distance = numeric_limits<double>::infinity();
      function<void(int)> visit = [&](int u) {
        if (u < 0 || lower_bound(u, q) > distance) return;
        int id = t[u].id;
        if (id != excluded) {
          double v = 0;
          for(size_t d=0;d<D;++d)v+=(points[id][d]-q[d])*(points[id][d]-q[d]);
          if(v<distance||(v==distance&&(best<0||id<best)))distance=v,best=id;
        }
        int a = t[u].left, b = t[u].right;
        if (lower_bound(a, q) > lower_bound(b, q)) swap(a, b);
        visit(a); visit(b);
      }; visit(root);
      if (best < 0) return nullopt;
      return pair {best, distance};
    }
    vector<int> range(const Point& low, const Point& high) const {
      vector<int> out;
      function<void(int)> visit = [&](int u) {
        if (u < 0) return;
        for(size_t d=0;d<D;++d)if(t[u].high[d]<low[d]||high[d]<t[u].low[d])return;
        bool inside = true;
        for(size_t d=0;d<D;++d)inside&=low[d]<=points[t[u].id][d]&&points[t[u].id][d]<=high[d];
        if (inside) out.push_back(t[u].id);
        visit(t[u].left); visit(t[u].right);
      }; visit(root); return out;
    }
  };
//NOTEBOOK_END
}
