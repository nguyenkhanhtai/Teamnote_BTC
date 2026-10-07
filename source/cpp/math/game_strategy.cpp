#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  const int DRAW = 0, WIN = 1, LOSE = -1;
  vector<int> retrograde_analysis(int n, const vector<vector<int>>& adj){
    vector<int>out_deg(n),res(n,DRAW); vector<vector<int>>radj(n); queue<int>q;
    for (int u = 0; u < n; ++u) {
      out_deg[u] = adj[u].size();
      for (int v : adj[u]) radj[v].push_back(u);
      if (out_deg[u] == 0) { res[u] = LOSE; q.push(u); }
    }
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int p : radj[u]) {
        if (res[p] != DRAW) continue;
        if (res[u] == LOSE) {
          res[p] = WIN; q.push(p);
        } else if(res[u]==WIN){ if(--out_deg[p]==0){ res[p]=LOSE; q.push(p); } }
      }
    }
    return res;
  }
  int calc_mex(const vector<int>& vals) {
    int m = vals.size(); vector<bool> seen(m + 1, false);
    for (int x : vals) if (0 <= x && x <= m) seen[x] = true;
    for (int i = 0; i <= m; ++i) if (!seen[i]) return i;
    return m + 1;
  }
  int get_grundy(int u, vector<int>& g, const vector<vector<int>>& adj){
    if (g[u] != -1) return g[u];
    vector<int> nxt;
    for (int v : adj[u]) nxt.push_back(get_grundy(v, g, adj));
    return g[u] = calc_mex(nxt);
  }
  // get_grundy requires a DAG and caller-owned memo initialized to -1.
//NOTEBOOK_END
}
