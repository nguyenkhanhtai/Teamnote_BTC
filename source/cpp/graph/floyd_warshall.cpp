#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: bool ok = floyd_warshall(dist); // vector<vector<int>>
  // Matrix includes diagonal 0, inf for absent edges. Reports whether a negative cycle exists.
  // Distances involving a negative cycle require separate -infinity propagation.
  bool floyd_warshall(vector<vector<int>>&d,int inf=1LL<<60){
    int n = d.size();
    for(int k=0;k<n;++k)for(int i=0;i<n;++i)if(d[i][k]<inf)for(int j=0;j<n;++j)if(d[k][j]<inf)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    for (int i = 0; i < n; ++i) if (d[i][i] < 0) return true;
    return false;
  }
//NOTEBOOK_END
}
