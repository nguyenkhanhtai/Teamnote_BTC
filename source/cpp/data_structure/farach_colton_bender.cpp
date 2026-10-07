#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Nonempty tree, root=0 default; O(n) preprocessing, O(1) LCA.
  struct FCBLCA {
    vector<int>euler,depth,first,profile,log2; vector<vector<int>>sparse;
    vector<vector<unsigned char>> micro; int block;
    int better(int a,int b)const { return depth[a]<=depth[b]?a:b; }
    int inside(int b,int l,int r)const { return b*block+micro[profile[b]][l*block+r]; }
    explicit FCBLCA(const vector<vector<int>>&adj,int root=0):first(adj.size(),-1){
      assert(!adj.empty()); struct Frame { int u, p, next, d; };
      vector<Frame>stack { {root,-1,0,0} }; euler.push_back(root); depth.push_back(0);
      first[root] = 0;
      while (!stack.empty()) {
        auto& f = stack.back();
        if (f.next == int(adj[f.u].size())) {
          stack.pop_back();
          if (!stack.empty()) {
            euler.push_back(stack.back().u); depth.push_back(stack.back().d);
          }
          continue;
        }
        int v = adj[f.u][f.next++];
        if (v == f.p) continue;
        int u=f.u,d=f.d+1; first[v]=euler.size(); euler.push_back(v); depth.push_back(d);
        stack.push_back( {v, u, 0, d});
      }
      int m = euler.size(), lg = 0;
      while ((1LL << (lg + 1)) <= m) ++lg;
      block = max(1, lg / 2); int count = (m + block - 1) / block;
      micro.resize(1<<(block-1),vector<unsigned char>(block*block));
      for (int mask = 0; mask < int(micro.size()); ++mask) {
        vector<int> d(block);
        for(int i=1; i<block; ++i)d[i]=d[i-1]+((mask>>(i-1)&1)?1:-1);
        for (int l = 0; l < block; ++l) {
          int best = l;
          for (int r = l; r < block; ++r) {
            if (d[r] < d[best]) best = r;
            micro[mask][l * block + r] = best;
          }
        }
      }
      profile.resize(count); vector<int> minima(count);
      for (int b = 0; b < count; ++b) {
        int start = b * block, end = min(m, start + block), best = start;
        for (int i = start + 1; i < end; ++i) {
          if (depth[i] > depth[i - 1]) profile[b] |= 1 << (i - start - 1);
          best = better(best, i);
        }
        minima[b] = best;
      }
      log2.resize(count + 1);
      for (int i = 2; i <= count; ++i) log2[i] = log2[i / 2] + 1;
      sparse.push_back(move(minima));
      for (int k = 1; (1 << k) <= count; ++k) {
        sparse.push_back(vector<int>(count - (1 << k) + 1));
        for(int i=0;i<int(sparse[k].size());++i)sparse[k][i]=better(sparse[k-1][i],sparse[k-1][i+(1<<(k-1))]);
      }
    }
    int lca(int u, int v) const {
      int l = first[u], r = first[v];
      if (l > r) swap(l, r);
      int a = l / block, b = r / block;
      if (a == b) return euler[inside(a, l % block, r % block)];
      int best=better(inside(a,l%block,block-1),inside(b,0,r%block));
      if (a + 1 < b) {
        int k=log2[b-a-1]; best=better(best,better(sparse[k][a+1],sparse[k][b-(1<<k)]));
      }
      return euler[best];
    }
  };
//NOTEBOOK_END
}
