#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto ans = reroot(g,identity,merge,finish,lift);
  //      RerootState: edit state type and write three named functions.
  // Associative merge, identity; finish(aggregate,u) adds vertex contribution.
  // lift(state,from,to) transforms a complete state across an edge. O(n) callbacks.
  using RerootState = pair<long long,long long>; // Change state for your DP.
  vector<RerootState> reroot(const vector<vector<int>>& g,RerootState identity,
      function<RerootState(RerootState,RerootState)> merge,
      function<RerootState(RerootState,int)> finish,
      function<RerootState(RerootState,int,int)> lift,int root=0){
    int n = g.size();
    if (!n) return {};
    vector<int> parent(n, -1), order {root};
    for(size_t i=0;i<order.size();++i)for(int v:g[order[i]])if(v!=parent[order[i]]){
      parent[v] = order[i]; order.push_back(v);
    }
    vector<RerootState> down(n, identity), up(n, identity), answer(n, identity);
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
      int u = *it; RerootState value = identity;
      for(int v:g[u])if(v!=parent[u])value=merge(value,lift(down[v],v,u));
      down[u] = finish(value, u);
    }
    for (int u : order) {
      int degree = g[u].size();
      vector<RerootState>pref(degree+1,identity),suff(degree+1,identity),messages;
      for(int v:g[u])messages.push_back(v==parent[u]?up[u]:lift(down[v],v,u));
      for(int i=0; i<degree; ++i)pref[i+1]=merge(pref[i],messages[i]);
      for(int i=degree-1; i>=0; --i)suff[i]=merge(messages[i],suff[i+1]);
      answer[u] = finish(pref[degree], u);
      for(int i=0;i<degree;++i)if(g[u][i]!=parent[u])up[g[u][i]]=lift(finish(merge(pref[i],suff[i+1]),u),u,g[u][i]);
    }
    return answer;
  }
//NOTEBOOK_END
}
