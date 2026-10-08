#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto edges = prufer_decode({0,1}); // n = code.size()+2
  // Labels 0..n-1; tree n>=2. O(n log n); decode uses n=code.size()+2.
  vector<int> prufer_encode(const vector<vector<int>>& g) {
    int n = g.size(); assert(n >= 2); vector<int> degree(n);
    priority_queue<int, vector<int>, greater<int>> leaves;
    for(int u=0; u<n; ++u)if((degree[u]=g[u].size())==1)leaves.push(u);
    vector<int> code;
    for (int i = 0; i < n - 2; ++i) {
      int u = leaves.top(); leaves.pop(); degree[u] = 0;
      for (int v : g[u]) if (degree[v]) {
        code.push_back(v);
        if (--degree[v] == 1) leaves.push(v);
        break;
      }
    }
    return code;
  }
  vector<pair<int, int>> prufer_decode(const vector<int>& code) {
    int n = code.size() + 2; vector<int> degree(n, 1);
    for (int u : code) { assert(0 <= u && u < n); ++degree[u]; }
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int u = 0; u < n; ++u) if (degree[u] == 1) leaves.push(u);
    vector<pair<int, int>> edges;
    for (int u : code) {
      int v = leaves.top(); leaves.pop(); edges.push_back( {u, v});
      if (--degree[u] == 1) leaves.push(u);
    }
    int a=leaves.top(); leaves.pop(); edges.push_back( {a,leaves.top()}); return edges;
  }
//NOTEBOOK_END
}
