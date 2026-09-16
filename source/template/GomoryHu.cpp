#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

const long long inf = 1LL << 61;
struct Dinic {
  struct edge {
    int to, rev;
    long long flow, w;
    int id;
  };
  int n, s, t, mxid;
  vector<int> d, flow_through;
  vector<int> done;
  vector<vector<edge>> g;
  Dinic() {}
  Dinic(int _n) {
    n = _n + 10;
    mxid = 0;
    g.resize(n);
  }
  void add_edge(int u, int v, long long w, int id = -1) {
    edge a = {v, (int)g[v].size(), 0, w, id};
    edge b = {u, (int)g[u].size(), 0, w, -2};//for bidirectional edges cap(b) = w
    g[u].emplace_back(a);
    g[v].emplace_back(b);
    mxid = max(mxid, id);
  }
  bool bfs() {
    d.assign(n, -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &e : g[u]) {
        int v = e.to;
        if (d[v] == -1 && e.flow < e.w) d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t] != -1;
  }
  long long dfs(int u, long long flow) {
    if (u == t) return flow;
    for (int &i = done[u]; i < (int)g[u].size(); i++) {
      edge &e = g[u][i];
      if (e.w <= e.flow) continue;
      int v = e.to;
      if (d[v] == d[u] + 1) {
        long long nw = dfs(v, min(flow, e.w - e.flow));
        if (nw > 0) {
          e.flow += nw;
          g[v][e.rev].flow -= nw;
          return nw;
        }
      }
    }
    return 0;
  }
  long long max_flow(int _s, int _t) {
    s = _s;
    t = _t;
    long long flow = 0;
    while (bfs()) {
      done.assign(n, 0);
      while (long long nw = dfs(s, inf)) flow += nw;
    }
    flow_through.assign(mxid + 10, 0);
    for(int i = 0; i < n; i++) for(auto e : g[i]) if(e.id >= 0) flow_through[e.id] = e.flow;
    return flow;
  }
};

/*For a given weighted graph, int the Gomory-Hu tree the maximum flow 
between vertices u and v in the tree(i.e. minimum edge from u to v)
is equal to the maximum flow in the graph.*/
struct edge{
	int u, v;
	long long w;
};
// all nodes are from 1 to n
// returns edges of the gomory hu tree
vector<edge> gomory_hu_tree(int n, vector<edge> &ed) {
	vector<edge> ans;
	vector<int> par(n + 1, 1);
	for (int i = 2; i <= n; i++) {
    Dinic F(n + 1);
    for (auto &e : ed) F.add_edge(e.u, e.v, e.w);
		int s = i, t = par[i];
		ans.push_back({s, t, F.max_flow(s, t)});
		for (int j = i + 1; j <= n; j++) {
			if (F.d[j] != -1 and par[j] == par[i]) {
				par[j] = i;
			}
		}
	}
	return ans;
}
cin >> n >> m;
vector<edge> ed(m);
for (edge &e : ed) cin >> e.u >> e.v >> e.w;
auto t = gomory_hu_tree(n, ed);
// https://codeforces.com/contest/343/problem/E