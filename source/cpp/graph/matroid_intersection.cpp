#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
using namespace std;
//NOTEBOOK_BEGIN
  // Use: MatroidIntersection mi(n,oracle1,oracle2); auto ids = mi.solve();
  //      Each oracle: bool(const vector<int>& selectedIDs).
  struct MatroidIntersection {
      // Oracle receives element IDs of a proposed set; no duplicates.
      using Oracle = function<bool(const vector<int>&)>;
      int n;
      Oracle independent1, independent2;

      MatroidIntersection(int n, Oracle first, Oracle second)
          : n(n), independent1(move(first)), independent2(move(second)) {}

      // Maximum cardinality; ground set is [0,n). Not weighted.
      vector<int> solve() const {
          vector<char> chosen(n, false);
          vector<int> selected;
          while (true) {
              int source = n, sink = n + 1;
              vector<vector<int>> graph(n + 2);
              vector<int> trial = selected;
              for (int x = 0; x < n; ++x) if (!chosen[x]) {
                  trial.push_back(x);
                  if (independent1(trial)) graph[source].push_back(x);
                  if (independent2(trial)) graph[x].push_back(sink);
                  trial.pop_back();
                  for (int i = 0; i < int(selected.size()); ++i) {
                      int y = selected[i];
                      trial[i] = x;
                      if (independent1(trial)) graph[y].push_back(x);
                      if (independent2(trial)) graph[x].push_back(y);
                      trial[i] = y;
                  }
              }
              vector<int> parent(n + 2, -1);
              queue<int> q;
              parent[source] = source;
              q.push(source);
              while (!q.empty() && parent[sink] == -1) {
                  int u = q.front(); q.pop();
                  for (int v : graph[u]) if (parent[v] == -1) {
                      parent[v] = u;
                      q.push(v);
                  }
              }
              if (parent[sink] == -1) return selected;
              for (int x = parent[sink]; x != source; x = parent[x])
                  chosen[x] ^= 1;
              selected.clear();
              for (int x = 0; x < n; ++x)
                  if (chosen[x]) selected.push_back(x);
          }
      }
  };
//NOTEBOOK_END
}
