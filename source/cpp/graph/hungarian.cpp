#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto ans = hungarian({{3,1},{2,4}}); // ans.cost, ans.column
  struct Assignment { int cost; vector<int> column; };
  // Minimum rectangular assignment, rows<=columns; costs may be negative.
  Assignment hungarian(const vector<vector<int>>& a) {
    int n = a.size();
    if (!n) return {
      0, {}
    }; int m=a[0].size(); assert(n<=m); vector<int>u(n+1),v(m+1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
      p[0]=i; int j0=0; vector<int>best(m+1,1LL<<60); vector<bool>used(m+1);
      do {
        used[j0]=true; int row=p[j0],j1=0; int delta=1LL<<60;
        for (int j = 1; j <= m; ++j) if (!used[j]) {
          int value = a[row - 1][j - 1] - u[row] - v[j];
          if (value < best[j]) { best[j] = value; way[j] = j0; }
          if (best[j] < delta) { delta = best[j]; j1 = j; }
        }
        for (int j = 0; j <= m; ++j) if (used[j]) {
          u[p[j]] += delta; v[j] -= delta;
        } else best[j] -= delta;
        j0 = j1;
      }
      while (p[j0]);
      do { int previous = way[j0]; p[j0] = p[previous]; j0 = previous; }
      while (j0);
    }
    vector<int> column(n);
    for (int j = 1; j <= m; ++j) if (p[j]) column[p[j] - 1] = j - 1;
    return {-v[0], column};
  }
//NOTEBOOK_END
}
