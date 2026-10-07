#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // [l,r); values, shifts and sums must remain well inside +/- INF.
  // chmin/chmax/sum: amortized logarithmic; with add: log^2 bound.
  struct SegmentTreeBeats {
    static constexpr long long INF = 1LL << 60;
    struct Node {
      long long sum=0,mx=-INF,mx2=-INF,mn=INF,mn2=INF,add=0; int cmx=0,cmn=0,len=0;
    }; int n; vector<Node> t;
    void pull(int p) {
      const auto&a=t[p*2],&b=t[p*2+1]; auto&c=t[p]; c.sum=a.sum+b.sum;
      c.len=a.len+b.len; c.mx=max(a.mx,b.mx); c.mn=min(a.mn,b.mn);
      c.cmx = (a.mx == c.mx ? a.cmx : 0) + (b.mx == c.mx ? b.cmx : 0);
      c.cmn = (a.mn == c.mn ? a.cmn : 0) + (b.mn == c.mn ? b.cmn : 0);
      c.mx2=max(a.mx==c.mx?a.mx2:a.mx,b.mx==c.mx?b.mx2:b.mx);
      c.mn2=min(a.mn==c.mn?a.mn2:a.mn,b.mn==c.mn?b.mn2:b.mn);
    }
    void add_node(int p, long long x) {
      auto&a=t[p]; a.sum+=x*a.len; a.mx+=x; a.mn+=x; a.add+=x;
      if (a.mx2 != -INF) a.mx2 += x;
      if (a.mn2 != INF) a.mn2 += x;
    }
    void cap(int p, long long x) {
      auto& a = t[p];
      if (x >= a.mx) return;
      a.sum += (x - a.mx) * a.cmx;
      if (a.mn == a.mx) a.mn = x;
      else if (a.mn2 == a.mx) a.mn2 = x;
      a.mx = x;
    }
    void floor_node(int p, long long x) {
      auto& a = t[p];
      if (x <= a.mn) return;
      a.sum += (x - a.mn) * a.cmn;
      if (a.mx == a.mn) a.mx = x;
      else if (a.mx2 == a.mn) a.mx2 = x;
      a.mn = x;
    }
    void push(int p) {
      for (int c : {p * 2, p * 2 + 1}) {
        if (t[p].add) add_node(c, t[p].add);
        cap(c, t[p].mx); floor_node(c, t[p].mn);
      }
      t[p].add = 0;
    }
    void build(int p, int l, int r, const vector<long long>& a) {
      if(r-l==1){ t[p].sum=t[p].mx=t[p].mn=a[l]; t[p].cmx=t[p].cmn=t[p].len=1; return; }
      int m=(l+r)/2; build(p*2,l,m,a); build(p*2+1,m,r,a); pull(p);
    }
    void update(int p,int l,int r,int ql,int qr,long long x,int kind){
      if(qr<=l||r<=ql||(kind==0&&t[p].mx<=x)||(kind==1&&t[p].mn>=x))return;
      if (ql <= l && r <= qr) {
        if (kind == 2) { add_node(p, x); return; }
        if (kind == 0 && t[p].mx2 < x) { cap(p, x); return; }
        if (kind == 1 && x < t[p].mn2) { floor_node(p, x); return; }
      }
      push(p); int m = (l + r) / 2; update(p * 2, l, m, ql, qr, x, kind);
      update(p * 2 + 1, m, r, ql, qr, x, kind); pull(p);
    }
    long long query(int p, int l, int r, int ql, int qr) {
      if (qr <= l || r <= ql) return 0;
      if (ql <= l && r <= qr) return t[p].sum;
      push(p); int m=(l+r)/2; return query(p*2,l,m,ql,qr)+query(p*2+1,m,r,ql,qr);
    }
    explicit SegmentTreeBeats(const vector<long long>&a):n(a.size()),t(4*max(1,n)){
      if (n) build(1, 0, n, a);
    }
    void chmin(int l, int r, long long x) {
      if (l < r) update(1, 0, n, l, r, x, 0);
    }
    void chmax(int l, int r, long long x) {
      if (l < r) update(1, 0, n, l, r, x, 1);
    }
    void add(int l, int r, long long x) {
      if (l < r) update(1, 0, n, l, r, x, 2);
    }
    long long sum(int l,int r){ return l<r?query(1,0,n,l,r):0; }
  };
//NOTEBOOK_END
}
