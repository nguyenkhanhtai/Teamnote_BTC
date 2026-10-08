#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: ImplicitTreap tr(123456); tr.insert(0,7); tr.reverse(0,1);
  // Implicit sequence with insert/erase/reverse/range-sum. RNG seed is explicit.
  // Erased nodes remain in the arena; storage O(total insertions), no dangling pointers.
  struct ImplicitTreap {
    struct Node {
      int value,sum; int priority; int left=-1,right=-1,size=1; bool rev=false;
    }; vector<Node> t; int root = -1; mt19937_64 rng;
    int size(int u) const { return u < 0 ? 0 : t[u].size; }
    int sum(int u) const { return u < 0 ? 0 : t[u].sum; }
    void flip(int u){ if(u>=0){ swap(t[u].left,t[u].right); t[u].rev^=1; } }
    void push(int u) {
      if(u>=0&&t[u].rev){ flip(t[u].left); flip(t[u].right); t[u].rev=false; }
    }
    void pull(int u) {
      t[u].size = 1 + size(t[u].left) + size(t[u].right);
      t[u].sum = t[u].value + sum(t[u].left) + sum(t[u].right);
    }
    pair<int, int> split(int u, int k) {
      if (u < 0) return {-1, -1};
      push(u);
      if (size(t[u].left) >= k) {
        auto[a,b]=split(t[u].left,k); t[u].left=b; pull(u); return {a,u};
      }
      auto[a,b]=split(t[u].right,k-size(t[u].left)-1); t[u].right=a; pull(u);
      return {u, b};
    }
    int merge(int a, int b) {
      if (a < 0) return b;
      if (b < 0) return a;
      if (t[a].priority > t[b].priority) {
        push(a); t[a].right = merge(t[a].right, b); pull(a); return a;
      }
      push(b); t[b].left = merge(a, t[b].left); pull(b); return b;
    }
    ImplicitTreap(int seed) : rng(seed) {}
    int size() const { return size(root); }
    void insert(int p, int x) {
      assert(0<=p&&p<=size()); int u=t.size(); t.push_back( {x,x,static_cast<int>(rng() >> 1)});
      auto[a, b] = split(root, p); root = merge(merge(a, u), b);
    }
    void erase(int l, int r) {
      assert(0<=l&&l<=r&&r<=size()); auto[a,c]=split(root,r); auto[b,discard]=split(a,l);
      (void) discard; root = merge(b, c);
    }
    void reverse(int l, int r) {
      assert(0<=l&&l<=r&&r<=size()); auto[a,c]=split(root,r); auto[b,m]=split(a,l);
      flip(m); root = merge(merge(b, m), c);
    }
    int sum(int l, int r) {
      assert(0<=l&&l<=r&&r<=size()); auto[a,c]=split(root,r); auto[b,m]=split(a,l);
      int value=sum(m); root=merge(merge(b,m),c); return value;
    }
  };
//NOTEBOOK_END
}
