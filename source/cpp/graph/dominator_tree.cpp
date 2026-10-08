#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto idom = immediate_dominators({{1},{2},{}},0);
  // Immediate dominators from source; source dominates itself; unreachable=-1.
  // Lengauer-Tarjan; recursive eval compression, O((n+m) log n) bound.
  vector<int>immediate_dominators(const vector<vector<int>>&g,int source){
    int n=g.size(); vector<int>index(n),vertex(1,-1),parent(1),order {source};
    struct Frame { int u,next; }; vector<Frame>stack { {source,0} }; index[source]=1;
    vertex.push_back(source); parent.push_back(0);
    while (!stack.empty()) {
      auto& f = stack.back();
      if (f.next == int(g[f.u].size())) { stack.pop_back(); continue; }
      int v = g[f.u][f.next++];
      if (index[v]) continue;
      int p=index[f.u]; index[v]=vertex.size(); vertex.push_back(v); parent.push_back(p);
      stack.push_back( {v, 0});
    }
    int count = vertex.size() - 1;
    vector<int>semi(count+1),label(count+1),ancestor(count+1),idom(count+1);
    iota(semi.begin(),semi.end(),0); iota(label.begin(),label.end(),0);
    vector<vector<int>> pred(count + 1), bucket(count + 1);
    for(int u=0;u<n;++u)if(index[u])for(int v:g[u])if(index[v])pred[index[v]].push_back(index[u]);
    struct DominatorDSU {
      vector<int>& ancestor; vector<int>& label; vector<int>& semi;
      void compress(int v) {
        if (ancestor[ancestor[v]]) {
          compress(ancestor[v]);
          if (semi[label[ancestor[v]]]<semi[label[v]]) label[v]=label[ancestor[v]];
          ancestor[v]=ancestor[ancestor[v]];
        }
      }
      int eval(int v) {
        if (ancestor[v]) compress(v);
        return label[v];
      }
    } dsu{ancestor,label,semi};
    for (int w = count; w > 1; --w) {
      for (int v : pred[w]) semi[w] = min(semi[w], semi[dsu.eval(v)]);
      bucket[semi[w]].push_back(w); ancestor[w] = parent[w];
      for(int v:bucket[parent[w]]){ int u=dsu.eval(v); idom[v]=semi[u]<semi[v]?u:parent[w]; }
      bucket[parent[w]].clear();
    }
    for(int w=2; w<=count; ++w)if(idom[w]!=semi[w])idom[w]=idom[idom[w]];
    vector<int> answer(n, -1); answer[source] = source;
    for (int w = 2; w <= count; ++w) answer[vertex[w]] = vertex[idom[w]];
    return answer;
  }
//NOTEBOOK_END
}
