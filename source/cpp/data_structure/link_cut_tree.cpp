#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: LinkCutTree lct({1,2,3}); lct.link(0,1);
  // Dynamic forest, vertex values, path sum. 0-based IDs; -1 is no node.
  struct LinkCutTree {
    struct Node {
      int child[2] {-1,-1},parent=-1; bool rev=false; long long value=0,sum=0;
    }; vector<Node> t;
    bool is_root(int u) const {
      int p=t[u].parent; return p<0||(t[p].child[0]!=u&&t[p].child[1]!=u);
    }
    long long sum(int u) const { return u < 0 ? 0 : t[u].sum; }
    void pull(int u){ t[u].sum=t[u].value+sum(t[u].child[0])+sum(t[u].child[1]); }
    void flip(int u){ if(u>=0){ swap(t[u].child[0],t[u].child[1]); t[u].rev^=1; } }
    void push(int u) {
      if(t[u].rev){ flip(t[u].child[0]); flip(t[u].child[1]); t[u].rev=false; }
    }
    void rotate(int u) {
      int p=t[u].parent,g=t[p].parent,d=t[p].child[1]==u,v=t[u].child[d^1];
      if (!is_root(p)) t[g].child[t[g].child[1] == p] = u;
      t[u].parent=g; t[u].child[d^1]=p; t[p].parent=u; t[p].child[d]=v;
      if (v >= 0) t[v].parent = p;
      pull(p); pull(u);
    }
    void splay(int u) {
      vector<int> path {u};
      for (int v = u; !is_root(v);) path.push_back(v = t[v].parent);
      for (auto it = path.rbegin(); it != path.rend(); ++it) push(*it);
      while (!is_root(u)) {
        int p = t[u].parent, g = t[p].parent;
        if(!is_root(p))rotate((t[p].child[1]==u)==(t[g].child[1]==p)?p:u);
        rotate(u);
      }
    }
    int access(int u) {
      int last = -1;
      for (int v = u; v >= 0; v = t[v].parent) {
        splay(v); t[v].child[1] = last;
        if (last >= 0) t[last].parent = v;
        pull(v); last = v;
      }
      splay(u); return last;
    }
    int root(int u) {
      access(u);
      while (push(u), t[u].child[0] >= 0) u = t[u].child[0];
      splay(u); return u;
    }
    LinkCutTree(const vector<long long>&values):t(values.size()){
      for(int i=0; i<(int)t.size(); ++i)t[i].value=t[i].sum=values[i];
    }
    void make_root(int u) { access(u); flip(u); }
    bool connected(int u, int v) { return u == v || root(u) == root(v); }
    bool link(int u, int v) {
      make_root(u);
      if (root(v) == u) return false;
      t[u].parent = v; return true;
    }
    bool cut(int u, int v) {
      make_root(u); access(v);
      if (t[v].child[0] != u || t[u].child[1] >= 0) return false;
      t[v].child[0] = -1; t[u].parent = -1; pull(v); return true;
    }
    void set(int u,long long value){ access(u); t[u].value=value; pull(u); }
    optional<long long> path_sum(int u, int v) {
      if (!connected(u, v)) return nullopt;
      make_root(u); access(v); return t[v].sum;
    }
    optional<int> lca(int rooted_at, int u, int v) {
      if (!connected(rooted_at, u) || !connected(u, v)) return nullopt;
      make_root(rooted_at); access(u); return access(v);
    }
  };
//NOTEBOOK_END
}
