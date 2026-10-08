#pragma once
#include <bits/stdc++.h>
namespace notebook::tree {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: HeavyLight hld({{1},{0,2},{1}},0); auto seg = hld.subtree(1);
  //      Store vertex values at hld.pos[u]; seg = [l,r).
  // Zero-based positions; segments [l,r). rev=true means traverse r-1 down to l.
  // path_segments returns segments in u-to-v order, supports noncommutative folds.
  struct HeavyLight {
    struct Segment { int l, r; bool reversed; };
    vector<int> parent, depth, size, heavy, head, pos, vertex;
    HeavyLight(const vector<vector<int>>&g,int root=0):parent(g.size(),-1),depth(g.size()),size(g.size(),1),heavy(g.size(),-1),head(g.size()),pos(g.size()),vertex(g.size()){
      if (g.empty()) return;
      vector<int> order {root};
      for(size_t i=0;i<order.size();++i)for(int v:g[order[i]])if(v!=parent[order[i]]){
        parent[v]=order[i]; depth[v]=depth[order[i]]+1; order.push_back(v);
      }
      for(auto it=order.rbegin();it!=order.rend();++it)for(int v:g[*it])if(parent[v]==*it){
        size[*it] += size[v];
        if (heavy[*it] < 0 || size[v] > size[heavy[*it]]) heavy[*it] = v;
      }
      vector<pair<int, int>> tasks { {root, root} }; int timer = 0;
      while (!tasks.empty()) {
        auto [u, h] = tasks.back(); tasks.pop_back();
        for (; u != -1; u = heavy[u]) {
          head[u] = h; pos[u] = timer; vertex[timer++] = u;
          for(int v:g[u])if(parent[v]==u&&v!=heavy[u])tasks.push_back( {v,v});
        }
      }
    }
    int lca(int u, int v) const {
      while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        u = parent[head[u]];
      }
      return depth[u] < depth[v] ? u : v;
    }
    pair<int,int>subtree(int u)const { return {pos[u],pos[u]+size[u]}; }
    vector<Segment>path_segments(int u,int v,bool edges=false)const {
      vector<Segment> left, right;
      while (head[u] != head[v]) {
        if (depth[head[u]] >= depth[head[v]]) {
          left.push_back( {pos[head[u]],pos[u]+1,true}); u=parent[head[u]];
        }else { right.push_back( {pos[head[v]],pos[v]+1,false}); v=parent[head[v]]; }
      }
      if (depth[u] >= depth[v]) {
        if(pos[v]+edges<pos[u]+1)left.push_back( {pos[v]+edges,pos[u]+1,true});
      } else if(pos[u]+edges<pos[v]+1)right.push_back( {pos[u]+edges,pos[v]+1,false});
      reverse(right.begin(), right.end());
      left.insert(left.end(), right.begin(), right.end()); return left;
    }
  };
//NOTEBOOK_END
}
