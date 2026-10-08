#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto wives = stable_marriage({{0,1},{1,0}},{{0,1},{1,0}});
  // Complete strict preference permutations, equal side sizes; proposer-optimal.
  vector<int>stable_marriage(const vector<vector<int>>&men,const vector<vector<int>>&women){
    int n = men.size(); assert(women.size() == men.size());
    vector<vector<int>> rank(n, vector<int>(n));
    for(int w=0; w<n; ++w)for(int i=0; i<n; ++i)rank[w][women[w][i]]=i;
    vector<int> husband(n, -1), wife(n, -1), next(n); queue<int> free;
    for (int m = 0; m < n; ++m) free.push(m);
    while (!free.empty()) {
      int m = free.front(); free.pop(); int w = men[m][next[m]++];
      if (husband[w] < 0 || rank[w][m] < rank[w][husband[w]]) {
        if(husband[w]>=0){ wife[husband[w]]=-1; free.push(husband[w]); }
        husband[w] = m; wife[m] = w;
      } else free.push(m);
    }
    return wife;
  }
//NOTEBOOK_END
}
